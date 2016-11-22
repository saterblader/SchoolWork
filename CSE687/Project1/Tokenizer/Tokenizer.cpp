/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2015                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:		Philip D. Geramian, Syracuse University			   //
//				pdgerami@syr.edu								   //
// Source:      Jim Fawcett, Syracuse University, CST 4-187        //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>
#include <vector>

namespace Scanner
{
  class ConsumeState
  {
  public:
    using Token = std::string;
    ConsumeState();
    ConsumeState(const ConsumeState&) = delete;
    ConsumeState& operator=(const ConsumeState&) = delete;
    virtual ~ConsumeState();
    void attach(std::istream* pIn) { _pIn = pIn; }
    virtual void eatChars() = 0;
    void consumeChars() {
      _pState->eatChars();
      _pState = nextState();
    }
    bool canRead() { return _pIn->good(); }
    std::string getTok() { return token; }
    bool hasTok() { return token.size() > 0; }
    ConsumeState* nextState();
	void setSpecialSingleChars(std::string ssc);
	void setSpecialCharPairs(std::string scp);
  protected:
    bool isOneCharToken(Token tok);
    bool isTwoCharToken(Token tok);
    Token makeString(int c);
    static std::string token;
    static std::istream* _pIn;
    std::vector<std::string> _oneCharTokens = {
		"<", ">", "{", "}", "[", "]", "(", ")", 
		":", "=", "+", "-", "*","\n"};
    std::vector<std::string> _twoCharTokens = { 
		"<<", ">>", "::", "++", "--", "==", "+=",
		"-=", "*=", "/="};
    static int prevChar;
    static int currChar;
    static ConsumeState* _pState;
    static ConsumeState* _pEatCppComment;
    static ConsumeState* _pEatCComment;
    static ConsumeState* _pEatWhitespace;
    static ConsumeState* _pEatPunctuator;
    static ConsumeState* _pEatAlphanum;
    static ConsumeState* _CheckSpecialChar;
    static ConsumeState* _pEatDoubleString;
    static ConsumeState* _pEatSingleString;
  };
}

using namespace Scanner;

std::string ConsumeState::token;
std::istream* ConsumeState::_pIn = nullptr;
int ConsumeState::prevChar;
int ConsumeState::currChar;
ConsumeState* ConsumeState::_pState = nullptr;
ConsumeState* ConsumeState::_pEatCppComment = nullptr;
ConsumeState* ConsumeState::_pEatCComment = nullptr;
ConsumeState* ConsumeState::_pEatWhitespace = nullptr;
ConsumeState* ConsumeState::_pEatPunctuator = nullptr;
ConsumeState* ConsumeState::_pEatAlphanum = nullptr;
ConsumeState* ConsumeState::_CheckSpecialChar = nullptr;
ConsumeState* ConsumeState::_pEatDoubleString = nullptr;
ConsumeState* ConsumeState::_pEatSingleString = nullptr;

//Logger if TEST_LOG is defined

void testLog(const std::string& msg);

// Add 1char token

void ConsumeState::setSpecialSingleChars(std::string ssc)
{
	_oneCharTokens.push_back(ssc);
}
// Add 2char token

void ConsumeState::setSpecialCharPairs(std::string scp)
{
	_twoCharTokens.push_back(scp);
}
// Is a 1char token?

bool ConsumeState::isOneCharToken(Token tok)
{
  for (int i = 0; i < _oneCharTokens.size(); i++)
    if (_oneCharTokens[i] == tok)
      return true;
  return false;
}
// Is a 2char token?

bool ConsumeState::isTwoCharToken(Token tok)
{
  for (int i = 0; i < _twoCharTokens.size(); i++)
	  if (_twoCharTokens[i] == tok)
	  {
		  return true;
	  }
  return false;
}
// Convert int to string (aka Token)

ConsumeState::Token ConsumeState::makeString(int c)
{
  Token temp;
  return temp += c;
}
// Select next state

ConsumeState* ConsumeState::nextState()
{
  if (!(_pIn->good()))
  {
    return nullptr;
  }
  int chNext = _pIn->peek();
  if (chNext == EOF)
  {
    _pIn->clear();
  }
  if (isOneCharToken(makeString(currChar)))
  {
	testLog("state: Check Special Chars");
    return _CheckSpecialChar;
  }
  if (std::isspace(currChar) && currChar != '\n')
  {
    testLog("state: Whitespace");
    return _pEatWhitespace;
  }
  if (currChar == '/' && chNext == '/')
  {
    testLog("state: Cpp Comment");
    return _pEatCppComment;
  }
  if (currChar == '/' && chNext == '*')
  {
    testLog("state: C Comment");
    return _pEatCComment;
  }
  if (std::isalnum(currChar) || currChar == '_')
  {
    testLog("state: Alpha Num");
    return _pEatAlphanum;
  }
  if (currChar == '\"' && prevChar != '\\')
  {
	testLog("state: Double String");
	return _pEatDoubleString;
  }
  if (currChar == '\'' && prevChar != '\\')
  {
	testLog("state: Single String");
    return _pEatSingleString;
  }
  if (ispunct(currChar))
  {
    testLog("state: Punctuator");
    return _pEatPunctuator;
  }
  if (!_pIn->good())
  {
	testLog("state: Whitespace");
    return _pEatWhitespace;
  }
  throw(std::logic_error("invalid type"));
}
// Process white space

class EatWhitespace : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    do {
      if (!_pIn->good())  // end of stream
        return;
      prevChar = currChar;
      currChar = _pIn->get();
    } while (std::isspace(currChar) && currChar != '\n');
  }
};
// Process C comment

class EatCComment : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do {
			if (!_pIn->good())  // end of stream
				return;
			token += currChar;
			prevChar = currChar;
			currChar = _pIn->get();
		} while (currChar != '*' || _pIn->peek() != '/');
		token += currChar;
		prevChar = currChar;
		currChar = _pIn->get();    // get terminating / character
		token += currChar;
		prevChar = currChar;
		currChar = _pIn->get();    // get first non-comment character
	}
};
// Process C++ comment

class EatCppComment : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    do {
      if (!_pIn->good())  // end of stream
        return;
      token += currChar;
      prevChar = currChar;
      currChar = _pIn->get();
    } while (currChar != '\n');
  }
};
// Process Alphas/ Nums
// counts '_' as char for clarity of reading

class EatAlphanum : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do {
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			prevChar = currChar;
			currChar = _pIn->get();
		} while (isalnum(currChar) || currChar=='_');
	}
};
// Process punctuation

class EatPunctuator : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    do {
      if (currChar == '\"' && prevChar != '\\')    // start of double quoted string
      {
        return;
      }
      if (currChar == '\'' && prevChar != '\\')    // start of single quoted string
      {
        return;
      }
      Token temp = makeString(currChar);
      if (isOneCharToken(temp))
      {
        return;
      }
      token += currChar;
      if (!_pIn->good())  // end of stream
      {
        return;
      }
      prevChar = currChar;
      currChar = _pIn->get();
    } while (ispunct(currChar));
  }
};
// Gets a possible 1char token, checks if a 2char token

class CheckSpecialChar : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    token += currChar;
    Token temp = makeString(currChar) += _pIn->peek();
    if (isTwoCharToken(temp))
    {
      prevChar = currChar;
      currChar = _pIn->get();
      token += currChar;
    }
    if (!_pIn->good())  // end of stream
      return;
    prevChar = currChar;
    currChar = _pIn->get();
  }
};
// Handles single quote strings discarding external quotes

class EatSingleString : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do
		{
			if (currChar != '\'')
			{
				token += currChar;
				prevChar = currChar;
				currChar = _pIn->get();
			}
			else if (currChar == '\'' && prevChar == '\\')
			{
				token.pop_back();
				token += currChar;
				prevChar = currChar;
				currChar = _pIn->get();
			}
			else
			{
				prevChar = currChar;
				currChar = _pIn->get();
			}
		} while (currChar != '\'' || prevChar == '\\');
		prevChar = currChar;
		currChar = _pIn->get();
	}
};
// Handles double quote strings discarding external quotes

class EatDoubleString : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    do
    {
		if (currChar != '\"' )
		{
			token += currChar;
			prevChar = currChar;
			currChar = _pIn->get();
		}
		else if (currChar == '\"' && prevChar == '\\' )
		{
			token.pop_back();
			token += currChar;
			prevChar = currChar;
			currChar = _pIn->get();
		}
		else
		{
			prevChar = currChar;
			currChar = _pIn->get();
		}
    } while (currChar != '\"' || prevChar == '\\');
    prevChar = currChar;
    currChar = _pIn->get();
  }
};
// Consume state constructor

ConsumeState::ConsumeState()
{
  static bool first = true;
  if (first)
  {
    first = false;
    _pEatAlphanum = new EatAlphanum();
    _pEatCComment = new EatCComment();
    _pEatCppComment = new EatCppComment();
    _pEatPunctuator = new EatPunctuator();
    _pEatWhitespace = new EatWhitespace();
    _pEatDoubleString = new EatDoubleString();
    _pEatSingleString = new EatSingleString();
	_CheckSpecialChar = new CheckSpecialChar();
    _pState = _pEatWhitespace;
  }
}
// ConsumeState destructor

ConsumeState::~ConsumeState()
{
  static bool first = true;
  if (first)
  {
    first = false;
    delete _pEatAlphanum;
    delete _pEatCComment;
    delete _pEatCppComment;
    delete _pEatPunctuator;
    delete _pEatWhitespace;
    delete _pEatDoubleString;
    delete _pEatSingleString;
	delete _CheckSpecialChar;
  }
}
// Constructor, set toker to EatWhiteSpace

Toker::Toker() : pConsumer(new EatWhitespace()) {}

// Toker destructor

Toker::~Toker() 
{ 
	delete pConsumer; 
}

// Put stream into tokenizer

bool Toker::attach(std::istream* pIn)
{
  if (pIn->good() && pIn != nullptr)
  {
    pConsumer->attach(pIn);
    return true;
  }
  return false;
}
// Get token made by ConsumeState

std::string Toker::getTok()
{
  while(true) 
  {
    if (!pConsumer->canRead())
      return "";
    pConsumer->consumeChars();
    if (pConsumer->hasTok())
      break;
  }
  return pConsumer->getTok();
}
// Toker at end of stream?

bool Toker::canRead() 
{
	return pConsumer->canRead(); 
}
// Add One Char Tokens

void Toker::setOneCharTokens(const std::vector<std::string>& chars)
{
	for (size_t i = 0; i < chars.size(); i++)
	{
		pConsumer->setSpecialSingleChars(chars[i]);
	}
}
// Add Two Char Tokens

void Toker::setTwoCharTokens(const std::vector<std::string>& chars)
{
	for (size_t i = 0; i < chars.size(); i++)
	{
		pConsumer->setSpecialCharPairs(chars[i]);
	}

}

// Show debug output if TEST_LOG is defined

void testLog(const std::string& msg)
{
#ifdef TEST_LOG
  std::cout << "\n  " << msg;
#endif
}

//Main if TEST_TOKENIZER is defined

#ifdef TEST_TOKENIZER

#include <fstream>

int main()
{
  //std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
  //std::string fileSpec = "../Tokenizer/Tokenizer.h";
  std::string fileSpec = "../Tokenizer/Test.txt";
  std::ifstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open " << fileSpec << "\n\n";
    return 1;
  }
  Toker toker;
  std::vector<std::string> doubles{"^^"};
  std::vector<std::string> singles{"&"};
  toker.setOneCharTokens(singles);
  toker.setTwoCharTokens(doubles);
  toker.attach(&in);
  do
  {
    std::string tok = toker.getTok();
    if (tok == "\n")
      tok = "newline";
    std::cout << "\n -- " << tok;
  } while (in.good());

  std::cout << "\n\n";
  return 0;
}
#endif

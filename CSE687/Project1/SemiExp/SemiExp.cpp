///////////////////////////////////////////////////////////////////////
// SemiExpression.cpp - collect tokens for analysis                  //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
// Author:		Philip D. Geramian, Syracuse University				 //
//				pdgerami@syr.edu									 //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "SemiExp.h"
#include "../Tokenizer/Tokenizer.h"


using namespace Scanner;

// Construct SemiExpression

SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}

// Finds a tokens location, if not found return length of toke

size_t SemiExp::find(std::string token)
{
  for (size_t i = 0; i < length(); i++)
    if (_tokens[i] == token)
      return i;
  return length();
}
// Removes a token at a given position

bool SemiExp::remove(size_t n)
{
  if (n < 0 || n >= length())
    return false;
  std::vector<Token>::iterator iter = _tokens.begin() + n;
  _tokens.erase(iter);
  return true;
}
//Removes a particular token

bool SemiExp::remove(const std::string& token)
{
	size_t loc = _tokens.size();
	bool success = false;
	loc = find(token);
	if (loc != _tokens.size())
	{
		success = remove(loc);
		return success;
	}
	return success;
}
// Clear tokens

void SemiExp::clear()
{
	for (size_t i = 0; i < _tokens.size(); i++)
	{
		remove(i);
	}
}
// Add element to _token

void SemiExp::push_back(const std::string& token)
{
	_tokens.push_back(token);
}
// Makes all tokens lowercase

void SemiExp::toLower()
{
	for (size_t i = 0; i < _tokens.size(); i++)
	{
		for (size_t j = 0; j < _tokens[i].length(); j++)
			_tokens[i][j] = tolower(_tokens[i][j]);
	}
}

// Remove unneeded newlines

void SemiExp::trimFront()
{
	while (length() > 1)
	{
		if (_tokens[0] == "\n")
			remove(0);
		else
			break;
	}
}

// Checks if the for is the older style (semi-colons) as show in class

bool SemiExp::CheckIfOldFor()
{
  int openParen = find("(");
  int semiColon = find(";");
  int closedParen = find(")");

  if (openParen < semiColon && semiColon < closedParen)
    return true;
  return false;
}
// Processes SemiExpression from toker as shown in class

bool SemiExp::get(bool clear)
{
  bool ok = getHelper(clear);

  if (hasFor && CheckIfOldFor())
  {
    getHelper(false);
    getHelper(false);
  }
  return ok;
}
// The 'real' getter (accounts for 'for(;;)')

bool SemiExp::getHelper(bool clear)
{
  hasFor = false;
  if (_pToker == nullptr)
    throw(std::logic_error("no vaild reference"));
  if(clear)
    _tokens.clear();
  std::string token;
  while (true)
  {
    token = _pToker->getTok();
    if (token == "")
      break;
    _tokens.push_back(token);

    if (token == "for")
      hasFor = true;
    
    if (token == "{" || token == "}" || token == ";")
      return true;

    if (token == "\n")
    {
		trimFront();
		if (_tokens[0] == "#")
			return true;
    }
    if (token == ":" && length() > 0 && _tokens[length() - 2] == "public")
      return true;

    if (token == ":" && length() > 0 && _tokens[length() - 2] == "protected")
      return true;

    if (token == ":" && length() > 0 && _tokens[length() - 2] == "private")
      return true;
  }
  return false;
}
// Read-Only index

Token SemiExp::operator[](size_t n) const
{
  if (n < 0 || n >= _tokens.size())
    throw(std::invalid_argument("index out of range"));
  return _tokens[n];
}
// Writeable index

Token& SemiExp::operator[](size_t n)
{
  if (n < 0 || n >= _tokens.size())
    throw(std::invalid_argument("index out of range"));
  return _tokens[n];
}
// Retruns Length of semiexpression

size_t SemiExp::length()
{
  return _tokens.size();
}
// Print out tokens

void SemiExp::show()
{
  std::cout << "\n  ";
  for (int i = 0; i < _tokens.size();i++)
    if(_tokens[i] != "\n")
      std::cout << _tokens[i] << " ";
  std::cout << "\n";
}

#ifdef TEST_SEMIEXP
int main()
{
  std::cout << "\n  Testing SemiExp class";
  std::cout << "\n =======================\n";
  Toker toker;
  std::string fileSpec = "SemiExp.cpp";
  std::fstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open file " << fileSpec << "\n\n";
    return 1;
  }
  toker.attach(&in);
  SemiExp semi(&toker);
  while (semi.get()) {}
  if (semi.length() > 0)
  {
    std::cout << "\n  Last SemiExpression";
	std::cout << semi.push_back("return");
	semi.show();
	std::cout<<semi.remove("return");
	semi.show();
    std::cout << "\n";
  }
  return 0;
}
#endif
//COMMENT FOR EASE OF TESTING.


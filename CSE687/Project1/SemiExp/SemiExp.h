#ifndef SEMIEXPRESSION_H
#define SEMIEXPRESSION_H
///////////////////////////////////////////////////////////////////////
// SemiExpression.h - collect tokens for analysis                    //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
// Author:		Philip D. Geramian, Syracuse University				 //
//				pdgerami@syr.edu									 //
// Source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a public SemiExp class that collects and makes
* available sequences of tokens.  SemiExp uses the services of a Toker
* class to acquire tokens.  Each call to SemiExp::get() returns a 
* sequence of tokens that ends in { , or ;. This will also return a 
* sperate token that begin with a }. Additionally this will create a 
* token if a line begins with a # and ends with a '\n'.
*
* Build Process:
* --------------
* Required Files: 
*   SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp
* 
* Build Command: devenv Project1.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : Feb. 9, 2016
* - Initial release for CSE-687 Project 1
*/

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "itokcollection.h"

namespace Scanner
{
  using Token = std::string;

  class SemiExp : public ITokCollection
  {
  public:
    SemiExp(Toker* pToker = nullptr);
    SemiExp(const SemiExp&) = delete;
    SemiExp& operator=(const SemiExp&) = delete;
    bool get(bool clear = true);
    Token& operator[](size_t n);
    Token operator[](size_t n) const;
    size_t length();
    size_t find(std::string token);
    bool remove(size_t n);
	bool remove(const std::string& token);
    void show();
	void clear();
	void push_back(const std::string& token);
	void toLower();
	void trimFront();
  private:
    bool getHelper(bool clear = false);
    bool CheckIfOldFor();
    bool hasFor = false;
    std::vector<Token> _tokens;
    Toker* _pToker;
  };
}
#endif

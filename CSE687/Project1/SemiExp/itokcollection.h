#ifndef ITOKCOLLECTION_H
#define ITOKCOLLECTION_H
/////////////////////////////////////////////////////////////////////
// ITokCollection.h - package for the ITokCollection interface     //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2015                            //
// Application: Prototype for CSE687 Pr1, Sp16                     //
// Author:		Philip D. Geramian, Syracuse University			   //
//				pdgerami@syr.edu								   //
// Source:      Jim Fawcett, Syracuse University, CST 4-187        //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////
/*
Module Purpose:
===============
ITokCollection is an interface that supports substitution of different
types of scanners for parsing.  In this solution, we demonstrate this
for the SemiExp Class

Maintenance History:
====================
ver 1.0 : Feb. 9, 2016
- Initial release for CSE-687 Project 1
*/

#include <string>
namespace Scanner
{
	struct ITokCollection
	{
		virtual bool get(bool clear = true) = 0;
		virtual size_t length() = 0;
		virtual std::string& operator[](size_t n) = 0;
		virtual size_t find(const std::string tok) = 0;
		virtual void push_back(const std::string& tok) = 0;
		virtual bool remove(const std::string& tok) = 0;
		virtual bool remove(size_t i) = 0;
		virtual void toLower() = 0;
		virtual void trimFront() = 0;
		virtual void clear() = 0;
		virtual void show() = 0;
		virtual ~ITokCollection() {};
	};
}
#endif

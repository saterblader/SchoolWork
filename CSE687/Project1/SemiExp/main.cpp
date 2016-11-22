/////////////////////////////////////////////////////////////////////////////
// Main.c - Test main for Project #1									   //
// ver 1.0																   //
// Language:    C++, Visual Studio 2015									   //
// Application: Test Executive Package, CSE687 - Object Oriented Design    //
// Author:		Philip D. Geramian, Syracuse University					   //
//				pdgerami@syr.edu										   //
/////////////////////////////////////////////////////////////////////////////
#include "itokcollection.h"
#include "SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include <iostream>
#include <fstream>

using namespace Scanner;
using namespace std;

//Fully test all functionality required of ITokenCollection and thus the
//requirements of the project 
//(To the best of my understanding of what the demo is supposed to do)
int main()
{
	Toker toker;
	string fileSpec = "SemiExp.cpp";
	fstream in(fileSpec);
	if (!in.good())
	{
		cout << "\n  can't open file " << fileSpec << "\n\n";
		return 1;
	}
	toker.attach(&in);
	SemiExp semi(&toker);
	cout << "\nget demo\n";
	while (semi.get()) {}
	if (semi.length() > 0)
	{
		cout << "show demo";
		semi.show();
		cout << "length demo: " << semi.length()<<"\n";
		cout << "[] demo: " << semi[1];
		cout << "push_back demo: ";
		semi.push_back("test");
		semi.show();
		cout << "find demo: " << semi.find("test") << "\n";
		cout << "remove string demo: ";
		semi.remove("test");
		semi.show();
		cout << "remove index demo: ";
		semi.remove(1);
		semi.show();
		cout << "toLower demo: ";
		semi.toLower();
		semi.show();
		cout << "trimFront demo: ";
		semi.trimFront();
		semi.show();
		cout << "Clear demo: ";
		semi.clear();
		semi.show();
		cout << "Above should be blank showing cleared\n";
	}

	return 0;
}
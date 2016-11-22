/////////////////////////////////////////////////////////////////////
//  MetricsExecutive.cpp - The Metrics Executive package to meet   //
//							requirement #9 of project 2			   //
//  ver 1.1                                                        //
//  Language:      Visual C++ 2015,		                           //
//  Platform:      Macbook Pro, Windows 10				           //
//  Application:   Prototype for CSE687 Pr2, Sp16                  //
//  Author:        Philip Geramian,Syracuse University			   //
//                 pdgerami@syr.edu						           //
/////////////////////////////////////////////////////////////////////
/*
Useage:
=======
To use this application please invoke via command line using one of these methods:
a) $ MetricsExecutive.cpp 
This will search for all .cpp and .h files in your current directory and down and run the parser on them
b) $ MetricsExecutive.cpp PATH
This will search for all .cpp and .h files in PATH and down and run the parser on them
c) $ MetricsExecutive.cpp PATH PATTERN1 PATTERN2 ... PATTERNn-1 PATTERNn
This will search for Pattern 1 through Pattern n files in PATH and run the parser on them


Build Process:
==============
Required files
- MetricsExecutive.cpp, Parser.h, Parser.cpp, SemiExpression.h, 
SemiExpression.cpp, tokenizer.h, tokenizer.cpp,
ActionsAndRules.h, ActionsAndRules.cpp,
ConfigureParser.h, ConfigureParser.cpp
Build commands (either one)
- devenv Parser.sln

Maintenance History:
====================
ver 1.1
-An attempt at a tree walk
ver 1.0
-Initial Release for Project #2
*/
#include "Parser.h"
#include "../FileMgr/FileSystem.h"
#include "../FileMgr/FileMgr.h"
#include "ConfigureParser.h"
#include "../Utilities/Utilities.h"
#include "../DataStore/DataStore.h"

using namespace Utilities;
#define Util StringHelper
void TreeWalk(element* pItem);
int parse(DataStore ds)
{
	for (auto fs : ds)
	{
		std::string fileSpec = FileSystem::Path::getFullFileSpec(fs);
		std::cout<< "Processing file " + fileSpec<<std::endl;

		ConfigParseToConsole configure;
		Parser* pParser = configure.Build();
		try
		{
			if (pParser)
			{
				if (!configure.Attach(fs))
				{
					std::cout << "\n  could not open file " << fileSpec << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return 1;
			}

			// now that parser is built, use it
			while (pParser->next())
				pParser->parse();
			std::cout << "\n";
			element pTop;
			configure.repo()->scopeStack().topptr()->lineCountEnd = configure.repo()->lineCount();
			pTop = configure.repo()->scopeStack().pop();
			std::cout << "Tree Walk of " << fileSpec << "\n";
			showStack(configure.repo()->Tree(),false);
			std::cout << "\n";
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}


	}
	std::cout << "\n";
	return 0;
}
int main(int argc, char* argv[])
{
	DataStore ds;
	if (argc == 1)
	{
		FileMgr fm("../parser", ds);
		fm.addPattern("*.h");
		fm.addPattern("*.cpp");
		fm.search();
	}
	else if (argc == 2)
	{
		FileMgr fm(argv[1], ds);
		fm.addPattern("*.h");
		fm.addPattern("*.cpp");
		fm.search();
	}
	else
	{
		FileMgr fm(argv[1], ds);
		for (int i = 2; i < argc; i++)
			fm.addPattern(argv[i]);
		fm.search();
	}
	int out = parse(ds);
	return out;
}


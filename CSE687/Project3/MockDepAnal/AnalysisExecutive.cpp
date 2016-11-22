/////////////////////////////////////////////////////////////////////
// AnalysisExecutive - Analysis Exec Package for Proj #3		   //
//  Version 1.0                                                    //
//  Platform:      MacBook Pro, Windows 10 Pro				       //	
//																   //
//  Author:		   Philip Geramian, Syracuse University			   //
//  Source: Jim Fawcett											   //
/////////////////////////////////////////////////////////////////////
/*
*
* This solution uses packages:
* - AnalysisExecutive - Root of the analysis packages with the project's
*                       entry point.
* - ParallelTypeAnal  - ParallelTypeAnalysis, TypeAnal, TableMerge,
*                       and EventHandler classes
* - IFileMgr          - IFileMgr interface
* - FileMgr           - FileMgr, AnalFileEventHandler, AnalDirEventHandler,
*                       and AnalDoneEventHandler classes
* - Task              - Task class
* - ThreadPool        - ThreadPool class
* - Logger            - Logger and StaticLogger<size_t>
* - BlockingQueue     - BlockingQueue<T> used by the three previous packages
* - Utilities         - Converter<T> has toString and toValue methods,
*                       and several other helper classes
* - DepAnal
* - TupeAnal
*/
/*
 * Maintenance History:
 * --------------------
 * ver 1.0 : 3 May 2016
 * - first release
 */
#include "ParallelTypeAnal.h"
#include "../Utilities/Utilities.h"
#include <string>
#include <vector>
#include <iostream>

using namespace Utilities;
using Utils = StringHelper;

class AnalysisExecutive
{
public:
  using Path = std::string;
  using Pattern = std::string;
  using Patterns = std::vector<Pattern>;

  bool parseCommandLine(int argc, char* argv[]);
  void doAnalysis();
private:
  Path path_;
  Patterns patterns_;
};

bool AnalysisExecutive::parseCommandLine(int argc, char* argv[])
{
	if (argc == 1)
	{
		path_ = "../Parser";
		patterns_.push_back("*.h");
		patterns_.push_back("*.cpp");
		return true;
	}
	else if (argc == 2)
	{
		path_ = argv[1];
		patterns_.push_back("*.h");
		patterns_.push_back("*.cpp");
		return true;
	}
	else
	{
		path_ = argv[1];
		for (int i = 2; i < argc; ++i)
			patterns_.push_back(argv[i]);
		return true;
	}
}

void AnalysisExecutive::doAnalysis()
{
  Show::write("\n  Pass #1 starting");
  Show::write("\n  numFilesProcessed will be displayed as zero until FileMgr\n  notifies TableMerge of the number of files processed\n");
  ParallelTypeAnalysis exec(path_);
  for (auto pattern : patterns_)
    exec.addPattern(pattern);
  exec.start();
  exec.wait();
  Show::write("\n  Pass #1 - Type Analysis complete\n");
  
  Show::write("\n  Pass #2 starting");
  exec.startDep();
 
  exec.print();
  exec.stop(); 
  Show::stop();
  DebugLog::stop();
}

#ifdef TEST_ANALYSIS

int main(int argc, char* argv[])
{

  Utils::Title("Testing MockDepAnal");

  Show::attach(&std::cout);
  Show::start();
  DebugLog::attach(&std::cout);

  AnalysisExecutive exec;
  if(!exec.parseCommandLine(argc, argv))
    return 1;
  exec.doAnalysis();
}
#endif

/////////////////////////////////////////////////////////////////////////
// ParallelTypeAnal.cpp - Does Pass 1								   //
// Version 1.0                                                         //
// Platform:      MacBook Pro, Windows 10 Pro				           //	
// Author:		  Philip Geramian, Syracuse University			       //
// Source:		  Jim Fawcett										   //
/////////////////////////////////////////////////////////////////////////

#include "ParallelTypeAnal.h"
#include "../Utilities/Utilities.h"

//----< initialize TableMerge and its done event >-------------------

TableMerge::TableMerge(BlockingQueue<TypeAnal::Table>& tableQ)
  : tableQ_(tableQ), dnEvt_(this)
{
  future_ = promise_.get_future();  // needed for wait function
}
//----< register done event handler with FileMgr >-------------------

void TableMerge::registerForDone(FileManager::IFileMgr* pFileMgr)
{
  pFileMgr->regForDone(&dnEvt_);
  numFilesProcessed_.store((size_t)0);
}
//----< display progress >-------------------------------------------

void TableMerge::showProgress(std::atomic<size_t>& numFilesProcessed, size_t numTablesProcessed)
{
  Show::write(
    "\n  tm - numFilesProcessed = " +
    Utilities::Converter<size_t>::toString(numFilesProcessed.load())
    );
  Show::write(
    "\n  tm - numTablesProcessed = " +
    Utilities::Converter<size_t>::toString(numTablesProcessed)
    );
}
//----< pretend to merge symbol tables >-----------------------------

std::vector<TypeAnal::Table> TableMerge::merge()
{
  TypeAnal::Table table;
  numTablesProcessed_ = 0;
  while (true)
  {
    // The test, below, prevents merge from blocking on table queue after all the tables
    // have been processed.  It assumes that each file analysis will generate a table,
    // even if empty.

    if ((numFilesProcessed_.load() == 0) || (numTablesProcessed_ < numFilesProcessed_.load()))
    {
      ++numTablesProcessed_;
      showProgress(numFilesProcessed_, numTablesProcessed_);
      table = tableQ_.deQ();
      merged_.push_back(table);
	  //std::cout << "File: " << table.file << "\n";
      if (table.file == "quit")
      {
        while (numFilesProcessed_.load() == 0)  // spin until done event propagates here
          ::Sleep(10);
        showProgress(numFilesProcessed_, numTablesProcessed_);
      }
    }
    else
    {
      Show::write("\n  releasing future");
      promise_.set_value(numFilesProcessed_);  // unblocks future
      break;
    }
  }
  return merged_;
}

void TableMerge::print()
{ // output the merged table to the console
	for (size_t i = 0; i < merged_.size(); ++i)
	{
		std::cout << "\n \n";
		TypeAnal::Table temp = merged_[i];

		std::cout << "File : " << temp.file << "\n";
		std::cout << "Types defined: \n";

		for (size_t i = 0; i < temp.typesDefined.size(); ++i)
		{
			std::cout << "\t" << temp.typesDefined[i] << "\n";
		}

		std::cout << "Types used: \n";

		for (size_t i = 0; i < temp.typesUsed.size(); ++i)
		{
			std::cout << "\t" << temp.typesUsed[i] << "\n";
		}

		std::cout << "Depends on: \n";

		for (size_t i = 0; i < temp.dependencies.size(); ++i)
		{
			std::cout << "\t" << temp.dependencies[i] << "\n";
		}
	}
}

//----< called by MergeDoneEventHandler::execute(...) >------------

void TableMerge::done(size_t numFilesProcessed)
{
  Show::write("\n------- done event handled in TableMerge -------");
  numFilesProcessed_.store(numFilesProcessed);
}
//----< ParallelTypeAnalysis calls to wait for merge to finish >------

size_t TableMerge::wait()
{
  size_t numFiles = future_.get();
  return numFiles;
}
//----< initlze Exec and TypeAnal, TableMerge, and evnt hndlrs >-----

ParallelTypeAnalysis::ParallelTypeAnalysis(const Path& path)
	: ta_(tableQueue_), tm_(tableQueue_), fevt_(this), devt_(this), dnEvt_(this), da_(tableQueue_)
{
  FileManager::FileMgrFactory factory;
  pFileMgr_ = factory.create(path);
  pFileMgr_->regForFiles(&fevt_);
  pFileMgr_->regForDirs(&devt_);
  pFileMgr_->regForDone(&dnEvt_);
  tm_.registerForDone(pFileMgr_);
}
//----< add to patterns collection >---------------------------------

void ParallelTypeAnalysis::addPattern(const Pattern& pattern)
{
  pFileMgr_->addPattern(pattern);
}
//----< start up the processing pipeline >---------------------------

void ParallelTypeAnalysis::start()
{
  tmco_ = [this]() -> bool
  {
    Show::write("\n  starting table merge");
    tm_.merge();
    return true;
  };
  task_.workItem(tmco_);

  fsco_ = [this]()
  {
    Show::write("\n  starting file search");
    pFileMgr_->search();
    return true;
  };
  task_.workItem(fsco_);
}

void ParallelTypeAnalysis::startDep()
{ // perform dependancy analysis
	typeTable = tm_.getMerged();
	da_.giveTypeAnalysis(typeTable);
	Show::write("\n  starting dependency search");
		
	for (size_t fileIndex = 0; fileIndex < typeTable.size(); ++fileIndex)
	{
		da_.doDepAnal(typeTable[fileIndex]);

			
	}

	
}
//----< shut down the threadpool >-----------------------------------

void ParallelTypeAnalysis::stop()
{
  CallObj exit = []() -> bool { return false; };
  task_.workItem(exit);
}
//----< wait for the merge process to finish >-----------------------

void ParallelTypeAnalysis::wait()
{
  tm_.wait();
}
//----< handler for file events from FileMgr >-----------------------

void ParallelTypeAnalysis::file(const File& file)
{
  DebugLog::write("\n  analyzing file \"" + file + "\"");
  File fileSpec = path_ + "\\" + file;
  taco_ = [this, fileSpec]() -> bool {
    ta_.doTypeAnal(fileSpec);
    return true;
  };

  task_.workItem(taco_);  // threadpool will make copy
}
//----< handler for dir events from FileMgr >------------------------

void ParallelTypeAnalysis::dir(const Path& path)
{
  path_ = path;
}
//----< handler for done event from FileMgr, not used >--------------

void ParallelTypeAnalysis::done(size_t numFilesProcessed)
{
  fileSearchDone = true;
  TypeAnal::Table temp;
  temp.file = "quit";

  tableQueue_.enQ(temp);
}

void AnalFileEventHandler::execute(const std::string& file)
{
  pExec_->file(file);
}

void AnalDirEventHandler::execute(const std::string& dir)
{
  pExec_->dir(dir);
}

void AnalDoneEventHandler::execute(size_t numFilesProcessed)
{
  pExec_->done(numFilesProcessed);
}

void MergeDoneEventHandler::execute(size_t numFilesProcessed)
{
  pTM_->done(numFilesProcessed);
}

void ParallelTypeAnalysis::print()
{
	da_.print();
}

#ifdef TEST_PARALLELTYPEANAL

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("Testing MockDepAnal");

  Show::attach(&std::cout);
  Show::start();
  DebugLog::attach(&std::cout);

  std::string msg = "\n  numFilesProcessed will be displayed as zero until FileMgr";
  msg += "\n  notifies TableMerge of the number of files processed\n";
  Show::write(msg);
  ParallelTypeAnalysis exec("../..");
  exec.addPattern("*.h");
  exec.addPattern("*.cpp");
  exec.start();
  exec.wait();  // wait for table merge to complete
  //exec.print();
  exec.stop();  // shut down thread pool - in full solution won't do this
                // until the end of Pass #2
  Show::stop();
  DebugLog::stop();
}
#endif

#ifndef PARALLELTYPEANAL_H
#define PARALLELTYPEANAL_H
/////////////////////////////////////////////////////////////////////////
// ParallelTypeAnal.h - Does Pass 1									   //
// Version 1.0                                                         //
// Platform:      MacBook Pro, Windows 10 Pro				           //	
// Author:		  Philip Geramian, Syracuse University			       //
// Source:		  Jim Fawcett										   //
/////////////////////////////////////////////////////////////////////////
#include <string>
#include <iostream>
#include <sstream>
#include <future>
#include <atomic>
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../FileMgr/IFileMgr.h"
#include "../FileMgr/FileMgr.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../Tasks/Task.h"
#include "../TypeAnal/TypeAnal.h"
#include "../DependancyAnal/DepAnal.h"

using Show = StaticLogger<0>;
using DebugLog = StaticLogger<1>;


/////////////////////////////////////////////////////////////////////
// TableMerge class
// - Responsible for merging type tables as they arrive in table queue
// - For complete solution this becomes package TableMerge
//
class TableMerge;

class MergeDoneEventHandler : public FileManager::IDoneEventHandler
{
public:
  MergeDoneEventHandler(TableMerge* pTM) : pTM_(pTM) {}
  void execute(size_t numFilesProcessed);
private:
  TableMerge* pTM_;
};

class TableMerge
{
public:
  TableMerge(BlockingQueue<TypeAnal::Table>& tableQ);
  void registerForDone(FileManager::IFileMgr* pFileMgr);
  std::vector<TypeAnal::Table> merge();
  void done(size_t numFilesProcessed);
  size_t wait();
  void print();
  std::vector<TypeAnal::Table> getMerged() { return merged_; };
  void clearMerged() { merged_.clear(); };
private:
  void showProgress(std::atomic<size_t>& numFilesProcessed, size_t numTablesProcessed);
  BlockingQueue<TypeAnal::Table>& tableQ_;
  std::vector<TypeAnal::Table> merged_;
  size_t numTablesCreated = 0;
  FileManager::IFileMgr* pFileMgr_;
  MergeDoneEventHandler dnEvt_;
  std::atomic<size_t> numFilesProcessed_;  // shared by FileMgr and TableMerge
  size_t numTablesProcessed_ = 0;
  std::future<size_t> future_;
  std::promise<size_t> promise_;
};

/////////////////////////////////////////////////////////////////////
// Analysis Event Handlers

class ParallelTypeAnalysis;

class AnalFileEventHandler : public FileManager::IFileEventHandler
{
public:
  AnalFileEventHandler(ParallelTypeAnalysis* pExec) : pExec_(pExec) {}
  void execute(const std::string& file);
private:
  ParallelTypeAnalysis* pExec_;
};

class AnalDirEventHandler : public FileManager::IDirEventHandler
{
public:
  AnalDirEventHandler(ParallelTypeAnalysis* pExec) : pExec_(pExec) {}
  void execute(const std::string& dir);
private:
  ParallelTypeAnalysis* pExec_;
};

class AnalDoneEventHandler : public FileManager::IDoneEventHandler
{
public:
  AnalDoneEventHandler(ParallelTypeAnalysis* pExec) : pExec_(pExec) {}
  void execute(size_t numFilesProcessed);
private:
  ParallelTypeAnalysis* pExec_;
};

/////////////////////////////////////////////////////////////////////
// ParallelTypeAnalysis class
// - Responsible for creating FileManager, TypeAnal, and TableMerge
// - Runs FileMgr::search(), TypeAnal::doTypeAnal(), and TableMerge::merge()
//   on ThreadPool threads, using the Task class
//
class ParallelTypeAnalysis
{
public:
  using File = std::string;
  using Path = std::string;
  using Pattern = std::string;
  using CallObj = std::function<bool()>;

  ParallelTypeAnalysis(const Path& path);
  void addPattern(const Pattern& pattern);
  void start();
  void stop();
  void wait();
  void file(const File& file);
  void dir(const Path& path);
  void done(size_t numFilesProcessed);
  void print();
  void startDep();
private:
  TypeAnal ta_;
  DepAnal da_;
  TableMerge tm_;
  BlockingQueue<TypeAnal::Table> tableQueue_;
  Path path_;
  Task<8> task_;
  FileManager::IFileMgr* pFileMgr_;
  AnalFileEventHandler fevt_;
  AnalDirEventHandler devt_;
  AnalDoneEventHandler dnEvt_;
  bool fileSearchDone = false;
  CallObj tmco_;  // table merge
  CallObj taco_;  // type anal
  CallObj fsco_;  // file search
  std::vector<TypeAnal::Table> typeTable;
};
#endif
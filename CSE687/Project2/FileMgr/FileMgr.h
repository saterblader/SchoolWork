#ifndef FILEMGR_H
#define FILEMGR_H
/////////////////////////////////////////////////////////////////////
// FileMgr.h - find files matching specified patterns              //
//             on a specified path                                 //
// ver 2.1														   //
//                                                                 //
//  Lanaguage:     Visual C++ 2015                                 //
//  Platform:      Macbook Pro Windows 10			               //
//  Application:   Prototype for CSE687 Pr2, Sp16                  //
//  Author:        Philip Geramian, Syracuse University			   //
//                 pdgerami@syr.edu						           //
//  Source:        Jim Fawcett, CST 2-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
 * ver 2.1 : 15 Mar 2016
 * - datastore now stores full path
 * ver 2.0 : 12 Mar 2016
 * - fixes bug in directory recursion in find(path)
 * - reduces scope of for loop in find for efficiency
 * ver 1.0 : 19 Feb 2016
 * - first release
 */
#include "FileSystem.h"
#include "../DataStore/DataStore.h"
#include <iostream>

class FileMgr
{
public:
  using iterator = DataStore::iterator;
  using patterns = std::vector<std::string>;

  FileMgr(const std::string& path, DataStore& ds) : path_(path), store_(ds)
  {
    patterns_.push_back("*.*");
  }

  void addPattern(const std::string& patt)
  {
    if (patterns_.size() == 1 && patterns_[0] == "*.*")
      patterns_.pop_back();
    patterns_.push_back(patt);
  }

  void search()
  {
    find(path_);
  }

  void find(const std::string& path)
  {
    std::string fpath = FileSystem::Path::getFullFileSpec(path);
    //---------------------------------------------------------
    // The statement above is not necessary, but helps to
    // make the processing clearer.  To show that, comment
    // it out and uncomment the following line.
    //
    // std::string fpath = path;
    //
    // Remove the std::cout statements below after you're 
    // convinced that everything works as it should.
    //---------------------------------------------------------

    //std::cout << "\n  ++ " << fpath;
    for (auto patt : patterns_)  // the scope of this for loop was
    {                            // changed to improve efficiency
      std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
      for (auto f : files)
      {
        //std::cout << "\n  --   " << f;
		  std::string full = fpath +'\\'+ f;
        store_.save(full);
      }
    }
    std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
    for (auto d : dirs)
    {
      if (d == "." || d == "..")
        continue;
      std::string dpath = fpath + "\\" + d;  // here's the fix
      find(dpath);
    }
  }
private:
  std::string path_;
  DataStore& store_;
  patterns patterns_;
};

#endif
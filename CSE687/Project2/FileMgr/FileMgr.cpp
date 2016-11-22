/////////////////////////////////////////////////////////////////////
// FileMgr.cpp - find files matching specified patterns            //
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

#include "FileMgr.h"
#include "../DataStore/DataStore.h"
#include <iostream>

#ifdef TEST_FILEMGR

int main()
{
  std::cout << "\n  Testing FileMgr";
  std::cout << "\n =================";

  DataStore ds;
  FileMgr fm("..", ds);
  //fm.addPattern("*.h");
  //fm.addPattern("*.c*");
  //fm.addPattern("*.partial");
  fm.search();

  std::cout << "\n\n  contents of DataStore";
  std::cout << "\n -----------------------";
  for (auto fs : ds)
  {
    std::cout << "\n  " << fs;
  }
  std::cout << "\n\n";
  return 0;
}
#endif

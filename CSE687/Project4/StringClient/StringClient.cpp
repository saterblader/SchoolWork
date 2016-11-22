/////////////////////////////////////////////////////////////////////////
// StringClient.cpp - File sending client						       //
//                                                                     //
// By: Philip Geramian pdgerami@syr.edu								   //
// CSE687 - Object Oriented Design, Spring 2016				           //
// Source: Jim Fawcett												   //
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, MacBook Pro, Windows 10 Pro        //
/////////////////////////////////////////////////////////////////////////

/*
 * This package implements a client that sends files 
 * to a server that saves them to a directory and does
 * type analysis on them.
 */

 /*
 * Required Files:
 *  StringClient.cpp, StringServer.cpp
 *  Sockets.h, Sockets.cpp,
 *	Cppll-BlockingQueue.h,
 *  Utilities.h, Utilities.cpp,
 *	FileSystem.h, FileSystem.cpp
 */
#include "../Sockets/Sockets.h"
#include "../Utilities/Utilities.h"
#include "../FileSystem/FileSystem.h"
#include "StringClient.h"
#include <string>
#include <iostream>
#include <vector>

using namespace Utilities;

void StringClient::execute(std::vector<std::string> ds)
{
  std::cout <<"Sending files...\n";
  try
  {
    SocketSystem ss;
    SocketConnecter si;
    while (!si.connect("localhost", 8080))
    {
		std::cout << "\n client waiting to connect";
      ::Sleep(100);
    }
	for (auto ReadFilePath : ds)
	{
		if (!FileSystem::File::exists(ReadFilePath))
		{
			std::cout << "\nInput doesn't exist" << std::endl;
			return;
		}
		FileSystem::File ReadFile(ReadFilePath);
		ReadFile.open(FileSystem::File::in, FileSystem::File::binary);
		if (!ReadFile.isGood())
		{
			std::cout << "Error while opening input file" << std::endl;
			return;
		}

		if (ReadFile.isGood())
		{
			std::string msg;
			FileSystem::FileInfo RdFile(ReadFilePath);
			size_t filesize = RdFile.size();
			const int BufferLength = 1024;
			char buffer[BufferLength];
			size_t ReadLength;
			ReadLength = ReadFile.getBuffer(BufferLength, buffer);
			char http[1000],sent[1000];
			size_t lastslash =ReadFilePath.find_last_of("/\\");
			std::string filename = ReadFilePath.substr(lastslash + 1);
			sprintf_s(http, "POST:%s:%zu", filename.c_str(), filesize);
			std::cout << "\n";
			sprintf_s(sent, "Sending %s...", ReadFilePath.c_str());
			std::cout << sent;
			si.sendString(http);
			while (true)
			{
				si.sendString(buffer);
				if (ReadLength < 1024)
				{
					ReadFile.close();
					break;
				}
				ReadLength = ReadFile.getBuffer(BufferLength, buffer);
			}
			if (ReadFile.isGood())
			{
				std::cout << "Error while closing read file" << std::endl;
				return;
			}
			std::cout << "\n";
		}
	}
		si.sendString("quit");
		std::cout << "\n  All done folks";
	
  }
  catch (std::exception& exc)
  {
    std::cout<<"\n  Exeception caught: ";
    std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
	std::cout <<exMsg;
  }
}


#ifdef TEST_STRINGCLIENT
int main()
{
  Show::title("Test File Sending");

  StringClient c1;
  std::vector<std::string> ds;
  ds.push_back("FileSystem.h");
  ds.push_back("FileSystem.cpp");
  /*std::thread t1(
    [&]() { c1.execute(ds); }
  );
  t1.join();*/
}
#endif
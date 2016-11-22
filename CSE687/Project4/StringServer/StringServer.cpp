/////////////////////////////////////////////////////////////////////////
// StringServer.cpp - File Reciveing server						       //
//                                                                     //
// By: Philip Geramian pdgerami@syr.edu								   //
// CSE687 - Object Oriented Design, Spring 2016				           //
// Source: Jim Fawcett												   //
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, MacBook Pro, Windows 10 Pro        //
// Version 1.0														   //
/////////////////////////////////////////////////////////////////////////
/*
* Required Files:
*   StringClient.cpp,
*   Sockets.h, Sockets.cpp, 
*	Cppll-BlockingQueue.h,
*   Utilities.h, Utilities.cpp,
*	FileSystem.h, FileSystem.cpp
*/
#include "../Sockets/Sockets.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../FileSystem/FileSystem.h"
#include <string>
#include <iostream>
#include <ctime>

using Show = StaticLogger<1>;

class ClientHandler
{
public:
  void operator()(Socket& socket_);
};

void ClientHandler::operator()(Socket& socket_)
{
	char date[19],time[9];
	_strdate_s(date);
	_strtime_s(time);
	date[2] = '_';
	date[5] = '_';
	date[8] = '_';
	time[2] = '_';
	time[5] = '_';
	for (size_t i = 0; i < 9; i++)
	{
		date[i + 9] = time[i];
	}
	FileSystem::Directory dir;
	dir.setCurrentDirectory("..\\");
	dir.create(date);
	dir.setCurrentDirectory(date);
  while (true)
  {
	  std::string msg;
	  msg = socket_.recvString();
	  if (msg == "quit")
		  break;
	  size_t first = msg.find(':');
	  std::string type = msg.substr(0, first);
	  std::string temp = msg.substr(first+1, msg.length() - 1);
	  size_t second = temp.find(':');
	  std::string WriteFilePath = msg.substr(first+1, second);
	  size_t length =atoi(temp.substr(second+1, msg.length()).c_str());

	  if (FileSystem::File::exists(WriteFilePath)) 
	  {
		  std::cout << "\nOutput file " << WriteFilePath << " already exist" << std::endl;
		  return;
	  }
	  FileSystem::File WriteFile(WriteFilePath);
	  WriteFile.open(FileSystem::File::out, FileSystem::File::binary);
	  if (!WriteFile.isGood())
	  {
		  std::cout << "\nError while opening output file" << std::endl;
		  return;
	  }
	  char* buffer;
	  size_t ReadLength=length;

	  while (true)
	  {
		  if (ReadLength < 1024)
		  {
			  msg = socket_.recvString();
			  buffer = (char*)msg.c_str();
			  WriteFile.putBuffer(ReadLength, buffer);
			  ReadLength = 0;
			  WriteFile.close();
			  break;
		  }
		  msg = socket_.recvString();
		  buffer = (char*)msg.c_str();
		  WriteFile.putBuffer(1024, buffer);
		  ReadLength = ReadLength - 1024;
	  }
    Show::write("\n Server received File\n " + WriteFilePath + "\n");
  }
 dir.setCurrentDirectory("..\\");
}

//----< test stub >--------------------------------------------------

int main()
{
  Show::attach(&std::cout);
  Show::start();
  Show::title("\n  File Server Started");
  try
  {
    SocketSystem ss;
    SocketListener sl(8080, Socket::IP6);
    ClientHandler cp;
    sl.start(cp);
    Show::write("\n --------------------\n  press key to exit: \n --------------------");
    std::cout.flush();
    std::cin.get();
  }
  catch (std::exception& exc)
  {
    Show::write("\n  Exeception caught: ");
    std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
    Show::write(exMsg);
  }
}
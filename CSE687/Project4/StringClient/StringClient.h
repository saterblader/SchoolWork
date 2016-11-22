/////////////////////////////////////////////////////////////////////////
// StringServer.h - File Reciveing server						       //
//                                                                     //
// By: Philip Geramian pdgerami@syr.edu								   //
// CSE687 - Object Oriented Design, Spring 2016				           //
// Source: Jim Fawcett												   //
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, MacBook Pro, Windows 10 Pro        //
// Version 1.0														   //
/////////////////////////////////////////////////////////////////////////
#include "../Sockets/Sockets.h"
#include "../Utilities/Utilities.h"
#include "../FileSystem/FileSystem.h"
#include <string>
#include <iostream>
#include <vector>
/////////////////////////////////////////////////////////////////////
// ClientCounter creates a sequential number for each client
//
class ClientCounter
{
public:
	ClientCounter() { ++clientCount; }
	size_t count() { return clientCount; }
private:
	static size_t clientCount;
};
/////////////////////////////////////////////////////////////////////
// StringClient class

class StringClient
{
public:
	void execute(std::vector<std::string> ds);
};
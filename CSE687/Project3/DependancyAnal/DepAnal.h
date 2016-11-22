#ifndef DEPANAL_H
#define DEPANAL_H
/////////////////////////////////////////////////////////////////////
//  DepAnal.h Does Dependancy Analysis							   //
//  Version 1                                                      //
//  Platform:      MacBook Pro, Windows 10 Pro				       //	
//																   //
//  Author:		   Philip Geramian, Syracuse University			   //
/////////////////////////////////////////////////////////////////////

#include "../TypeAnal/TypeAnal.h"

class DepAnal
{
public:
	DepAnal(BlockingQueue<TypeAnal::Table>& tableQ) : _tableQueque(tableQ) {};
	~DepAnal() {};
	void doDepAnal(TypeAnal::Table& file);
	void giveTypeAnalysis(std::vector<TypeAnal::Table> typeTables);
	void print();

private:
	std::string findTypeDef(std::string type);
	std::vector<TypeAnal::Table> typeAnalysis;
	BlockingQueue<TypeAnal::Table>& _tableQueque;

};




#endif
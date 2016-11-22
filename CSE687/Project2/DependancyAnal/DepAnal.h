#ifndef DEPANAL_H
#define DEPANAL_H

#include "../TypeAnal/TypeAnal.h"

class DepAnal
{
public:
	DepAnal(BlockingQueue<TypeAnal::Table>& tableQ) : tableQ_(tableQ) {};
	~DepAnal() {};
	void doDepAnal(TypeAnal::Table& file);
	void giveTypeAnalysis(std::vector<TypeAnal::Table> typeTables);
	void print();

private:
	std::string findTypeDef(std::string type);
	std::vector<TypeAnal::Table> typeAnalysis;
	BlockingQueue<TypeAnal::Table>& tableQ_;

};




#endif
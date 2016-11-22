/////////////////////////////////////////////////////////////////////
//  DepAnal.cpp Does Dependancy Analysis						   //
//  Version 1                                                      //
//  Platform:      MacBook Pro, Windows 10 Pro				       //	
//																   //
//  Author:		   Philip Geramian, Syracuse University			   //
/////////////////////////////////////////////////////////////////////
#include "DepAnal.h"

void DepAnal::doDepAnal(TypeAnal::Table& file)
{
	for (size_t i = 0; i < file.typesUsed.size(); ++i)
	{
		std::string dependency = this->findTypeDef(file.typesUsed[i]);
		if (dependency != "DNE")
			file.dependencies.push_back(dependency);	
	}
	_tableQueque.enQ(file);
}

std::string DepAnal::findTypeDef(std::string type)
{
	for (size_t i = 0; i < typeAnalysis.size(); ++i)
	{
		for (size_t j = 0; j < typeAnalysis[i].typesDefined.size(); ++j)
			if (typeAnalysis[i].typesDefined[j] == type)
				return typeAnalysis[i].file;
	}
	return "DNE";
}

void DepAnal::giveTypeAnalysis(std::vector<TypeAnal::Table> typeTables)
{
	typeAnalysis = typeTables;
}

void DepAnal::print()
{
	for (size_t i = 0; i < _tableQueque.size(); ++i)
	{
		TypeAnal::Table temp = _tableQueque.deQ();
		std::cout << "\n \n File : " << temp.file << std::endl;
		std::cout << "Types defined: \n";

		for (size_t i = 0; i < temp.typesDefined.size(); ++i)
		{
			std::cout << "\t" << temp.typesDefined[i] << std::endl;
		}

		std::cout << "Types used: \n";

		for (size_t i = 0; i < temp.typesUsed.size(); ++i)
		{
			std::cout << "\t" << temp.typesUsed[i] << std::endl;
		}

		std::cout << "Depends on: \n";

		for (size_t i = 0; i < temp.dependencies.size(); ++i)
		{
			std::cout << "\t" << temp.dependencies[i] << std::endl;
		}

		std::cout << "-----------------------------------------------";
	}
}



#ifdef TEST_DEPANAL
int main()
{
	BlockingQueue<TypeAnal::Table> _q;
	TypeAnal typeDetect(_q);
	std::vector<TypeAnal::Table> typeTables;
	DepAnal depDetect(_q);

	typeDetect.doTypeAnal("../Parser/ConfigureParser.h");
	typeDetect.doTypeAnal("../Parser/ActionsAndRules.h");
	typeDetect.doTypeAnal("../Parser/Parser.h");

	for (int i = 0; i < 3; ++i)
	{
		typeTables.push_back(_q.deQ());
	}

	depDetect.giveTypeAnalysis(typeTables);

	for (int i = 0; i < 3; ++i)
	{
		depDetect.doDepAnal(typeTables[i]);
	}

	depDetect.print();
}
#endif



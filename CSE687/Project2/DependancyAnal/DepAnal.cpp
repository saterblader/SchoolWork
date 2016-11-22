#include "DepAnal.h"



void DepAnal::doDepAnal(TypeAnal::Table& file)
{// scanmerged table for dependencies
	for (size_t i = 0; i < file.typesUsed.size(); ++i)
	{
		std::string dependency = this->findTypeDef(file.typesUsed[i]);

		if (dependency != "DNE")
		{
			file.dependencies.push_back(dependency);
		}	
	}
	tableQ_.enQ(file);
}

std::string DepAnal::findTypeDef(std::string type)
{// find wehre the type is defined
	for (size_t i = 0; i < typeAnalysis.size(); ++i)
	{
		for (size_t j = 0; j < typeAnalysis[i].typesDefined.size(); ++j)
		{
			if (typeAnalysis[i].typesDefined[j] == type)
				return typeAnalysis[i].file;
		}
	}
	return "DNE";
}

void DepAnal::giveTypeAnalysis(std::vector<TypeAnal::Table> typeTables)
{
	typeAnalysis = typeTables;
}

void DepAnal::print()
{ // print types declared in a file
	for (size_t i = 0; i < tableQ_.size(); ++i)
	{
		TypeAnal::Table temp = tableQ_.deQ();

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



#ifdef TEST_DEPANAL
int main()
{
	BlockingQueue<TypeAnal::Table> q_;

	TypeAnal typeDetect(q_);
	std::vector<TypeAnal::Table> typeTables;
	DepAnal depDetect(q_);

	typeDetect.doTypeAnal("../Parser/ConfigureParser.h");
	typeDetect.doTypeAnal("../Parser/ActionsAndRules.h");
	typeDetect.doTypeAnal("../Parser/Parser.h");

	for (int i = 0; i < 3; ++i)
	{
		typeTables.push_back(q_.deQ());
	}

	depDetect.giveTypeAnalysis(typeTables);

	for (int i = 0; i < 3; ++i)
	{
		depDetect.doDepAnal(typeTables[i]);
	}

	depDetect.print();
}
#endif // TEST_DEPANAL



/////////////////////////////////////////////////////////////////////
//  TypeAnal.cpp Does Type Analysis							       //
//  Version 1                                                      //
//  Platform:      MacBook Pro, Windows 10 Pro				       //	
//																   //
//  Author:		   Philip Geramian, Syracuse University			   //
/////////////////////////////////////////////////////////////////////

#include "TypeAnal.h"
#include <windows.h>

using namespace Scanner;

TypeAnal::TypeAnal(BlockingQueue<Table>& tableQ) : _tablequeue(tableQ)
{}

void TypeAnal::doTypeAnal(std::string fileName)
{
	Table newTable;
	newTable.file = fileName;
	TypeParser* pTypeParser = new TypeParser;
	Parser* pParser = pTypeParser->Build();
	pTypeParser->Attach(fileName);

	// parse the file
	while (pParser->next())
		pParser->parse();

	//pull the types
	newTable.typesDefined = pTypeParser->getTypesDefined();
	newTable.typesUsed = pTypeParser->getTypesUsed();

	// push to queue
	_tablequeue.enQ(newTable);
}


void TypeAnal::print()
{
	for (size_t i = 0; i < _tablequeue.size(); ++i)
	{
		Table temp = _tablequeue.deQ();

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
	}
}


TypeParser::~TypeParser()
{
	delete pBeginningOfScope;
	delete pFunctionDefinition;
	delete pDeclaration;
	delete pTypeDefinition;
	delete pShowDeclaration;
	delete pTypeDeclaration;
	delete pExecutable;
	delete pControlStatement;
	delete pParser;
	delete pSemi;
	delete pToker;
	pIn->close();

	if (pIn != 0)
		delete pIn;
}

bool TypeParser::Attach(const std::string& name, bool isFile)
{
	if (pToker == 0)
		return false;

	if (pIn != 0)
		delete pIn;

	pIn = new std::ifstream(name);
	if (!pIn->good())
		return false;
	return pToker->attach(pIn);
}

bool TypeParser::Detach()
{
	if (pToker == 0)
		return false;

	delete pToker;
	pToker = new Toker;
	return true;
}

Parser* TypeParser::Build()
{
	try
	{
		pToker = new Toker;
		pToker->returnComments(false);
		pSemi = new SemiExp(pToker);
		pParser = new Parser(pSemi);

		pBeginningOfScope = new BeginningOfScope();
		pParser->addRule(pBeginningOfScope);

		pFunctionDefinition = new FunctionDefinition;
		pParser->addRule(pFunctionDefinition);

		pControlStatement = new ControlStatement;
		pParser->addRule(pControlStatement);

		pDeclaration = new Declaration;
		pParser->addRule(pDeclaration);		
		pTypeDeclaration = new TypeDeclaration;
		pDeclaration->addAction(pTypeDeclaration);
		pShowDeclaration = new ShowDeclaration;

		pClassDefinition = new ClassDefinition;
		pParser->addRule(pClassDefinition);
		pTypeDefinition = new TypeDefinition;
		pClassDefinition->addAction(pTypeDefinition);

		pExecutable = new Executable;
		pParser->addRule(pExecutable);

		return pParser;
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n  " << ex.what() << "\n\n";
		return 0;
	}
}

#ifdef TEST_TYPEANAL

int main()
{
	BlockingQueue<TypeAnal::Table> _q;
	TypeAnal typeDetect(_q);
	typeDetect.doTypeAnal("TypeAnal.h");
	typeDetect.print();
}
#endif

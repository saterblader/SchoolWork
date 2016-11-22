#ifndef TYPEANAL_H
#define TYPEANAL_H
/////////////////////////////////////////////////////////////////////
//  TypeAnal.h Does Type Analysis							       //
//  Version 1                                                      //
//  Platform:      MacBook Pro, Windows 10 Pro				       //	
//																   //
//  Author:		   Philip Geramian, Syracuse University			   //
/////////////////////////////////////////////////////////////////////

#include <string>
#include "../Parser/ConfigureParser.h"
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"

class TypeParser;


class TypeAnal
{
public:

	struct Table
	{
		std::string file;
		std::vector<std::string> typesDefined;
		std::vector<std::string> typesUsed;
		std::vector<std::string> dependencies;
	};

	TypeAnal(BlockingQueue<Table>& tableQ);
	~TypeAnal() {};

	void doTypeAnal(std::string fileName);
	void print();

private:
	BlockingQueue<Table>& _tablequeue;

};

class TypeDefinition : public IAction
{
public:
	void doAction(ITokCollection*& pTc)
	{
		//std::cout << "\n checking if class";
		// if the declaration detects a class, save the type
		ITokCollection& tc = *pTc;
		if (tc.find("class") < tc.length() )
		{
			types.push_back(tc[tc.find("class") + 1]);
		}
	}


	std::vector<std::string> getTypes()
	{
		return types;
	}

private:
	// vector containing all of the types that are declared in a file
	std::vector<std::string> types;
};

class TypeDeclaration : public IAction
{
public:
	bool isNativeType(ITokCollection& tc)
	{
		std::vector<std::string> nativeTypes = {"int", "char", "std", "double", "float", "size_t", "class",
		"bool", "using", "else", "delete", "new", "template", ">"};

		for (size_t i = 0; i < tc.length(); ++i)
		{
			for (size_t j = 0; j < nativeTypes.size(); ++j)
			{
				if (tc[i] == nativeTypes[j])
					return true;
			}
		}
		return false;
	};

	void doAction(ITokCollection*& pTc)
	{
		ITokCollection& tc = *pTc;
		if (!isNativeType(tc) && tc[tc.length() - 2] != ")")
		{
			typesUsed.push_back(tc[1]);
		}

	}

	std::vector<std::string> getTypes()
	{
		// get the types vector, cause I need that
		return typesUsed;
	}

private:
	std::vector<std::string> typesUsed;
	
};

class TypeParser
{
public:
	TypeParser() {};
	~TypeParser();
	bool Attach(const std::string& name, bool isFile = true);
	bool Detach();
	Parser* Build();
	std::vector<std::string> getTypesDefined() { return pTypeDefinition->getTypes();  };
	std::vector<std::string> getTypesUsed() { return pTypeDeclaration->getTypes(); };

private:

	std::ifstream* pIn = 0;
	Scanner::Toker* pToker = 0;
	Scanner::SemiExp* pSemi = 0;
	Parser* pParser = 0;


	BeginningOfScope* pBeginningOfScope;
	FunctionDefinition* pFunctionDefinition;
	EndOfScope* pEndOfScope;
	ControlStatement * pControlStatement;
	Declaration* pDeclaration;
	TypeDeclaration* pTypeDeclaration;
	ClassDefinition * pClassDefinition;
	ShowDeclaration * pShowDeclaration;
	TypeDefinition* pTypeDefinition;
	Executable* pExecutable;

};



#endif


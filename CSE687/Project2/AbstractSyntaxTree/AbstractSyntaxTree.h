#ifndef ABSTRACT_SYNTAX_TREE
#define ABSTRACT_SYNTAX_TREE
/////////////////////////////////////////////////////////////////////
//  AbstactSyntaxTree.h - manages abstract syntax tree             //
//  ver 1                                                          //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09			       //	
//																   //
//  Author:		   Ben Henry, Syracuse University				   //
//				   bwhenry@syr.edu								   //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

///////////////////////////////////////////////////////////////
// ScopeStack/AST element is application specific

struct element
{
	std::string type;
	std::string name;
	size_t startingLine;
	size_t endingLine = 0;
	std::string show()
	{
		std::ostringstream temp;
		temp << "(";
		temp << type;
		temp << ", ";
		temp << name;
		temp << ", ";
		temp << endingLine - startingLine + 1;
		temp << ")";
		return temp.str();
	}
};

class ASTNode
{
public:
	ASTNode();
	ASTNode(element scopeIn);
	ASTNode& AddChild(void);		// add an empty child node
	bool Populate(element &elementIn);	//populate scope in a node, return false if already populated
	int AssessComplexity(void);	// return the complexity of a function
	size_t GetChildCount(void);
	const ASTNode& GetNode();
	ASTNode* GetChild(size_t index);
	std::string GetName();
	std::string GetType() { return scope.type; };
	size_t GetLength();
	void PrintFunctionLength();
	~ASTNode();

private:
	element scope;
	std::vector<ASTNode*> children;
};


class AbstractSyntaxTree
{
public:
	AbstractSyntaxTree();
	~AbstractSyntaxTree();
	void showAST();
	void OpenNewNode();
	void PopulateNode(element& scope);
	void CloseNode();
	ASTNode* getRoot() { return pGlobalNameSpace; };



private:
	const ASTNode* GetReferenceToChild(ASTNode & node, size_t index);
	ASTNode * pGlobalNameSpace;
	std::vector<ASTNode*> buildStack;

};

template<typename CallObj>
void TreeWalk(ASTNode* pNode, CallObj& co, size_t indent = 0)
{
	++indent;
	ASTNode * pChild = 0;
	co(pNode, indent);
	if (pNode->GetChildCount() != 0)
	{
		for (size_t i = 0; i < pNode->GetChildCount(); ++i)
		{
			pChild = pNode->GetChild(i);
			TreeWalk(pChild, co, indent);
		}
	}
	--indent;
}

#endif
/////////////////////////////////////////////////////////////////////
//  AbstactSyntaxTree.cpp - manages abstract syntax tree           //
//  ver 1                                                          //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09			       //	
//																   //
//  Author:		   Ben Henry, Syracuse University				   //
//				   bwhenry@syr.edu								   //
//  Source:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include "AbstractSyntaxTree.h"
#include <vector>
#include <exception>



AbstractSyntaxTree::AbstractSyntaxTree()
{
	//Create origin node of tree
	
	element temp;
	temp.type = "global name space";
	temp.name = "";
	temp.startingLine = 0;
	pGlobalNameSpace = new ASTNode(temp);
	buildStack.push_back(pGlobalNameSpace);
}


AbstractSyntaxTree::~AbstractSyntaxTree()
{
	delete pGlobalNameSpace;
}

void AbstractSyntaxTree::OpenNewNode()
{// open a new node to be populated
	size_t index = buildStack.size();
	ASTNode& temp = buildStack[index - 1]->AddChild();
	buildStack.push_back(&temp);
}

void AbstractSyntaxTree::PopulateNode(element& scope)
{// populate the node on the top of the build stack, ie the most recently opened one
	size_t index = buildStack.size();
	buildStack[index - 1]->Populate(scope);
}

void AbstractSyntaxTree::CloseNode()
{// close node on top of build stack
	buildStack.pop_back();
}




const ASTNode* AbstractSyntaxTree::GetReferenceToChild(ASTNode& parent, size_t index)
{
	return parent.GetChild(index);
}

void ShowNode(ASTNode* pNode, size_t  indent)
{
	std::cout << std::string(2 * indent, ' ');
	std::cout << pNode->GetType() << ", " << pNode->GetName()
		<< ", #children = " << pNode->GetChildCount() << "\n";
}


void AbstractSyntaxTree::showAST()
{
	TreeWalk(pGlobalNameSpace, ShowNode);
}



ASTNode::ASTNode()
{

}


ASTNode::ASTNode(element scopeIn)
{
	scope = scopeIn;
}


ASTNode::~ASTNode()
{
} 
ASTNode& ASTNode::AddChild(void)
{// add empty child
	// called when a new scope is added to the scope stack
	ASTNode * NewNode = new ASTNode;
	children.push_back(NewNode);
	return *NewNode;
}

// fill an empty ASTNode with a scope element
// return true on success, false if node is already populated
bool ASTNode::Populate(element &elementIn)
{
	if (scope.endingLine == 0)
	{
		scope = elementIn;
		return true;
	}
	return false;
}

int ASTNode::AssessComplexity()
{// recursively step through the brances of the tree, starting at a node just under the GNS

	int complexity = 0;

	for (size_t i = 0; i < children.size(); ++i)
	{
		complexity += children[i]->AssessComplexity();
	}

	if (scope.type == "function")
	{
		std::cout << "Function: " << scope.name;
		std::cout << " Complexity: " << complexity + 1 << "\n";
	}

	return ++complexity;
}

size_t ASTNode::GetChildCount()
{
	return children.size();
}

const ASTNode& ASTNode::GetNode()
{
	return *this;
}

ASTNode* ASTNode::GetChild(size_t index)
{// get a reference to a child of a node
	return children[index];
}

std::string ASTNode::GetName()
{
	return scope.name;
}

size_t ASTNode::GetLength()
{
	return scope.endingLine - scope.startingLine + 1;
}

void ASTNode::PrintFunctionLength()
{
	if (scope.type == "function")
	{
		std::cout << "Function: " << scope.name;
		std::cout << " Length: " << scope.endingLine - scope.startingLine + 1 << "\n";
	}

	for (size_t i = 0; i < children.size(); ++i)
	{
		children[i]->PrintFunctionLength();
	}
	
}


#ifdef TEST_AST
// Abstract Syntax Tree test stub
int main()
{
	AbstractSyntaxTree AST;
	std::cout << "-----Testing Abstract Syntax Tree-----\n\n";
	element function1;
	function1.type = "function";
	function1.name = "function1";
	function1.startingLine = 4;
	function1.endingLine = 22;
	
	element for1;
	for1.type = "for";
	for1.name = "";
	for1.startingLine = 4;
	for1.endingLine = 22;

	element for2;
	for2.type = "for";
	for2.name = "";
	for2.startingLine = 4;
	for2.endingLine = 22;

	element ifInfor;
	ifInfor.type = "if";
	ifInfor.name = "";
	ifInfor.startingLine = 4;
	ifInfor.endingLine = 22;

	element function2;
	function2.type = "function";
	function2.name = "function2";
	function2.startingLine = 23;
	function2.endingLine = 49;

	element if1;
	if1.type = "if";
	if1.name = "";
	if1.startingLine = 4;
	if1.endingLine = 22;

	std::cout << "Creating scope for function 1 \n";
	AST.OpenNewNode();
	AST.PopulateNode(function1);

	AST.OpenNewNode();
	AST.PopulateNode(for1);
	AST.CloseNode();

	AST.OpenNewNode();
	AST.PopulateNode(for2);
	
	AST.OpenNewNode();
	AST.PopulateNode(ifInfor);
	AST.CloseNode();

	AST.CloseNode();
	AST.CloseNode();

	AST.OpenNewNode();
	AST.PopulateNode(function2);

	AST.OpenNewNode();
	AST.PopulateNode(if1);
	AST.CloseNode();
	AST.CloseNode();

	AST.showAST();
	
	
	
}
#endif
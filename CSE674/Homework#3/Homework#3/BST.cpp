/*
 File Name: BST.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 BST.cpp for Homework #3 for
 ADS F2016 Syracuse University
*/

#include "BST.h"
#include <algorithm>
#include <fstream>

BST::BST()
{
    head=NULL;
}

void BST::insert(int key, int value)
{
    BSTNode *node, *cursor, *prev;
    node = new BSTNode();
    node->_key=key;
    node->_value=value;
    node->Rlink=NULL;
    node->Llink=NULL;
    if (head==NULL)
    {
        head=node;
        return;
    }
    else
    {
        cursor=head;
        prev=NULL;
        while(cursor!=NULL)
        {
            prev=cursor;
            if (node->_key<=cursor->_key)
                cursor=cursor->Llink;
            else
                cursor=cursor->Rlink;
        }
        if(node->_key<=prev->_key)
            prev->Llink=node;
        else
            prev->Rlink=node;
    }
    return;
}

void BST::insert(BSTNode* node)
{
    BSTNode *cursor, *prev;
    if (head==NULL)
    {
        head=node;
        return;
    }
    else
    {
        cursor=head;
        prev=NULL;
        while(cursor!=NULL)
        {
            prev=cursor;
            if (node->_key<=cursor->_key)
                cursor=cursor->Llink;
            else
                cursor=cursor->Rlink;
        }
        if(node->_key<=prev->_key)
            prev->Llink=node;
        else
            prev->Rlink=node;
    }
    return;
}

bool BST::deleteKey(int key)
{
    if (head==NULL)
        return false;
    else
    {
        BSTNode *cursor, *prev, *nodeToDelete, *parentOfDelete;
        cursor=head;
        prev=NULL;
        while((cursor!=NULL)&&(key!=cursor->_key))
        {
            prev=cursor;
            if(key<cursor->_key)
                cursor=cursor->Llink;
            else
                cursor=cursor->Rlink;
        }
        if(cursor==NULL)
            return false;
        else
        {
                if(cursor==head)
                {
                    nodeToDelete=head;
                    parentOfDelete=NULL;
                }
                else
                {
                    nodeToDelete=cursor;
                    parentOfDelete=prev;
                }
        }
        if(nodeToDelete->Rlink==NULL)
        {
                if(parentOfDelete==NULL)
                {
                    head=nodeToDelete->Llink;
                    delete nodeToDelete;
                    return true;
                }
                else
                {
                    if(parentOfDelete->Llink==nodeToDelete)
                        parentOfDelete->Llink=nodeToDelete->Llink;
                    else
                        parentOfDelete->Rlink=nodeToDelete->Llink;
                    delete nodeToDelete;
                    return true;
                }
        }
        else
        {
                if(nodeToDelete->Llink==NULL)
                {
                    if(parentOfDelete==NULL)
                    {
                        head=nodeToDelete->Rlink;
                        delete nodeToDelete;
                        return true;
                    }
                }
                else
                {
                    cursor=nodeToDelete->Llink;
                    prev=nodeToDelete;
                    while (cursor->Rlink!=NULL)
                    {
                        prev=cursor;
                        cursor=cursor->Rlink;
                    }
                    nodeToDelete->_key=cursor->_key;
                    nodeToDelete->_value=cursor->_value;
                    if(prev==nodeToDelete)
                        prev->Llink=cursor->Llink;
                    else
                        prev->Rlink=cursor->Llink;
                    delete cursor;
                    return true;
                }
        }
    }
    return false;
}

BSTNode* BST::search(int key)
{
    BSTNode *cursor, *returnNode;
    if (head==NULL)
        return NULL;
    else
    {
        cursor=head;
        while((cursor!=NULL) && (cursor->_key!=key))
        {
            if (key<=cursor->_key)
                cursor=cursor->Llink;
            else
                cursor=cursor->Rlink;
        }
    }
    if(cursor!=NULL)
    {
        returnNode= new BSTNode();
        returnNode->_key=cursor->_key;
        returnNode->_value=cursor->_value;
        returnNode->Llink=NULL;
        returnNode->Rlink=NULL;
    }
    else
        returnNode=NULL;
    return returnNode;
}

int BST::height()
{    if (head==NULL)
        return -1;
    else
        return (1+ std::max(heightHelper(head->Llink),heightHelper(head->Rlink)));
}

int BST::heightHelper(BSTNode* node)
{
    if (node==NULL)
        return 0;
    else
        return (1+ std::max(heightHelper(node->Llink),heightHelper(node->Rlink)));
}

void BST::show(std::string filename)
{
    int level=0;
    if(head==NULL)
        return;
    std::ofstream output;
    output.open(filename);
    output<<"digraph G{"<<std::endl;
    showHelper(head, output, level, 0);
    output<<"}"<<std::endl;
    output.close();
    return;
}
int BST::showHelper(BSTNode* node, std::ofstream& file, int count, int parent)
{
    int level=count;
    if(node!=NULL)
    {
        if(count!=0)
            file<<" "<<parent<<"->"<<count<<std::endl;
        file<<" "<<count<<" [label=\""<<node->_key<<","<<node->_value<<"\"]"<<std::endl;
        count++;
        count=showHelper(node->Llink, file, count, level);
        count=showHelper(node->Rlink, file, count, level);
    }
    else if(node==NULL)
    {
        if(count!=0)
            file<<" "<<parent<<"->"<<count<<"[style = invis]"<<std::endl;
        file<<" "<<count<<" [label = \"\", width = .1, style = invis]"<<std::endl;
        count++;
    }
    return count;
}
BSTNode* BST::getHead()
{
    BSTNode *ret;
    if(head==NULL)
        return NULL;
    ret=new BSTNode();
    ret->_key=head->_key;
    ret->_value=head->_value;
    ret->Llink=NULL;
    ret->Rlink=NULL;
    return ret;
}
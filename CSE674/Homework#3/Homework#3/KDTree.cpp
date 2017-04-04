/*
 File Name: KDTree.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 KDTree.cpp for Homework #3 for
 ADS F2016 Syracuse University
*/

#include "KDTree.h"
#include <algorithm>
#include <fstream>

KDTree::KDTree()
{
    head=NULL;
}

void KDTree::insert(int x, int y, int value)
{
    KDNode *temp;
    temp = new KDNode();
    temp->_x=x;
    temp->_y=y;
    temp->_value=value;
    if (head==NULL)
        head=temp;
    else
    {
        insertHelper(temp);
    }
    return;
}

void KDTree::insert(KDNode* node)
{
    if (head==NULL)
        head=node;
    else
    {
        insertHelper(node);
    }
    return;
}

void KDTree::insertHelper(KDNode *node)
{
    KDNode *cursor, *prev;
    bool XorY=1;
    cursor=head;
    prev=NULL;
    while(cursor!=NULL)
    {
        XorY=!XorY;
        prev=cursor;
        if (XorY==1)
        {
            if (node->_y<=cursor->_y)
                cursor=cursor->Llink;
            else
                cursor=cursor->Rlink;
        }
        else
        {
            if (node->_x<=cursor->_x)
                cursor=cursor->Llink;
            else
                cursor=cursor->Rlink;
        }
    }
    if(XorY==1)
    {
        if(node->_y<=prev->_y)
            prev->Llink=node;
        else
            prev->Rlink=node;
    }
    else
    {
        if(node->_x<=prev->_x)
            prev->Llink=node;
        else
            prev->Rlink=node;
    }
}

void KDTree::deleteKey(int x, int y)
{
    if (head==NULL)
        return;
    else
    {
        if(deleteHelper(head,x,y,0)!=NULL)
            return;
    }
    return;
}

KDNode* KDTree::deleteHelper(KDNode* node, int x, int y ,int depth)
{
    if(node==NULL)
        return NULL;
    int XorY=depth%2;
    if(node->_x==x && node->_y==y)
    {
        if(node==head && node->Llink==NULL && node->Rlink==NULL)
        {
            head=NULL;
            return NULL;
        }
        if(node->Rlink!=NULL)
        {
            KDNode *min=findMin(node->Rlink,XorY,0);
            node->_x=min->_x;
            node->_y=min->_y;
            node->_value=min->_value;
            node->Rlink=deleteHelper(node->Rlink, min->_x, min->_y, depth+1);
        }
        else if(node->Llink!=NULL)
        {
            KDNode*min=findMin(node->Llink,XorY,0);
            node->_x=min->_x;
            node->_y=min->_y;
            node->_value=min->_value;
            node->Llink=deleteHelper(node->Llink, min->_x, min->_y, depth+1);
        }
        else
        {
            node=NULL;
            return NULL;
        }
        return node;
    }
    if(XorY==0)
    {
        if(x<=node->_x)
            node->Llink=deleteHelper(node->Llink, x, y, depth+1);
        else
            node->Rlink=deleteHelper(node->Rlink, x, y, depth+1);
    }
    else
    {
        if(y<=node->_y)
            node->Llink=deleteHelper(node->Llink, x, y, depth+1);
        else
            node->Rlink=deleteHelper(node->Rlink, x, y, depth+1);
    }
    return node;
}

KDNode* KDTree::findMin(KDNode* node, int d, int depth)
{
    if (node==NULL)
        return NULL;
    int XorY=depth%2;
    if (XorY==d)
    {
        if(node->Llink==NULL)
            return node;
        return findMin(node->Llink,d,depth+1);
    }
    return minNode(node, findMin(node->Llink,d,depth+1),findMin(node->Rlink, d, depth+1),d);
}

KDNode* KDTree::minNode(KDNode *x, KDNode *y, KDNode *z, int d)
{
    KDNode *ret=x;
    if (d==0)
    {
        if(y!=NULL && y->_x<ret->_x)
            ret=y;
        if(z!=NULL && z->_x<ret->_x)
            ret=z;
    }
    else
    {
        if(y!=NULL && y->_y<ret->_y)
            ret=y;
        if(z!=NULL && z->_y<ret->_y)
            ret=z;
    }
    return ret;
}

KDNode* KDTree::search(int x, int y)
{
    KDNode *node, *retNode;
    bool XorY=0;
    int val, key;
    if (head==NULL)
        return NULL;
    else
    {
        node=head;
        if(XorY==1)
            key=y;
        else
            key=x;
        val=node->_x;
        while(node!=NULL && (node->_x!=x || node->_y!=y))
        {
            if(key<=val)
                node=node->Llink;
            else
                node=node->Rlink;
            if(XorY==0 && node!=NULL)
            {
                val=node->_y;
                key=y;
            }
            else if(node!=NULL)
            {
                val=node->_x;
                key=x;
            }
            XorY=!XorY;
        }
    }
    if(node!=NULL)
    {
        retNode= new KDNode();
        retNode->_x=node->_x;
        retNode->_y=node->_y;
        retNode->_value=node->_value;
        retNode->Llink=NULL;
        retNode->Rlink=NULL;
    }
    else
        retNode=NULL;
    return retNode;
}

int KDTree::height()
{
    if (head==NULL)
        return -1;
    else
        return (1+ std::max(heightHelper(head->Llink),heightHelper(head->Rlink)));
}

int KDTree::heightHelper(KDNode* node)
{
    if (node==NULL)
        return 0;
    else
        return (1+ std::max(heightHelper(node->Llink),heightHelper(node->Rlink)));
}

void KDTree::show(std::string filename)
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
    return;
}

int KDTree::showHelper(KDNode* node, std::ofstream& file, int count, int parent)
{
    int level=count;
    if(node!=NULL)
    {
        if(count!=0)
            file<<" "<<parent<<"->"<<count<<std::endl;
        file<<" "<<count<<" [label=\""<<node->_x<<","<<node->_y<<","<<node->_value<<"\"]"<<std::endl;
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

KDNode* KDTree::getHead()
{
    KDNode *ret;
    if(head==NULL)
        return NULL;
    ret=new KDNode();
    ret->_x=head->_x;
    ret->_y=head->_y;
    ret->_value=head->_value;
    ret->Llink=NULL;
    ret->Rlink=NULL;
    return ret;
}
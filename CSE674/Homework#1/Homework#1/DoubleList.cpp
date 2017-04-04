/*
 File Name: DoubleList.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Implements a doubly linked list for ADS F2016
 
*/
#include "DoubleList.h"
#include <iostream>
DoubleList::DoubleList()
{
    _lenght=0;
    _head_ptr=NULL;
    cursor=NULL;
}
DoubleList::DoubleList(const DoubleList& source)
{
    DoubleNode *temp;
    temp=source._head_ptr;
    while (temp!=NULL)
    {
        insert(temp);
        temp=temp->frontLink();
    }
    cursor=source.cursor;
    
}
DoubleList::~DoubleList()
{
    DoubleNode *remove_ptr;
    while (_head_ptr!=NULL)
    {
        remove_ptr=_head_ptr->frontLink();
        _head_ptr=_head_ptr->frontLink();
        delete remove_ptr;
    }
    _lenght=0;
    cursor=NULL;
}

void DoubleList::insert(const int& value)
{
    if(cursor==NULL)
    {
        DoubleNode *insert_ptr;
        insert_ptr= new DoubleNode(value,NULL,NULL);
        _head_ptr=insert_ptr;
        cursor=_head_ptr;
    }
    else
    {
        DoubleNode *insert_ptr;
        insert_ptr= new DoubleNode(value,cursor->frontLink(),cursor);
        if(insert_ptr->frontLink()!=NULL)
            insert_ptr->frontLink()->set_backLink(insert_ptr);
        cursor->set_frontLink(insert_ptr);
        insert_ptr->set_backLink(cursor);
        cursor=insert_ptr;
    }
    _lenght++;
}
void DoubleList::insert(DoubleNode* pointer)
{
    if(cursor==NULL && length()==0)
    {
        _head_ptr=pointer;
        cursor=_head_ptr;
    }
    else
    {
        pointer->set_frontLink(cursor->frontLink());
        if(pointer->frontLink()!=NULL)
            pointer->frontLink()->set_backLink(pointer);
        pointer->set_backLink(cursor);
        cursor->set_frontLink(pointer);
        cursor=pointer;
    }
    _lenght++;
}
void DoubleList::remove_current()
{
    if(cursor==_head_ptr)
    {
        DoubleNode *temp;
        temp=cursor->frontLink();
        _head_ptr=temp;
        delete cursor;
        cursor=_head_ptr;
    }
    else
    {
        DoubleNode *prev, *current;
        current=cursor;
        prev=current->backLink();
        if (current->frontLink()!=NULL)
        {
            prev->set_frontLink(current->frontLink());
            current->frontLink()->set_backLink(prev);
        }
        else
            prev->set_frontLink(NULL);
        delete cursor;
        cursor=prev->frontLink();
    }
    _lenght--;
    
}
DoubleNode* DoubleList::remove_current_node()
{
    DoubleNode *returnptr;
    if(cursor==_head_ptr)
    {
        DoubleNode *temp;
        temp=cursor->frontLink();
        _head_ptr=temp;
        returnptr=cursor;
        returnptr->set_frontLink(NULL);
        returnptr->set_backLink(NULL);
        cursor=_head_ptr;
    }
    else
    {
        DoubleNode *prev, *current;
        current=cursor;
        prev=current->backLink();
        if (current->frontLink()!=NULL)
        {
            prev->set_frontLink(current->frontLink());
            current->frontLink()->set_backLink(prev);
        }
        else
            prev->set_frontLink(NULL);
        returnptr=cursor;
        returnptr->set_frontLink(NULL);
        returnptr->set_backLink(NULL);
        cursor=prev->frontLink();
    }
    _lenght--;
    return returnptr;
}
void DoubleList::copy(DoubleList* src)
{
    if(this==src)
        return;
    if(_head_ptr!=NULL)
        delete this;
    if (src->_head_ptr==NULL)
        return;
    insert(src->_head_ptr->data());
    DoubleNode *temp;
    temp=src->_head_ptr->frontLink();
    while(temp !=NULL)
    {
        insert(temp->data());
        temp=temp->frontLink();
    }
}
void DoubleList::operator =(DoubleList *src)
{
    copy(src);
}
void DoubleList::advance()
{
    if (cursor==NULL)
        return;
    else if(cursor->frontLink()==NULL)
        cursor=NULL;
    else
        cursor=cursor->frontLink();
}
void DoubleList::back()
{
    if (cursor==NULL)
        return;
    else if(cursor->backLink()==NULL)
        cursor=NULL;
    else
        cursor=cursor->backLink();
}
bool DoubleList::contains(int value)
{
    DoubleNode *temp;
    temp=cursor;
    start();
    for(int i=0;i<length();i++)
    {
        if(current()==value)
        {
            cursor=temp;
            return true;
            break;
        }
        else
            advance();
    }
    cursor=temp;
    return false;
}
void DoubleList::Print()
{
    DoubleNode *temp;
    temp=cursor;
    start();
    for(int i=0;i<length();i++)
    {
        std::cout<<current();
        if(!(i==length()-1))
            std::cout<<", ";
        advance();
    }
    std::cout<<std::endl;
    cursor=temp;
}

void DoubleList::sort()
{
    start();
    int n=length();
    DoubleNode *prev;
    prev=cursor;
    advance();
    bool swapped=false;
    for(int j=0;j<length();j++)
    {
        start();
        for(int i=0;i<=n;i++)
        {
            if(cursor!=NULL)
            {
                if(prev->data()>cursor->data())
                {
                    swap(prev,cursor);
                    swapped=true;
                }
                if(cursor->frontLink()!=NULL)
                {
                    prev=cursor;
                    advance();
                }
                else
                {
                    prev=_head_ptr;
                    break;
                }
            }
            if(cursor==NULL)
                break;
        }
    }
    return;
}
void DoubleList::swap(DoubleNode *a, DoubleNode *b)
{
    DoubleNode *temp,*swapee;
    temp=cursor;
    start();
    int i=0;
    for(i=0;i<length();i++)
    {
        if(cursor==a)
            break;
        advance();
    }
    swapee=remove_current_node();
    start();
    for(i=0;i<length();i++)
    {
        if(cursor==b)
            break;
        advance();
    }
    insert(swapee);
}

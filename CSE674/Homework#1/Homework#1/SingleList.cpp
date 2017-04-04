/*
 File Name: SingleList.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Implements a singlely linked list for ADS F2016
 
 */
#include "SingleList.h"
#include <iostream>
SingleList::SingleList()
{
    _lenght=0;
    _head_ptr=NULL;
    cursor=NULL;
}
SingleList::SingleList(const SingleList& source)
{
    SingleNode *temp;
    cursor=NULL;
    temp=source._head_ptr;
    while (temp!=NULL)
    {
        insert(temp);
        temp=temp->link();
    }
    cursor=source.cursor;
    _lenght=source._lenght;
}
SingleList::~SingleList()
{
    SingleNode *remove_ptr;
    while (_head_ptr!=NULL)
    {
        remove_ptr=_head_ptr->link();
        _head_ptr=_head_ptr->link();
        delete remove_ptr;
    }
    _lenght=0;
    cursor=NULL;
}

void SingleList::insert(const int& value)
{
    if(cursor==NULL)
    {
        SingleNode *insert_ptr;
        insert_ptr= new SingleNode(value,NULL);
        _head_ptr=insert_ptr;
        cursor=_head_ptr;
    }
    else
    {
        SingleNode *insert_ptr;
        insert_ptr= new SingleNode(value,cursor->link());
        cursor->set_link(insert_ptr);
        cursor=insert_ptr;
    }
    _lenght++;
}
void SingleList::insert(SingleNode* pointer)
{
    if(cursor==NULL)
    {
        _head_ptr=pointer;
        cursor=_head_ptr;
    }
    else
    {
        pointer->set_link(cursor->link());
        cursor->set_link(pointer);
        cursor=pointer;
    }
    _lenght++;
}
void SingleList::remove_current()
{
    if(cursor==_head_ptr)
    {
        SingleNode *temp;
        temp=cursor->link();
        _head_ptr=temp;
        delete cursor;
        cursor=_head_ptr;
    }
    else
    {
        SingleNode *prev, *current;
        current=_head_ptr;
        prev=NULL;
        while (current!=cursor)
        {
            prev=current;
            current=current->link();
        }
        if (cursor->link()!=NULL)
            prev->set_link(cursor->link());
        else
            prev->set_link(NULL);
        delete cursor;
        cursor=prev->link();
    }
    _lenght--;
    
}
SingleNode* SingleList::remove_current_node()
{
    SingleNode *returnptr;
    if(cursor==_head_ptr)
    {
        SingleNode *temp;
        temp=cursor->link();
        _head_ptr=temp;
        returnptr=cursor;
        returnptr->set_link(NULL);
        cursor=_head_ptr;
    }
    else
    {
        SingleNode *prev, *current;
        current=_head_ptr;
        prev=NULL;
        while (current!=cursor)
        {
            prev=current;
            current=current->link();
        }
        if (cursor->link()!=NULL)
            prev->set_link(cursor->link());
        else
            prev->set_link(NULL);
        returnptr=cursor;
        returnptr->set_link(NULL);
        cursor=prev->link();
    }
    _lenght--;
    return returnptr;
}
void SingleList::copy(SingleList* src)
{
    if(this==src)
        return;
    if(_head_ptr!=NULL)
        delete this;
    if (src->_head_ptr==NULL)
        return;
    insert(src->_head_ptr->data());
    SingleNode *temp;
    temp=src->_head_ptr->link();
    while(temp !=NULL)
    {
        insert(temp->data());
        temp=temp->link();
    }
}
void SingleList::advance()
{
    if (cursor==NULL)
        return;
    else if(cursor->link()==NULL)
        cursor=NULL;
    else
        cursor=cursor->link();
}
bool SingleList::contains(int value)
{
    SingleNode *temp;
    temp=cursor;
    start();
    if (cursor==NULL)
    {
        cursor=temp;
        return false;
    }
    int limit=length();
    for(int i=0;i<limit;i++)
    {
        if (cursor==NULL)
        {
            cursor=temp;
            return false;
        }
        else if(current()==value)
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
void SingleList::Print()
{
    SingleNode *temp;
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
void SingleList::sort()
{
    start();
    int n=length();
    SingleNode *prev;
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
                if(cursor->link()!=NULL)
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
void SingleList::swap(SingleNode *a, SingleNode *b)
{
    SingleNode *temp,*swapee;
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

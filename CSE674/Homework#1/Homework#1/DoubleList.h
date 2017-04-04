/*
 File Name: DoubleList.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Implements a doubly linked list for ADS F2016
 
*/
#ifndef DoubleList_H
#define DoubleList_H

#include <stdio.h>
#include "DoubleNode.h"
class DoubleList
{
public:
    DoubleList();
    DoubleList(const DoubleList& source);
    ~DoubleList();
    void insert(const int& value);
    void insert(DoubleNode* pointer);
    void remove_current();
    DoubleNode* remove_current_node();
    int length() {return _lenght;};
    void copy(DoubleList* src);
    void operator =(DoubleList *src);
    void advance();
    void back();
    int current() {if (cursor!=NULL) return cursor->data(); else return int();}
    void start() {cursor = _head_ptr;}
    bool contains(int value);
    void Print();
    void sort();
    void swap(DoubleNode *a, DoubleNode *b);
private:
    DoubleNode *_head_ptr, *cursor;
    int _lenght;
};
#endif

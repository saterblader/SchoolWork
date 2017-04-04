/*
 File Name: SingleList.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Implements a singlely linked list for ADS F2016
 
 */

#ifndef SingleList_H
#define SingleList_H

#include <stdio.h>
#include "SingleNode.h"
class SingleList
{
public:
    SingleList();
    SingleList(const SingleList& source);
    ~SingleList();
    void insert(const int& value);
    void insert(SingleNode* pointer);
    void remove_current();
    SingleNode* remove_current_node();
    int length() {return _lenght;};
    void copy(SingleList* src);
    void advance();
    int current() {return cursor->data();}
    void start() {cursor = _head_ptr;}
    bool contains(int value);
    void Print();
    void sort();
    void swap(SingleNode *a, SingleNode *b);
private:
    SingleNode *_head_ptr, *cursor;
    int _lenght;
};
#endif
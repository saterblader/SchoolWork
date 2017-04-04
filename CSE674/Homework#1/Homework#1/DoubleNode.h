/*
 File Name: DoubleNode.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Implements a doubly linked node for ADS F2016
 
 */

#ifndef DoubleNode_H
#define DoubleNode_H

#include <stdio.h>
class DoubleNode
{
public:
    DoubleNode(const int& init_data = int(),DoubleNode* init_frontLink = NULL,DoubleNode* init_backLink = NULL )
    {_data =init_data; _frontLink=init_frontLink; _backLink=init_backLink;}
    void set_data(const int data) {_data=data;}
    void set_frontLink(DoubleNode* link) {_frontLink=link;}
    void set_backLink(DoubleNode* link) {_backLink=link;}
    int data() const {return _data;}
    const DoubleNode* frontLink() const {return _frontLink;}
    const DoubleNode* backLink() const {return _backLink;}
    DoubleNode* frontLink() {return _frontLink;}
    DoubleNode* backLink() {return _backLink;}
    ~DoubleNode(){_data= int(); _frontLink=NULL; _backLink=NULL;}
    
private:
    int _data;
    DoubleNode* _frontLink;
    DoubleNode* _backLink;
};
#endif

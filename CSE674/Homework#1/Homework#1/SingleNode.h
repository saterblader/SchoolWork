/*
 File Name: SingleNode.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Implements a singlely linked node for ADS F2016
 
*/

#ifndef SingleNode_H
#define SingleNode_H
#include <stdio.h>
class SingleNode
{
public:
    SingleNode(const int& init_data = int(),SingleNode* init_link = NULL)
                {_data =init_data; _link=init_link;}
    void set_data(const int data) {_data=data;}
    void set_link(SingleNode* link) {_link=link;}
    int data() const {return _data;}
    const SingleNode* link() const {return _link;}
    SingleNode* link() {return _link;}
    ~SingleNode(){_data= int(); _link=NULL;}

private:
    int _data;
    SingleNode* _link;
};
#endif

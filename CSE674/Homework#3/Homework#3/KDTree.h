/*
 File Name: KDTree.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 KDTree.h for Homework #3 for
 ADS F2016 Syracuse University
*/

#ifndef KDTree_H
#define KDTree_H

#include <stdio.h>
#include <string>
struct KDNode
{
    int _x;
    int _y;
    int _value;
    KDNode *Llink=NULL;
    KDNode *Rlink=NULL;
};

class KDTree
{
public:
    KDTree();
    void insert(int x, int y, int value);
    void insert(KDNode* node);
    void deleteKey(int x, int y);
    KDNode* search(int x, int y);
    int height();
    void show(std::string filename);
    KDNode* getHead();
private:
    KDNode *head;
    void insertHelper(KDNode *node);
    KDNode* deleteHelper(KDNode* node, int x, int y ,int depth);
    KDNode* findMin(KDNode* node, int d, int depth);
    KDNode* minNode(KDNode *x, KDNode *y, KDNode *z, int d);
    int heightHelper(KDNode* node);
    int showHelper(KDNode* node, std::ofstream& file, int count, int parent);
};
#endif
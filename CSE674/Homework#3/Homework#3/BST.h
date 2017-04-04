/*
 File Name: BST.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 BST.h for Homework #3 for
 ADS F2016 Syracuse University
*/

#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <string>
#include <fstream>
struct BSTNode
{
    int _key;
    int _value;
    BSTNode *Llink=NULL;
    BSTNode *Rlink=NULL;
};

class BST
{
public:
    BST();
    void insert(int key, int value);
    void insert(BSTNode* node);
    bool deleteKey(int key);
    BSTNode* search(int key);
    int height();
    void show(std::string filename);
    BSTNode* getHead();
private:
    BSTNode *head;
    int heightHelper(BSTNode* node);
    int showHelper(BSTNode* node, std::ofstream& file, int count, int parent);
};
#endif
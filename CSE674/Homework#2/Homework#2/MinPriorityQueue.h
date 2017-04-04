/*
 File Name: MinPriorityQueue.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 MinPriorityQueue.h for Homework #2 for
 ADS F2016 Syracuse University
 */

#ifndef MinPriorityQueue_h
#define MinPriorityQueue_h

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class MinPriorityQueue
{
public:
    MinPriorityQueue();
    MinPriorityQueue(std::vector<std::pair<int,int> > vect);
    bool isEmpty();
    std::vector<std::pair<int,int> > AllMinimum();
    std::vector<std::pair<int,int> > ExtractAllMin();
    void DecreaseKey(int position,int newKey);
    void PrintQueue();
    void Insert(std::pair<int,int> NewValue);
    std::vector<std::pair<int,int> > GetQueue();
    int GetSize();
    std::pair<int,int> GetPair(int index);
private:
    std::vector<std::pair<int,int> > _minHeap;
    void HeapifyDown(int index, int length);
    void HeapifyUp(int key);
    void Heapify();
};
#endif
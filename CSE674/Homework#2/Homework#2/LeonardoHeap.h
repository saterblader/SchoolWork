/*
 File Name: LeonardoHeap.h
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 LeonardoHeap.h for Homework #2 for
 ADS F2016 Syracuse University
 */

#ifndef LeonardoHeap_H
#define LeonardoHeap_H

#include <iostream>
#include <vector>
#include <iterator>

class LeonardoHeap
{
public:
    LeonardoHeap();
    LeonardoHeap(std::vector<int> vect);
    bool isEmpty();
    void SmoothSort();
    std::vector<int> GetHeap();
    int GetSize();
    int GetComparisons();
private:
    void IncrementComparisons();
    void Heapify(int low, int high);
    void SwapElement(int low, int high);
    void HeapifyRight(int low, int high);
    std::vector<int> _heap;
    int _num_of_comparisons;
};
#endif
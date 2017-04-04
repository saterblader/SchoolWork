/*
 File Name: LeonardoHeap.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 LeonardoHeap.cpp for Homework #2 for
 ADS F2016 Syracuse University
*/


#include "LeonardoHeap.h"
LeonardoHeap::LeonardoHeap()
{
    _num_of_comparisons=0;
}

LeonardoHeap::LeonardoHeap(std::vector<int> vect) : _heap(vect)
{
    _num_of_comparisons=0;
}

bool LeonardoHeap::isEmpty()
{
    if (_heap.size()<=0)
        return true;
    return false;
}

void LeonardoHeap::SmoothSort()
{
    if (isEmpty()&&GetSize()<=0)
        return;
    int size=GetSize()-1;
    Heapify(0,size);
    while (size>0)
    {
        SwapElement(size,0);
        size--;
        HeapifyRight(0,size);
    }
    return;
}

std::vector<int> LeonardoHeap::GetHeap()
{
    return _heap;
}

int LeonardoHeap::GetSize()
{
    return _heap.size();
}

int LeonardoHeap::GetComparisons()
{
    return _num_of_comparisons;
}

void LeonardoHeap::IncrementComparisons()
{
    _num_of_comparisons++;
    return;
}

void LeonardoHeap::Heapify(int low, int high)
{
    int middle=(high-low-1)/2;
    while (middle>=0)
    {
        HeapifyRight(middle,high);
        middle--;
    }
    return;
}

void LeonardoHeap::SwapElement(int low, int high)
{
    int swap=_heap.at(low);
    _heap.at(low)=_heap.at(high);
    _heap.at(high)=swap;
    return;
}

void LeonardoHeap::HeapifyRight(int low, int high)
{
    int root=low;
    while ((root*2)+1<=high)
    {
        int LChild=(root*2)+1;
        int RChild=LChild+1;
        int SwapIndex=root;
        if (_heap.at(SwapIndex)<_heap.at(LChild))
        {
            SwapIndex=LChild;
            IncrementComparisons();
        }
        if ((RChild<=high)&&(_heap.at(SwapIndex)<_heap.at(RChild)))
        {
            SwapIndex=RChild;
            IncrementComparisons();
        }
        if (SwapIndex!=root)
        {
            SwapElement(root,SwapIndex);
            root=SwapIndex;
            IncrementComparisons();
        }
        else
            break;
    }
    return;
}
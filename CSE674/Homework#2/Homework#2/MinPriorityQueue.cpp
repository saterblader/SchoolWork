/*
 File Name: MinPriorityQueue.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 MinPriorityQueue.cpp for Homework #2 for
 ADS F2016 Syracuse University
*/

#include "MinPriorityQueue.h"
MinPriorityQueue::MinPriorityQueue()
{

}

MinPriorityQueue::MinPriorityQueue(std::vector<std::pair<int,int> > vect) : _minHeap(vect)
{
    Heapify();
}

bool MinPriorityQueue::isEmpty()
{
    if (_minHeap.size()<=0)
        return true;
    return false;
}

std::vector<std::pair<int,int> > MinPriorityQueue::AllMinimum()
{
    std::vector<std::pair<int,int> > Mins;
    int minVal=_minHeap[0].first;
    int length=_minHeap.size();
    Mins.push_back(_minHeap[0]);
    for (int i=1;i<length;i++)
    {
        if (minVal==_minHeap[i].first)
        {
            Mins.push_back(_minHeap[i]);
        }
    }
    return Mins;
}

std::vector<std::pair<int,int> >MinPriorityQueue::ExtractAllMin()
{
    std::vector<int> ToDelete;
    std::vector<std::pair<int,int> > Mins;
    int minVal=_minHeap[0].first;
    int length=_minHeap.size();
    for (int i=0;i<length;i++)
    {
        if (minVal==_minHeap[i].first)
        {
            Mins.push_back(_minHeap[i]);
            ToDelete.push_back(i);
        }
    }
    std::reverse(ToDelete.begin(),ToDelete.end());
    for (int j=0;j<ToDelete.size();j++)
        _minHeap.erase(_minHeap.begin()+ToDelete[j]);
    HeapifyDown(0,_minHeap.size());
    return Mins;
}

void MinPriorityQueue::DecreaseKey(int position, int newKey)
{
    int length=_minHeap.size();
    int oldKey=_minHeap[position].first;
    if (position<length)
    {
        _minHeap[position].first=newKey;
        if(oldKey > newKey)
            HeapifyUp(position);
        if(oldKey < newKey)
            HeapifyDown(position,length);
    }
    return;
}

void MinPriorityQueue::PrintQueue()
{
    std::cout<<"PrintQueue\n";
    for (std::vector<std::pair<int,int> >::iterator iter=_minHeap.begin();iter!=_minHeap.end();iter++)
    {
        int key=iter->first;
        int value=iter->second;
        std::cout<<key<<" , "<<value<<"\n";
    }
    return;
}

void MinPriorityQueue::Insert(std::pair<int,int> NewValue)
{
    int length=_minHeap.size();
    _minHeap.push_back(NewValue);
    HeapifyUp(length);
}

std::vector<std::pair<int,int> > MinPriorityQueue::GetQueue()
{
    return _minHeap;
}

int MinPriorityQueue::GetSize()
{
    return _minHeap.size();
}

std::pair<int,int> MinPriorityQueue::GetPair(int index)
{
    return _minHeap.at(index);
}

void MinPriorityQueue::Heapify()
{
    std::vector<std::pair<int,int> >::iterator iter=_minHeap.begin();
    int length=_minHeap.size();
    for(int i=length-1;i>=0;--i)
    {
        HeapifyDown(i,length);
    }
    for (std::vector<std::pair<int,int> >::iterator iter=_minHeap.begin();iter!=_minHeap.end();iter++)
    {
        int key=iter->first;
        int value=iter->second;
        std::cout<<key<<" , "<<value<<"\n";
    }
    return;
}

void MinPriorityQueue::HeapifyDown(int index, int length)
{
    int LeftChildIndex=2*index+1;
    if(LeftChildIndex>=length)
        return;
    int RightChildIndex=2*index+2;
    int minIndex=index;
    if(_minHeap[index]>_minHeap[LeftChildIndex])
        minIndex=LeftChildIndex;
    if((RightChildIndex<length)&&(_minHeap[minIndex]>_minHeap[RightChildIndex]))
        minIndex=RightChildIndex;
    if(minIndex!=index)
    {
        std::pair<int,int> temp=_minHeap[index];
        _minHeap[index]=_minHeap[minIndex];
        _minHeap[minIndex]=temp;
        HeapifyDown(minIndex,length);
    }
    return;
}

void MinPriorityQueue::HeapifyUp(int index)
{
    if(index==0)
        return;
    int ParentIndex=(index-1);
    if(_minHeap[ParentIndex]>_minHeap[index])
    {
        std::pair<int,int> temp=_minHeap[ParentIndex];
        _minHeap[ParentIndex]=_minHeap[index];
        _minHeap[index]=temp;
        HeapifyUp(ParentIndex);
    }
    return;
}
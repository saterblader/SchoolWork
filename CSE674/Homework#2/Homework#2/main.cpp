/*
 File Name: main.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Main.cpp for Homework #2 for 
 ADS F2016 Syracuse University
*/

#include <cstdlib>
#include <array>
#include <algorithm>
#include <string>
#include "MinPriorityQueue.h"
#include "LeonardoHeap.h"
using namespace std;
vector<int>RandomDistinctNumebers(int Range, int Total);
void PrintExtracted(vector<pair<int,int> > Out);
void PrintMinimums(vector<pair<int,int> > Out);
void EmptyQueue(bool value);
void PrintQueue(vector<pair<int,int> > Out);
void PrintNewPriority(pair<int,int> mypair, int newkey);
void PrintIterations(int num);
void PrintIterNum(int num);
void ShortenedList(vector<int> vect);
void NumberOfCompare(int value);
vector<int>CreateSet(int Start, int End);
double GetRandom(double Min, double Max);
void TestCaseOne();
void TestCaseTwo();
void TestCaseThree();
void TestCaseFour();
void TestCaseFive();
void TestCaseSix();
void TestCaseSeven();
void TestCaseEight();
void TestCaseNine();
void TestCaseTen();
int main(int argc, const char * argv[])
{
    TestCaseOne();
    TestCaseTwo();
    TestCaseThree();
    TestCaseFour();
    TestCaseFive();
    TestCaseSix();
    TestCaseSeven();
    TestCaseEight();
    TestCaseNine();
    TestCaseTen();
    return 0;
}

vector<int>RandomDistinctNumebers(int Range, int Total)
{
    vector<int> vec;
    srand (time(NULL));
    int r;
    for(int i=0;i<Total;i++)
    {
        do
        {
            r=rand()% Range+1;
        }while(find(vec.begin(),vec.end(),r)!=vec.end());
        vec.push_back(r);
    }
    return vec;
}

void PrintExtracted(vector<pair<int,int> > Out)
{
    cout<<"Extracted Minimums: ";
    for (int i =0;i<Out.size();i++)
        cout<<"["<<Out[i].first<<" "<<Out[i].second<<"] ";
    cout<<"\n";
    return;
}

void PrintMinimums(vector<pair<int,int> > Out)
{
    cout<<"All Minimums: ";
    for (int i=0;i<Out.size();i++)
        cout<<"["<<Out[i].first <<" "<<Out[i].second<<"] ";
    cout<< "\n";
    return;
}

void EmptyQueue(bool value)
{
    cout << "Verifiying the contents of the queue\n";
    if (value==true)
        cout<<"The queue is empty.\n";
    else
        cout<<"The queue is not empty.\n";
    return;
}

void PrintQueue(vector<pair<int,int> > Out)
{
    for (vector<pair<int,int> >::iterator iter=Out.begin();iter!=Out.end();iter++)
    {
        int key=iter->first;
        int val=iter->second;
        cout<<"["<<key<<" "<<val<<"]\n";
    }
    return;
}

void PrintNewPriority(pair<int,int> mypair, int newkey)
{
    cout<<"Changing the Priority of ["<<mypair.first<<" "<<mypair.second<<"] to "<<newkey<<".\n";
    return;
}

void PrintIterations(int num)
{
    cout<<"Contents of the Queue at Iteration: "<<num<<"\n";
    return;
}

void PrintIterNum(int num)
{
    cout<<"Iteration: "<<num<<" ";
    return;
}

void ShortenedList(vector<int> vect)
{
    cout<<"A shortened list of elements in the Leonardo Heap:\n";
    cout<<"[ ";
    for (int i=0;i<vect.size();i++)
    {
        if (i%20 == 0){
            cout  << vect.at(i);
            if (i != vect.size()-20)
                cout << ",";
        }
        
    }
    cout <<" ]\n";
    return;
}

void NumberOfCompare(int value)
{
    cout<<"The total number of comparisons performed among elements in the Leonardo Heap = "<<value<<"\n";
    return;
}

vector<int> CreateSet(int Start, int End)
{
    vector<int> NumberSet;
    if(Start>End)
    {
        for (int i=Start;i>End-1;i--)
        {
            NumberSet.push_back(i);
        }
    }
    else if (Start<End)
    {
        for (int j=Start;j<=End;j++)
        {
            NumberSet.push_back(j);
        }
    }
    return NumberSet;
}

double GetRandom(double Min, double Max)
{
    return ((double(rand())/double(RAND_MAX))*(Max-Min))+Min;
}
void TestCaseOne()
{
    cout<<endl<<"Test Case 1:\n";
    MinPriorityQueue PQ;
    EmptyQueue(PQ.isEmpty());
    cout<<"Inserting Data items: [100 1] [99 2] ... [1 100]"<<endl;
    int i=1;
    int j=100;
    do
    {
        PQ.Insert(make_pair(j,i));
        i++;
        j--;
    }
    while (i<101&&j>0);
    PrintExtracted(PQ.ExtractAllMin());
    cout<<"Inserting [1 0] into queue\n";
    PQ.Insert(make_pair(1,0));
    PrintExtracted(PQ.ExtractAllMin());
    return;
}
void TestCaseTwo()
{
    cout<<endl<<"Test Case 2:\n";
    MinPriorityQueue PQ;
    EmptyQueue(PQ.isEmpty());
    cout<<"Inserting Data items: [1000 1] [999 2] ... [1 1000]"<<endl;
    int i=1;
    int j=1000;
    do
    {
        PQ.Insert(make_pair(j,i));
        i++;
        j--;
    }
    while (i<1001&&j>0);
    PrintMinimums(PQ.AllMinimum());
    cout<<"Inserting Data items: [1 1] [1 2] ... [1 30]"<<endl;
    for (int k=1;k<=30;k++)
    {
        PQ.Insert(make_pair(1,k));
    }
    PrintExtracted(PQ.ExtractAllMin());
    PrintMinimums(PQ.AllMinimum());
    return;
}
void TestCaseThree()
{
    cout<<endl<<"Test Case 3:\n";
    MinPriorityQueue PQ;
    int count = 0;
    EmptyQueue(PQ.isEmpty());
    cout<<"Generating 500 random data items [i,j]. (10 >= [i,j] <= 1000)"<<endl;
    while (count<500)
    {
        PQ.Insert(std::make_pair(GetRandom(10,1001),GetRandom(10,1001)));
        count++;
    }
    count=0;
    while (count<5)
    {
        PrintExtracted(PQ.ExtractAllMin());
        count++;
    }
    int r=rand()%PQ.GetSize();
    PrintNewPriority(PQ.GetPair(r),5);
    PQ.DecreaseKey(r,5);
    PrintMinimums(PQ.AllMinimum());
    return;
}
void TestCaseFour()
{
    cout<<endl<<"Test Case 4:\n";
    MinPriorityQueue PQ;
    int count=0, index, newKey;
    EmptyQueue(PQ.isEmpty());
    cout<<"Generating 500 random data items [i,j]. (10 >= [i,j] <= 1000)"<<endl;
    while (count<500)
    {
        PQ.Insert(make_pair(GetRandom(10,1001),GetRandom(10,1001)));
        count++;
    }
    count=0;
    while (count<10)
    {
        index=rand()%PQ.GetSize();
        newKey=rand()%9+1;
        PrintNewPriority(PQ.GetPair(index),newKey);
        PQ.DecreaseKey(index,newKey);
        PrintExtracted(PQ.ExtractAllMin());
        count++;
    }
    return;
}
void TestCaseFive()
{
    cout<<endl<<"Test Case 5:\n";
    int index=0,oldkey=0,newKey=0,Operation=0;
    MinPriorityQueue PQ;
    EmptyQueue(PQ.isEmpty());
    for (int i=1;i<=100;i++)
    {
        Operation=rand()%4;
        PrintIterNum(i);
        switch (Operation)
        {
            case 0:
                cout<<"Randomly Selected Insert."<<endl;
                PQ.Insert(std::make_pair(GetRandom(1,1000),GetRandom(1,1000)));
                break;
            case 1:
                cout<<"Randomly Selected All Minimum."<<endl;
                if (!PQ.isEmpty())
                {
                    PQ.AllMinimum();
                }
                else
                    cout<<"The queue is empty."<<endl;
                break;
            case 2:
                cout<<"Randomly Selected Decrease Key."<<endl;
                if (!PQ.isEmpty())
                {
                    index=rand()%PQ.GetSize();
                    oldkey=PQ.GetPair(index).first;
                    newKey=rand()%oldkey+1;
                    PQ.DecreaseKey(index,newKey);
                }
                else
                    cout<<"The queue is empty."<<endl;
                break;
            case 3:
                cout<<"Randomly Selected Extract All Minimum."<<endl;
                if (!PQ.isEmpty())
                {
                    PQ.ExtractAllMin();
                }
                else
                    cout<<"The queue is empty."<<endl;
                break;
        }
        if (i%20==0)
        {
            PrintIterations(i);
            PrintQueue(PQ.GetQueue());
        }
    }
    return;
}
void TestCaseSix()
{
    cout<<endl<<"Test Case 6:\n";
    LeonardoHeap A(CreateSet(1000,1));
    A.SmoothSort();
    NumberOfCompare(A.GetComparisons());
    ShortenedList(A.GetHeap());
    return;
}
void TestCaseSeven()
{
    cout<<endl<<"Test Case 7:\n";
    LeonardoHeap A(CreateSet(1,2000));
    vector<int> vec=RandomDistinctNumebers(2000,20);
    int i=0;
    while (i<20)
    {
        int temp=vec.at(i);
        vec.at(i)=vec.at(i+1);
        vec.at(i+1)=temp;
        i=i+2;
    }
    A.SmoothSort();
    NumberOfCompare(A.GetComparisons());
    ShortenedList(A.GetHeap());
    return;
}
void TestCaseEight()
{
    cout<<endl<<"Test Case 8:\n";
    LeonardoHeap A(CreateSet(1,2000));
    vector<int> vec=RandomDistinctNumebers(2000,60);
    int i=0;
    while (i<20){
        int temp=vec.at(i);
        vec.at(i)=vec.at(i+1);
        vec.at(i+1)=temp;
        i=i+2;
    }
    A.SmoothSort();
    NumberOfCompare(A.GetComparisons());
    ShortenedList(A.GetHeap());
    return;
}
void TestCaseNine()
{
    cout<<endl<<"Test Case 9:\n";
    vector<int> createheap;
    for (int i=0;i<3193;i++)
        createheap.push_back(GetRandom(1,10000));
    LeonardoHeap A(createheap);
    A.SmoothSort();
    NumberOfCompare(A.GetComparisons());
    ShortenedList(A.GetHeap());
    return;
}
void TestCaseTen()
{
    cout<<endl<<"Test Case 10:\n";
    vector<int> createheap;
    for (int i=0;i<5166;i++)
        createheap.push_back(GetRandom(1,10000));
    LeonardoHeap A(createheap);
    A.SmoothSort();
    NumberOfCompare(A.GetComparisons());
    ShortenedList(A.GetHeap());
    return;
}
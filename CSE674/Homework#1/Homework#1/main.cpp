/*
 File Name: main.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Implements the three qestions on Homework #1
 and the test cases for ADS F2016
 
*/

#include <iostream>
#include <time.h>
#include "SingleList.h"
#include "DoubleList.h"
using namespace std;
void SingleTeamOfFour(SingleList *list);
void DoubleTeamOfFour(DoubleList *list);
void SingleReverse(SingleList *list);
void DoubleReverse(DoubleList *list);
void SingleShuffle(SingleList *list);
void DoubleShuffle(DoubleList *list);
void GenerateListOrdered(SingleList *sOrder, DoubleList *dOrder, int length);
void GenerateListRandom(SingleList *sRando, DoubleList *dRando, int length);
void TestCase1(SingleList *list);
void TestCase2(DoubleList *list);
void TestCase3(SingleList *list);
void TestCase4(DoubleList *list);
void TestCase5(SingleList *list);
void TestCase6(DoubleList *list);
void TestCase7(SingleList *list);
void TestCase8(DoubleList *list);
void TestCase9(SingleList *list);
void TestCase10(DoubleList *list);
void TestCase11(SingleList *list);
void TestCase12(DoubleList *list);
int main(int argc, const char * argv[])
{
    SingleList *sOrder, *sRando;
    DoubleList *dOrder, *dRando;
    sOrder=new SingleList();
    sRando=new SingleList();
    dOrder=new DoubleList();
    dRando=new DoubleList();
    GenerateListOrdered(sOrder,dOrder,100);
    GenerateListRandom(sRando, dRando, 100);
    cout<<"Skipping Test Case 1 & 2 as per Professor directions.\n";
    //TestCase1(sOrder);
    //TestCase2(dOrder);
    TestCase3(sRando);
    TestCase4(dRando);
    TestCase5(sOrder);
    TestCase6(dOrder);
    TestCase7(sRando);
    TestCase8(dRando);
    TestCase9(sOrder);
    TestCase10(dOrder);
    TestCase11(sRando);
    TestCase12(dRando);
    return 0;
}
void GenerateListOrdered(SingleList *sOrder, DoubleList *dOrder, int length)
{
    for (int i=1; i<=length;i++)
    {
        sOrder->insert(i);
        dOrder->insert(i);
    }
    sOrder->start();
    dOrder->start();
}
void GenerateListRandom(SingleList *sRando, DoubleList *dRando, int length)
{
    srand(time(NULL));
    int temp=0;
    for (int i=1; i<=length;i++)
    {
        temp = rand();
        while(dRando->contains(temp))
            temp = rand();
        SingleNode *insertSnode;
        DoubleNode *insertDnode;
        insertSnode= new SingleNode(temp,NULL);
        insertDnode= new DoubleNode(temp,NULL);
        dRando->insert(insertDnode);
        sRando->insert(insertSnode);
    }
    sRando->start();
    dRando->start();
}
void SingleTeamOfFour(SingleList *list)
{
    SingleList *temp,*sortList;
    temp = new SingleList();
    sortList = new SingleList();
    list->start();
    sortList->start();
    temp->start();
    int limit=list->length();
    for(int i=0; i<limit;i=i+4)
    {
        if(4>list->length())
        {
            int max=list->length();
            for(int j=0;j<max;j++)
                sortList->insert(list->remove_current_node());
        }
        else
            for(int j=0;j<4;j++)
                sortList->insert(list->remove_current_node());
        sortList->sort();
        sortList->start();
        int limit=sortList->length();
        for(int j=0;j<limit;j++)
            temp->insert(sortList->remove_current_node());
    }
    list->copy(temp);
    return;
}
void DoubleTeamOfFour(DoubleList *list)
{
    DoubleList *temp,*sortList;
    temp = new DoubleList();
    sortList = new DoubleList();
    list->start();
    sortList->start();
    temp->start();
    int limit=list->length();
    for(int i=0; i<limit;i=i+4)
    {
        if(4>list->length())
        {
            int max=list->length();
            for(int j=0;j<max;j++)
                sortList->insert(list->remove_current_node());
        }
        else
            for(int j=0;j<4;j++)
                sortList->insert(list->remove_current_node());
        sortList->sort();
        sortList->start();
        int limit=sortList->length();
        for(int j=0;j<limit;j++)
            temp->insert(sortList->remove_current_node());
    }
    list->copy(temp);
    return;
}
void SingleReverse(SingleList *list)
{
    SingleList *temp;
    temp = new SingleList();
    for(int i=0;list->length();i++)
    {
        list->start();
        for(int j=0;j<list->length()-1;j++)
        {
            list->advance();
        }
        temp->insert(list->remove_current_node());
    }
    list->copy(temp);
    return;
}
void DoubleReverse(DoubleList *list)
{
    DoubleList *temp;
    temp = new DoubleList();
    for(int i=0;list->length();i++)
    {
        list->start();
        for(int j=0;j<list->length()-1;j++)
        {
            list->advance();
        }
        temp->insert(list->remove_current_node());
    }
    list->copy(temp);
    return;
}
void SingleShuffle(SingleList *list)
{
    list->start();
    int indexer=0;
    if(list->length()%2==0)
        indexer=list->length()/2;
    else
        indexer=list->length()/2+1;
    SingleList *secondhalf;
    secondhalf = new SingleList();
    for (int i=0;i<indexer;i++)
        list->advance();
    int limit=list->length();
    for(int i=indexer;i<limit;i++)
        secondhalf->insert(list->remove_current_node());
    secondhalf->start();
    list->start();
    for(int i=0;i<limit/2;i++)
    {
        list->insert(secondhalf->remove_current_node());
        list->advance();
    }
    return;
}
void DoubleShuffle(DoubleList *list)
{
    list->start();
    int indexer=0;
    if(list->length()%2==0)
        indexer=list->length()/2;
    else
        indexer=list->length()/2+1;
    DoubleList *secondhalf;
    secondhalf = new DoubleList();
    for (int i=0;i<indexer;i++)
        list->advance();
    int limit=list->length();
    secondhalf->start();
    for(int i=indexer;i<limit;i++)
        secondhalf->insert(list->remove_current_node());
    secondhalf->start();
    list->start();
    for(int i=0;i<limit/2;i++)
    {
        list->insert(secondhalf->remove_current_node());
        list->advance();
    }
    return;
}
void TestCase1(SingleList *list)
{
    cout<<endl;
    cout<<"Test Case 1:\n";
    cout<<"Before Running \"Team of Four\" on a Singly Linked List S1:\n";
    list->Print();
    SingleTeamOfFour(list);
    cout<<"After Running \"Team of Four\" on a Singly Linked List S1:\n";
    list->Print();
}
void TestCase2(DoubleList *list)
{
    cout<<endl;
    cout<<"Test Case 2:\n";
    cout<<"Before Running \"Team of Four\" on a Doubly Linked List S1:\n";
    list->Print();
    DoubleTeamOfFour(list);
    cout<<"After Running \"Team of Four\" on a Doubly Linked List S1:\n";
    list->Print();
}
void TestCase3(SingleList *list)
{
    cout<<endl;
    cout<<"Test Case 3:\n";
    cout<<"Before Running \"Team of Four\" on a Singly Linked List S2:\n";
    list->Print();
    SingleTeamOfFour(list);
    cout<<"After Running \"Team of Four\" on a Singly Linked List S2:\n";
    list->Print();
}
void TestCase4(DoubleList *list)
{
    cout<<endl;
    cout<<"Test Case 4:\n";
    cout<<"Before Running \"Team of Four\" on a Doubly Linked List S2:\n";
    list->Print();
    DoubleTeamOfFour(list);
    cout<<"After Running \"Team of Four\" on a Doubly Linked List S2:\n";
    list->Print();
}
void TestCase5(SingleList *list)
{
    cout<<endl;
    cout<<"Test Case 5:\n";
    cout<<"Before Running \"Reverse\" on a Singly Linked List S1:\n";
    list->Print();
    SingleReverse(list);
    cout<<"After Running \"Reverse\" on a Singly Linked List S1:\n";
    list->Print();
}
void TestCase6(DoubleList *list)
{
    cout<<endl;
    cout<<"Test Case 6:\n";
    cout<<"Before Running \"Reverse\" on a Doubly Linked List S1:\n";
    list->Print();
    DoubleReverse(list);
    cout<<"After Running \"Reverse\" on a Doubly Linked List S1:\n";
    list->Print();
}
void TestCase7(SingleList *list)
{
    cout<<endl;
    cout<<"Test Case 7:\n";
    cout<<"Before Running \"Reverse\" on a Singly Linked List S2:\n";
    list->Print();
    SingleReverse(list);
    cout<<"After Running \"Reverse\" on a Singly Linked List S2:\n";
    list->Print();
}
void TestCase8(DoubleList *list)
{
    cout<<endl;
    cout<<"Test Case 8:\n";
    cout<<"Before Running \"Reverse\" on a Doubly Linked List S2:\n";
    list->Print();
    DoubleReverse(list);
    cout<<"After Running \"Reverse\" on a Doubly Linked List S2:\n";
    list->Print();

}
void TestCase9(SingleList *list)
{
    cout<<endl;
    cout<<"Test Case 9:\n";
    cout<<"Before Running \"Shuffle\" on a Singly Linked List S1:\n";
    list->Print();
    SingleShuffle(list);
    cout<<"After Running \"Shuffle\" on a Singly Linked List S1:\n";
    list->Print();
}
void TestCase10(DoubleList *list)
{
    cout<<endl;
    cout<<"Test Case 10:\n";
    cout<<"Before Running \"Shuffle\" on a Doubly Linked List S1:\n";
    list->Print();
    DoubleShuffle(list);
    cout<<"After Running \"Shuffle\" on a Doubly Linked List S1:\n";
    list->Print();

}
void TestCase11(SingleList *list)
{
    cout<<endl;
    cout<<"Test Case 11:\n";
    cout<<"Before Running \"Shuffle\" on a Singly Linked List S2:\n";
    list->Print();
    SingleShuffle(list);
    cout<<"After Running \"Shuffle\" on a Singly Linked List S2:\n";
    list->Print();
}
void TestCase12(DoubleList *list)
{
    cout<<endl;
    cout<<"Test Case 12:\n";
    cout<<"Before Running \"Shuffle\" on a Doubly Linked List S2:\n";
    list->Print();
    DoubleShuffle(list);
    cout<<"After Running \"Shuffle\" on a Doubly Linked List S2:\n";
    list->Print();
}
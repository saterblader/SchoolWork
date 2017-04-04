/*
 File Name: main.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Main.cpp for Homework #3 for
 ADS F2016 Syracuse University
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include "BST.h"
#include "KDTree.h"
void TestCase1();
void TestCase2();
void TestCase3();
void TestCase4();
void TestCase5();
void TestCase6();
void TestCase7();
void TestCase8();
using namespace std;
int main(int argc, const char * argv[])
{
    srand(time(NULL));
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    TestCase6();
    TestCase7();
    TestCase8();
    return 0;
}

void TestCase1()
{
    BST List1;
    int k=int(), kprev=int(), kprevprev=int();
    cout<<"Running Test Case #1\n";
    cout<<"\tCreating List 1\n";
    for(int i=0;i<16;i++)
    {
        if(i==0)
        {
            k=0;
            kprevprev=0;
            List1.insert(k, i);
        }
        else if(i==1)
        {
            k=1000;
            kprev=1000;
            List1.insert(k, i);
        }
        else
        {
            k=floor(((kprev+kprevprev)/2));
            kprevprev=kprev;
            kprev=k;
            List1.insert(k, i);
        }
            
    }
    List1.show("t1.dot");
    cout<<"\tFile t1.dot created\n";
    return;
}
void TestCase2()
{
    KDTree List2;
    int x=int(), y=int(), xprev=int(), xprevprev=int();
    cout<<"Running Test Case #2\n";
    cout<<"\tCreating List 2\n";
    for(int i=0;i<16;i++)
    {
        if(i==0)
        {
            x=0;
            xprevprev=0;
            y=500-x;
            List2.insert(x,y,i);
        }
        else if(i==1)
        {
            x=500;
            xprev=500;
            y=500-x;
            List2.insert(x, y, i);
        }
        else
        {
            x=floor(((xprev+xprevprev)/2));
            xprevprev=xprev;
            xprev=x;
            y=500-x;
            List2.insert(x, y, i);
        }
        
    }
    List2.show("t2.dot");
    cout<<"\tFile t2.dot created\n";
    return;
}
void TestCase3()
{
    BST List3;
    int k=int();
    cout<<"Running Test Case #3\n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<"n= No. of Nodes in the Tree\t\tHeight of BST T3\tlgn\tsqrt(n)\n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<right<<setw(27)<<setfill(' ')<<"0"<<"\t"<<right<<setw(20)<<setfill(' ')<<List3.height()<<"\t"<<right<<setw(9)<<setfill(' ')<<"N.A."<<"\t"<<sqrt(0)<<endl;
    for (int i=0;i<200;i++)
    {
        k=rand()%1000;
        while (List3.search(k)!=NULL)
              k=rand()%1000;
        List3.insert(k, i);
        if(i%20==0 && i!=0)
        {
            cout<<right<<setw(27)<<setfill(' ')<<i<<"\t"<<right<<setw(20)<<setfill(' ')<<List3.height()<<"\t"<<right<<setw(9)<<setfill(' ')<<log2(i)<<"\t"<<sqrt(i)<<endl;
        }
        
    }
    cout<<right<<setw(27)<<setfill(' ')<<"200"<<"\t"<<right<<setw(20)<<setfill(' ')<<List3.height()<<"\t"<<right<<setw(9)<<setfill(' ')<<log2(200)<<"\t"<<sqrt(200)<<endl;
    cout<<"-------------------------------------------------------------------------------------------\n";
    //List3.show("T3.dot");
    return;
}
void TestCase4()
{
    KDTree List4;
    int x=int(), y=int(), r=int();
    cout<<"Running Test Case #4\n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<"n= No. of Nodes in the Tree\t\tHeight of BST T4\tlgn\tsqrt(n)\n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<right<<setw(27)<<setfill(' ')<<"0"<<"\t"<<right<<setw(20)<<setfill(' ')<<List4.height()<<"\t"<<right<<setw(9)<<setfill(' ')<<"N.A."<<"\t"<<sqrt(0)<<endl;
    for (int i=0;i<200;i++)
    {
        r=rand();
        x=r%1000;
        y=(r%1000)+50;
        while (List4.search(x,y)!=NULL)
        {
            r=rand();
            x=r%1000;
            y=(r%1000)+50;
        }
        List4.insert(x,y, i);
        if(i%20==0 && i!=0)
        {
            cout<<right<<setw(27)<<setfill(' ')<<i<<"\t"<<right<<setw(20)<<setfill(' ')<<List4.height()<<"\t"<<right<<setw(9)<<setfill(' ')<<log2(i)<<"\t"<<sqrt(i)<<endl;
        }
        
    }
    cout<<right<<setw(27)<<setfill(' ')<<"200"<<"\t"<<right<<setw(20)<<setfill(' ')<<List4.height()<<"\t"<<right<<setw(9)<<setfill(' ')<<log2(200)<<"\t"<<sqrt(200)<<endl;
    cout<<"-------------------------------------------------------------------------------------------\n";
    //List4.show("T4.dot");
    return;
}
void TestCase5()
{
    BST List5, List1;
    int k=int(), kprev=int(), kprevprev=int();
    cout<<"Running Test Case #5\n";
    for(int i=0;i<16;i++)
    {
        if(i==0)
        {
            k=0;
            kprevprev=0;
            List1.insert(k, i);
        }
        else if(i==1)
        {
            k=1000;
            kprev=1000;
            List1.insert(k, i);
        }
        else
        {
            k=floor(((kprev+kprevprev)/2));
            kprevprev=kprev;
            kprev=k;
            List1.insert(k, i);
        }
        
    }
    cout<<"\tCreating List 5\n";
    for(int i=0; i<10;i++)
    {
        BSTNode *insert;
        insert=new BSTNode();
        int r=rand()%1000;
        insert=List1.search(r);
        while(insert==NULL)
        {
            r=rand()%1000;
            insert=List1.search(r);
        }
        while(List5.search(insert->_key)!=NULL)
        {
            insert=NULL;
            while(insert==NULL)
            {
                r=rand()%1000;
                insert=List1.search(r);
            }
        }
        List5.insert(insert);
    }
    cout<<"\tMaking t5-a.dot\n";
    List5.show("t5-a.dot");
    cout<<"\t\tRemoving the head of List 5\n";
    BSTNode *head;
    head=new BSTNode();
    head=List5.getHead();
    List5.deleteKey(head->_key);
    cout<<"\tMaking t5-b.dot\n";
    List5.show("t5-b.dot");
    return;
}
void TestCase6()
{
    KDTree List6, List2;
    int x=int(), y=int(), xprev=int(), xprevprev=int();
    cout<<"Running Test Case #6\n";
    for(int i=0;i<16;i++)
    {
        if(i==0)
        {
            x=0;
            xprevprev=0;
            y=500-x;
            List2.insert(x,y,i);
        }
        else if(i==1)
        {
            x=500;
            xprev=500;
            y=500-x;
            List2.insert(x, y, i);
        }
        else
        {
            x=floor(((xprev+xprevprev)/2));
            xprevprev=xprev;
            xprev=x;
            y=500-x;
            List2.insert(x, y, i);
        }
        
    }
    cout<<"\tCreating List 6\n";
    for(int i=0; i<10;i++)
    {
        KDNode *insert;
        insert=new KDNode();
        x=rand()%500;
        y=500-x;
        insert=List2.search(x,y);
        while(insert==NULL)
        {
            x=rand()%500;
            y=500-x;
            insert=List2.search(x,y);
        }
        while(List6.search(insert->_x, insert->_y)!=NULL)
        {
            insert=NULL;
            while(insert==NULL)
            {
                x=rand()%500;
                y=500-x;
                insert=List2.search(x,y);
            }
        }
        List6.insert(insert);
    }
    cout<<"\tMaking t6-a.dot\n";
    List6.show("t6-a.dot");
    cout<<"\t\tRemoving the head of List 6\n";
    KDNode *head;
    head=new KDNode();
    head=List6.getHead();
    List6.deleteKey(head->_x,head->_y);
    cout<<"\tMaking t6-b.dot\n";
    List6.show("t6-b.dot");
    return;
}
void TestCase7()
{
    int d=int();
    BST List7;
    cout<<"Running Test Case #7\n";
    for(int i=1;i<=10;i++)
    {
        List7.insert(i,d);
        d++;
    }
    cout<<"\tCreating List 7\n";
    for(int i=1;i<=10;i++)
    {
        List7.insert(i,d);
        d++;
    }
    //List7.show("t7.dot");
    cout<<"-------------------------------------------------------------------------------------------\n";
    cout<<"Stage\t Data item at root\t The root (after deletion)\t Search for data with key\n";
    cout<<"-------------------------------------------------------------------------------------------\n";
    for(int i=0;i<=20;i++)
    {
        BSTNode *head, *newhead,*search;
        head=new BSTNode();
        newhead=new BSTNode();
        search=new BSTNode();
        head=List7.getHead();
        if(head==NULL)
        {
            cout<<right<<setw(5)<<setfill(' ')<<i<<"\t"<<right<<setw(15)<<setfill(' ')<<"nil\t";
            newhead=NULL;
            search=NULL;
        }
        else
        {
            cout<<right<<setw(5)<<setfill(' ')<<i<<"\t"<<right<<setw(12)<<setfill(' ')<<"["<<head->_key<<", "<<head->_value<<"]\t";
        List7.deleteKey(head->_key);
        search=List7.search(head->_key);
        newhead=List7.getHead();
        }
        if(newhead!=NULL && search!=NULL)
        cout<<setw(20)<<setfill(' ')<<"["<<newhead->_key<<", "<<newhead->_value<<"]\t"<<setw(19)<<setfill(' ')<<"["<<search->_key<<", "<<search->_value<<"]\n";
        else if (newhead==NULL && search==NULL && head==NULL)
            cout<<right<<setw(31)<<setfill(' ')<<"nil\t"<<right<<setw(30)<<setfill(' ')<<"nil\n";
        else if (newhead==NULL && search==NULL)
            cout<<right<<setw(23)<<setfill(' ')<<"nil\t"<<right<<setw(30)<<setfill(' ')<<"nil\n";
        else if(search==NULL)
            cout<<right<<setw(20)<<setfill(' ')<<"["<<newhead->_key<<", "<<newhead->_value<<"]\t"<<right<<setw(22)<<setfill(' ')<<"nil\n";
        else if(newhead==NULL)
            cout<<setw(23)<<setfill(' ')<<"nil\t"<<setw(21)<<setfill(' ')<<"["<<search->_key<<", "<<search->_value<<"]\n";
    }
    cout<<"-------------------------------------------------------------------------------------------\n";
    return;
}
void TestCase8()
{
    KDTree List8;
    cout<<"Running Test Case #8\n";
    cout<<"\tCreating List 8\n";
    for(int i=1;i<=6;i++)
    {
        List8.insert(i, i, i);
    }
    for(int i=1;i<=6;i++)
    {
        List8.insert(i, i+6, i+6);
    }
    for(int i=1;i<=6;i++)
    {
        List8.insert(i+6, i, i+12);
    }
    int i=1, count=0;
    //List8.show("t8.dot");
    while((List8.getHead())!=NULL)
    {
        KDNode *head;
        head=new KDNode();
        head=List8.getHead();
        List8.deleteKey(head->_x,head->_y);
        cout<<"\t\tRemoving the head of List 8\n";
        count++;
        if(List8.getHead()==NULL)
        {
            cout<<"List 8 is now empty\n";
            break;
        }
        KDNode *search;
        if(i<=6)
        {
            search=List8.search(i, i);
            if(search!=NULL)
                cout<<"Item L"<<i<<" is present\n"<<"\t["<<search->_x<<", "<<search->_y<<", "<<search->_value<<"]\n";
            //else
                //cout<<"Item L"<<i<<" is not present\n";
            
        }
        else if(i>6 && i<=12)
        {
            search=List8.search(i-6, i);
            if(search!=NULL)
                cout<<"Item L"<<i<<" is present\n"<<"\t["<<search->_x<<", "<<search->_y<<", "<<search->_value<<"]\n";
            //else
                //cout<<"Item L"<<i<<" is not present\n";
        }
        else if(i>12&& i<=18)
        {
            search=List8.search(i-6, i-12);
            if(search!=NULL)
                cout<<"Item L"<<i<<" is present\n"<<"\t["<<search->_x<<", "<<search->_y<<", "<<search->_value<<"]\n";
            //else
                //cout<<"Item L"<<i<<" is not present\n";
        }
        i++;
        if(count==6)
        {
            cout<<"Making t8-a.dot\n";
            List8.show("t8-a.dot");
        }
        else if(count==12)
        {
            cout<<"Making t8-b.dot\n";
            List8.show("t8-b.dot");
        }
    }
    
    return;
}

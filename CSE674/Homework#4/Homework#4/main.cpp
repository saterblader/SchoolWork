/*
 File Name: main.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Main.cpp for Homework #4 for
 ADS F2016 Syracuse University
*/

#include <iostream>
#include "Graph.h"
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <vector>

using namespace std;

void TestCase1();
void TestCase2();
void TestCase3();
void TestCase4();
void TestCase5();
void TestCase6();
void TestCase7();
void TestCase8();
void TestCase9();
void TestCase10();
void TestCase11();
void TestCase12();

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
    TestCase9();
    TestCase10();
    TestCase11();
    TestCase12();
    return 0;
}

void TestCase1()
{
    cout<<"Running Test Case #1\n";
    cout<<"Creating Graph object...\n";
    Graph G1("fig1.csv");
    cout<<"Creating t1.dot based off object G1\n";
    G1.show("t1.dot");
    cout<<endl;
    return;
}

void TestCase2()
{
    cout<<"Running Test Case #2\n";
    cout<<"Creating Graph object...\n";
    Graph G2("fig2.csv");
    cout<<"Creating t2.dot based off object G2\n";
    G2.show("t2.dot");
    cout<<endl;
    return;
}

void TestCase3()
{
    cout<<"Running Test Case #3\n";
    cout<<"Creating Graph object...\n";
    Graph G3("fig3-w.csv");
    cout<<"Creating t3.dot based off object G3\n";
    G3.show("t3.dot");
    cout<<endl;
    return;
}

void TestCase4()
{
    cout<<"Running Test Case #4\n";
    cout<<"Creating Graph G1...\n";
    Graph G1("fig1.csv");
    cout<<"Inserting vertex z\n";
    G1.insert_vertex("z");
    cout<<"Inserting edges (z,w), (z,x), (z,y)\n";
    G1.insert_edge("z","w");
    G1.insert_edge("z","x");
    G1.insert_edge("z","y");
    cout<<"Creating t4a.dot based off object G1\n";
    G1.show("t4a.dot");
    cout<<"Removing vertex s\n";
    G1.remove_vertex("s");
    cout<<"Removing vertex x\n";
    G1.remove_vertex("x");
    cout<<"Removing edge (u,t)\n";
    G1.remove_edge("u","t");
    cout<<"Creating t4b.dot based off object G1\n";
    G1.show("t4b.dot");
    cout<<endl;
    return;
}

void TestCase5()
{
    cout<<"Running Test Case #5\n";
    cout<<"Creating Graph Ue...\n";
    Graph Ue;
    cout<<"Inserting vertexs 6, ..., 10\n";
    for(int i=6;i<=10;i++)
    {
        Ue.insert_vertex(to_string(i));
    }
    cout<<"Inserting edges (6,7), (7,8), (8,9), (9,10), (10,6)\n";
    Ue.insert_edge("6", "7");
    Ue.insert_edge("7", "8");
    Ue.insert_edge("8", "9");
    Ue.insert_edge("9", "10");
    Ue.insert_edge("10", "6");
    cout<<"Inserting vertexs 1, ..., 5\n";
    for(int i=1;i<=5;i++)
    {
        Ue.insert_vertex(to_string(i));
    }
    cout<<"Inserting edges (1,6), (2,7), (3,8), (4,9), (5,10)\n";
    Ue.insert_edge("1", "6");
    Ue.insert_edge("2", "7");
    Ue.insert_edge("3", "8");
    Ue.insert_edge("4", "9");
    Ue.insert_edge("5", "10");
    cout<<"Creating t5a.dot based off object Ue\n";
    Ue.show("t5a.dot");
    cout<<"Removing vertex 8\n";
    Ue.remove_vertex("8");
    cout<<"Removing vertex 6\n";
    Ue.remove_vertex("6");
    cout<<"Creating t5b.dot based off object Ue\n";
    Ue.show("t5b.dot");
    cout<<endl;
    return;
}

void TestCase6()
{
    vector<string> vertices;
    cout<<"Running Test Case #6\n";
    cout<<"Creating Directed Graph De...\n";
    Graph De;
    De.setDirected();
    for(int i=1;i<=5;i++)
    {
        vertices.push_back(to_string(i*2));
    }
    int r=0;
    cout<<endl;
    cout<<"Inserting vertices 2, 4, 6, 8, 10 in a random order\n";
    while(vertices.size()!=0)
    {
        r=rand()%vertices.size();
        De.insert_vertex(vertices[r]);
        cout<<"Inserting vertex "<<vertices[r]<<endl;
        vertices.erase(vertices.begin()+r);
    }
    cout<<"Inserting edges (2,4), (2,6), (4,6), (4,8), (6,8), (6,10), (8,10), (8,2)\n";
    De.insert_edge("2","4");
    De.insert_edge("2","6");
    De.insert_edge("4","6");
    De.insert_edge("4","8");
    De.insert_edge("6","8");
    De.insert_edge("6","10");
    De.insert_edge("8","10");
    De.insert_edge("8","2");
    for(int i=1;i<=5;i++)
    {
        vertices.push_back(to_string(i*2-1));
    }
    r=0;
    cout<<endl;
    cout<<"Inserting vertices 1, 3, 5, 7, 9 in a random order\n";
    while(vertices.size()!=0)
    {
        r=rand()%vertices.size();
        De.insert_vertex(vertices[r]);
        cout<<"Inserting vertex "<<vertices[r]<<endl;
        vertices.erase(vertices.begin()+r);
    }
    cout<<"Inserting edges (1,2), (3,4), (5,6), (7,8), (9,10)\n";
    De.insert_edge("1","2");
    De.insert_edge("3","4");
    De.insert_edge("5","6");
    De.insert_edge("7","8");
    De.insert_edge("9","10");
    cout<<endl;
    cout<<"Creating t6a.dot based off object De\n";
    De.show("t6a.dot");
    for(int i=1;i<=5;i++)
    {
        vertices.push_back(to_string(i*2));
    }
    cout<<"Randomly selecting a vertex from 2, 4, 6, 8, 10 to remove\n";
    r=rand()%vertices.size();
    cout<<"Randomly selected "<<vertices[r]<<" for removal\n";
    De.remove_vertex(vertices[r]);
    vertices.clear();
    for(int i=1;i<=5;i++)
    {
        vertices.push_back(to_string(i*2-1));
    }
    cout<<"Randomly selecting a vertex from 1, 3, 5, 7, 9 to remove\n";
    r=rand()%vertices.size();
    cout<<"Randomly selected "<<vertices[r]<<" for removal\n";
    De.remove_vertex(vertices[r]);
    vertices.clear();
    cout<<"Creating t6b.dot based off object De\n";
    De.show("t6b.dot");
    cout<<endl;
    return;
}

void TestCase7()
{
    cout<<"Running Test Case #7\n";
    cout<<"Creating Directed and weighted Graph G3...\n";
    Graph G3("fig3-w.csv");
    cout<<"-------------------------------------------\n";
    for(int i=0;i<G3.getSizeOfGraph();i++)
    {
        cout<<"\t"<<G3.getVertexName(i);
    }
    cout<<endl;
    cout<<"-------------------------------------------\n";
    for(int i=0;i<G3.getSizeOfGraph();i++)
    {
        cout<<G3.getVertexName(i);
        vector<int> dist;
        dist=G3.Dijkstra(G3.getVertexName(i));
        for(int j=0;j<dist.size();j++)
        {
            cout<<"\t"<<dist[j];
        }
        cout<<endl;
    }
    cout<<"-------------------------------------------\n";
    cout<<endl;
    return;
}

void TestCase8()
{
    cout<<"Running Test Case #8\n";
    cout<<"Creating Undirected and weighted Graph G4...\n";
    Graph G4("fig3-w.csv",true);
    cout<<"-------------------------------------------\n";
    for(int i=0;i<G4.getSizeOfGraph();i++)
    {
        cout<<"\t"<<G4.getVertexName(i);
    }
    cout<<endl;
    cout<<"-------------------------------------------\n";
    for(int i=0;i<G4.getSizeOfGraph();i++)
    {
        cout<<G4.getVertexName(i);
        vector<int> dist;
        dist=G4.Dijkstra(G4.getVertexName(i));
        for(int j=0;j<dist.size();j++)
        {
            cout<<"\t"<<dist[j];
        }
        cout<<endl;
    }
    cout<<"-------------------------------------------\n";
    cout<<endl;
    return;
}

void TestCase9()
{
    cout<<"Running Test Case #9\n";
    cout<<"Creating Directed and weighted Graph G3...\n";
    Graph G3("fig3-w.csv");
    G3.Dijkstra("s");
    cout<<"--------------------------------------------------------------\n";
    cout<<"Vertex\tThe path from source vertex s to this vertex in G3\n";
    cout<<"--------------------------------------------------------------\n";
    for(int i=0;i<G3.getSizeOfGraph();i++)
    {
        cout<<G3.getVertexName(i)<<"\t";
        vector<char> row;
        row=G3.getPath(i);
        if(row.size()==1)
            cout<<"nil";
        else
            for(int j=1; j<row.size();j++)
            {
                if(j>1)
                    cout<<"->"<<row[j];
                else
                    cout<<row[j];
            }
        
        cout<<endl;
    }
    G3.Dijkstra("z");
    cout<<"--------------------------------------------------------------\n";
    cout<<"Vertex\tThe path from source vertex z to this vertex in G3\n";
    cout<<"--------------------------------------------------------------\n";
    for(int i=0;i<G3.getSizeOfGraph();i++)
    {
        cout<<G3.getVertexName(i)<<"\t";
        vector<char> row;
        row=G3.getPath(i);
        if(row.size()==1)
            cout<<"nil";
        else
            for(int j=1; j<row.size();j++)
            {
                if(j>1)
                    cout<<"->"<<row[j];
                else
                    cout<<row[j];
            }
        cout<<endl;
    }
    cout<<endl;
    return;
}

void TestCase10()
{
    cout<<"Running Test Case #10\n";
    cout<<"Creating undirected and weighted Graph G4...\n";
    Graph G4("fig3-w.csv",true);
    G4.Dijkstra("s");
    cout<<"--------------------------------------------------------------\n";
    cout<<"Vertex\tThe path from source vertex s to this vertex in G4\n";
    cout<<"--------------------------------------------------------------\n";
    for(int i=0;i<G4.getSizeOfGraph();i++)
    {
        cout<<G4.getVertexName(i)<<"\t";
        vector<char> row;
        row=G4.getPath(i);
        if(row.size()==1)
            cout<<"nil";
        else
            for(int j=1; j<row.size();j++)
            {
                if(j>1)
                    cout<<"->"<<row[j];
                else
                    cout<<row[j];
            }
        
        cout<<endl;
    }
    G4.Dijkstra("z");
    cout<<"--------------------------------------------------------------\n";
    cout<<"Vertex\tThe path from source vertex z to this vertex in G4\n";
    cout<<"--------------------------------------------------------------\n";
    for(int i=0;i<G4.getSizeOfGraph();i++)
    {
        cout<<G4.getVertexName(i)<<"\t";
        vector<char> row;
        row=G4.getPath(i);
        if(row.size()==1)
            cout<<"nil";
        else
            for(int j=1; j<row.size();j++)
            {
                if(j>1)
                    cout<<"->"<<row[j];
                else
                    cout<<row[j];
            }
        cout<<endl;
    }
    cout<<endl;
    return;
}

void TestCase11()
{
    cout<<"Running Test Case #11\n";
    cout<<"Creating Directed and weighted Graph G3...\n";
    Graph G3("fig3-w.csv");
    int max=0, stringmax=0,rowmax=0,pos1=-1,pos2=-1,pos3=-1;
    for(int i=0;i<G3.getSizeOfGraph();i++)
    {
        cout<<G3.getVertexName(i);
        vector<int> dist;
        dist=G3.Dijkstra(G3.getVertexName(i));
        rowmax=0;
        for(int j=0;j<dist.size();j++)
        {
            if(dist[j]>rowmax)
            {
                rowmax=dist[j];
                pos3=j;
            }
        }
        if(rowmax>stringmax)
        {
            stringmax=rowmax;
            pos2=pos3;
        }
        if(stringmax>max)
        {
            max=stringmax;
            pos1=i;
        }
    }
    cerr<<flush<<"<-ignore this, cleaning out cout"<<endl;
    G3.Dijkstra(G3.getVertexName(pos1));
    vector<char> row;
    row=G3.getPath(pos2);
    cout<<"Most expensive shortest path is:\n";
    for(int j=0; j<row.size();j++)
    {
        if(j>0)
            cout<<"->"<<row[j];
        else
            cout<<row[j];
    }
    cout<<endl;
    cout<<"Creating file t11.dot with most expensive shortest path lined in red\n";
    G3.show("t11.dot",true,"red",pos2);
    cout<<endl;
    return;
}

void TestCase12()
{
    cout<<"Running Test Case #12\n";
    cout<<"Creating Undirected and weighted Graph G4...\n";
    Graph G4("fig3-w.csv",true);
    int max=0, stringmax=0,rowmax=0,pos1=-1,pos2=-1,pos3=-1;
    for(int i=0;i<G4.getSizeOfGraph();i++)
    {
        cout<<G4.getVertexName(i);
        vector<int> dist;
        dist=G4.Dijkstra(G4.getVertexName(i));
        rowmax=0;
        for(int j=0;j<dist.size();j++)
        {
            if(dist[j]>rowmax)
            {
                rowmax=dist[j];
                pos3=j;
            }
        }
        if(rowmax>stringmax)
        {
            stringmax=rowmax;
            pos2=pos3;
        }
        if(stringmax>max)
        {
            max=stringmax;
            pos1=i;
        }
    }
    cerr<<flush<<"<-ignore this, cleaning out cout"<<endl;
    G4.Dijkstra(G4.getVertexName(pos1));
    vector<char> row;
    row=G4.getPath(pos2);
    cout<<"Most expensive shortest path is:\n";
    for(int j=0; j<row.size();j++)
    {
        if(j>0)
            cout<<"--"<<row[j];
        else
            cout<<row[j];
    }
    cout<<endl;
    cout<<"Creating file t12.dot with most expensive shortest path lined in blue\n";
    G4.show("t12.dot",true,"blue",pos2);
    cout<<endl;
    return;
}
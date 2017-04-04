/*
 File Name: main.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Graph.h for Homework #4 for
 ADS F2016 Syracuse University
*/


#ifndef Graph_H
#define Graph_H

#include <stdio.h>
#include <string>
#include <vector>
struct node
{
    std::string _vertex;
    int _weight;
    node *link;
};

class Graph
{
public:
    Graph();
    Graph(std::string Filename,bool undirected=false);
    void setDirected();
    void setWeighted();
    void insert_vertex(std::string v);
    void remove_vertex(std::string v);
    void insert_edge(std::string v1, std::string v2, int weight=1);
    void remove_edge(std::string v1, std::string v2);
    void show(std::string FileName, bool path=false, std::string color="black", int row=0);
    void CreateGraphFromCSV(std::string Filename,bool undirected=false);
    std::vector<int> Dijkstra(std::string startNode);
    std::string getVertexName(int i);
    int getSizeOfGraph();
    std::vector<char> getPath(int i);
    
private:
    bool _weighted;
    bool _directed;
    std::vector<node> _graph;
    std::string _path[20];
    std::vector<std::vector<char>> _pathvec;
};

#endif

/*
 File Name: Graph.cpp
 Author: Philip D. Geramian
 Author Contact: pdgerami@syr.edu
 
 About:
 Grpah.cpp for Homework #4 for
 ADS F2016 Syracuse University
*/


#include "Graph.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "MinHeapHW4.h"


Graph::Graph()
{
    _weighted=false;
    _directed=false;
    
}

Graph::Graph(std::string Filename, bool undirected)
{
    CreateGraphFromCSV(Filename,undirected);
}

void Graph::setDirected()
{
    _directed=true;
    return;
}

void Graph::setWeighted()
{
    _directed=true;
    _weighted=true;
    return;
}

void Graph::insert_vertex(std::string v)
{
    node *insert;
    insert=new node();
    insert->_vertex=v;
    insert->link=NULL;
    insert->_weight=0;
    _graph.push_back(*insert);
    return;
}

void Graph::remove_vertex(std::string v)
{
    int i=0;
    bool found=false;
    for(i=0;i<_graph.size();i++)
    {
        if(_graph[i]._vertex!=v)
            remove_edge(_graph[i]._vertex, v);
    }
    for(i=0;i<_graph.size();i++)
    {
        if(_graph[i]._vertex!=v)
            remove_edge(v,_graph[i]._vertex);
    }
    i=0;
    while(!found)
    {
        if(_graph[i]._vertex==v)
        {
            _graph.erase(_graph.begin()+i);
            found=true;
        }
        i++;
    }
    return;
}

void Graph::insert_edge(std::string v1, std::string v2, int weight)
{
    node *_v2, *index;
    bool found=false;
    int i=0;
    _v2=new node();
    _v2->_vertex=v2;
    _v2->link=NULL;
    _v2->_weight=weight;
    if(!_directed)
    {
        node *_v1;
        _v1=new node();
        _v1->_vertex=v1;
        _v1->link=NULL;
        _v1->_weight=weight;
        while(!found)
        {
            if(_graph[i]._vertex==v1)
            {
                found=true;
                index=&_graph[i];
                while(index->link!=NULL)
                    index=index->link;
                index->link=_v2;
            }
            else i++;
        }
        found=false;
        i=0;
        while(!found)
        {
            if(_graph[i]._vertex==v2)
            {
                found=true;
                index=&_graph[i];
                while(index->link!=NULL)
                    index=index->link;
                index->link=_v1;
            }
            else i++;
        }
    }
    else
    {
        while(!found)
        {
            if(_graph[i]._vertex==v1)
            {
                found=true;
                index=&_graph[i];
                while(index->link!=NULL)
                    index=index->link;
                index->link=_v2;
            }
            else i++;
        }
    }
    return;
}

void Graph::remove_edge(std::string v1, std::string v2)
{
    node *index,*prev,*toDelete;
    bool found=false;
    int i=0;
    if(!_directed)
    {
        while(!found)
        {
            if(_graph[i]._vertex==v1)
            {
                found=true;
                index=&_graph[i];
                prev=&_graph[i];
                while(index!=NULL && index->_vertex!=v2)
                {
                    prev=index;
                    index=index->link;
                }
                if(index!=NULL)
                {
                    toDelete=index;
                    prev->link=index->link;
                    toDelete->link=NULL;
                    delete toDelete;
                }
            }
            else i++;
        }
        found=false;
        i=0;
        while(!found)
        {
            if(_graph[i]._vertex==v2)
            {
                found=true;
                index=&_graph[i];
                prev=&_graph[i];
                while(index!=NULL && index->_vertex!=v1)
                {
                    prev=index;
                    index=index->link;
                }
                if(index!=NULL)
                {
                    toDelete=index;
                    prev->link=index->link;
                    toDelete->link=NULL;
                    delete toDelete;
                }
            }
            else i++;
        }
    }
    else
    {
        while(!found)
        {
            if(_graph[i]._vertex==v1)
            {
                found=true;
                index=&_graph[i];
                prev=&_graph[i];
                while(index!=NULL && index->_vertex!=v2)
                {
                    prev=index;
                    index=index->link;
                }
                if(index!=NULL)
                {
                    toDelete=index;
                    prev->link=index->link;
                    toDelete->link=NULL;
                    delete toDelete;
                }
            }
            else i++;
        }
    }
    return;
}

void Graph::show(std::string FileName, bool path, std::string color, int row)
{
    std::ofstream output;
    bool found=false;
    node *next;
    output.open(FileName);
    int j=0;
    if(_directed)
        output<<"strict digraph G{"<<std::endl;
    else
        output<<"strict graph G{"<<std::endl;
    for(int i=0;i<_graph.size();i++)
    {
        next=_graph[i].link;
        bool printed=false;
        while(next!=NULL)
        {
            if(!_directed)
            {
                for(j=0;j<=i;j++)
                    if(_graph[j]._vertex==next->_vertex)
                        found=true;
                if(!found)
                {
                    output<<_graph[i]._vertex<<"--"<<next->_vertex;
                    printed=true;
                }
            }
            else
            {
                output<<_graph[i]._vertex<<"->"<<next->_vertex;
                printed=true;
            }
            if(_weighted && printed==true)
                output<<"[label=\""<<next->_weight<<"\"]";
            if(!_directed && found==false)
            {
                
                output<<"[arrowhead = none]"<<std::endl;
            }
            else if (_directed)
                output<<std::endl;
            found=false;
            printed=false;
            next=next->link;
        }
        if(next==NULL && j==0)
            output<<_graph[i]._vertex<<std::endl;
        j=0;
    }
    if(path)
    {
        if(_pathvec[row].size()>1)
            for(int j=0;j<_pathvec[row].size();j++)
                if(j!=_pathvec[row].size()-1)
                {
                    if(_directed)
                    output<<_pathvec[row][j]<<"->"<<_pathvec[row][j+1]<<"[color="<<color;
                    else if(!_directed)
                        output<<_pathvec[row][j]<<"--"<<_pathvec[row][j+1]<<"[color="<<color;
                    output<<"]\n";
                }
    }
    output<<"}"<<std::endl;
    output.close();
    return;
}

void Graph::CreateGraphFromCSV(std::string Filename, bool unweighted)
{
    std::vector<std::vector <char>> data;
    char inDat;
    std::ifstream input;
    input.open(Filename);
    if(!input.good())
    {
        std::cout<<"File: "<<Filename<<" not found. Aborting\n";
        input.close();
        return;
    }
    
    while(input.good())
    {
        input.get(inDat);
        std::vector<char> line;
        while(inDat!='\0' && inDat!='\n')
        {
            line.push_back(inDat);
            input.get(inDat);
        }
        if(line.size()!=0)
            data.push_back(line);
        
    }
    if(data.size()==0)
    {
        std::cout<<"Empty file. Aborting\n";
        return;
    }
    else if(data[0][0]=='W' || data[0][0]=='w')
    {
        _directed=true;
        _weighted=true;
    }
    else if(data[0][0]=='U' || data[0][0]=='u')
    {
        _directed=false;
        _weighted=false;
    }
    else if (data[0][0]=='D' || data[0][0]=='d')
    {
        _directed=true;
        _weighted=false;
    }
    else
    {
        std::cout<<"Incorrectly formatted file. Aborting\n";
        return;
    }
    int i=1;
    node *index, *next, *cursor;
    std::vector<char> names;
    while(data[0].size()>=i)
    {
        if(!(data[0][i]==','))
            names.push_back(data[0][i]);
        i++;
    }
    i=1;
    int counter=0;
    while (i<data.size())
    {
        index = new node();
        index->_vertex=data[i][0];
        index->link=NULL;
        index->_weight=0;
        int j=1;
        while(data[i].size()>=j)
        {
            if(!(data[i][j]==','))
            {
                if(!_weighted)
                    if(data[i][j]=='1')
                    {
                        next=new node();
                        next->_vertex=data[0][j];
                        next->_weight=1;
                        next->link=NULL;
                        cursor=index;
                        while(cursor->link!=NULL)
                            cursor=cursor->link;
                        cursor->link=next;
                        
                    }
            }
            
            if(_weighted)
            {
                std::vector<char> w;
                if(data[i][j]==',')
                {
                    j++;
                    while(!(data[i][j]==',') && data[i].size()>=j)
                    {
                        w.push_back(data[i][j]);
                        j++;
                    }
                }
                w.push_back('\0');
                int temp=0;
                if(w[0]!='\0')
                {
                    counter++;
                    temp=std::stoi(std::string(w.begin(),w.end()),nullptr);
                }
                if(temp!=-1 && temp!=0)
                {
                    next=new node();
                    next->_vertex=names[counter-1];
                    next->_weight=temp;
                    next->link=NULL;
                    cursor=index;
                    while(cursor->link!=NULL)
                        cursor=cursor->link;
                    cursor->link=next;
                }
                j--;
            }
            j++;
        }
        i++;
        counter=0;
        _graph.push_back(*index);
    }
    if(unweighted)
    {
        _directed=false;
        for(int i=0;i<_graph.size();i++)
        {
            index=_graph[i].link;
            std::string v;
            node *other;
            v=_graph[i]._vertex;
            int j=0;
            while(index!=NULL)
            {
                other=NULL;
                j=0;
                while(_graph[j]._vertex!=index->_vertex)
                    j++;
                other=_graph[j].link;
                while(other!=NULL && other->_vertex!=v )
                    other=other->link;
                if(other==NULL)
                {
                    node *insert;
                    insert=new node();
                    insert->_vertex=v;
                    insert->_weight=index->_weight;
                    insert->link=NULL;
                    other=_graph[j].link;
                    while(other->link!=NULL)
                        other=other->link;
                    other->link=insert;
                }
                else
                {
                    if(other->_weight<index->_weight)
                        index->_weight=other->_weight;
                    else
                        other->_weight=index->_weight;
                    //other->_weight=weight;
                    //index->_weight=weight;
                }
                index=index->link;
            }
        }
    }
    
    return;
}

std::vector<int> Graph::Dijkstra(std::string startNode)
{
    int size=_graph.size();
    _pathvec.clear();
    std::vector<int> dist;
    int source=-1;
    for (int i=0;i<_graph.size();i++)
    {
        if(_graph[i]._vertex==startNode)
        {
            source=i;
            break;
        }
    }
    struct MinHeap* mH=createMinHeap(size);
    for(int v=0;v<size;++v)
    {
        dist.push_back(20000000);
        _path[v]=_graph[v]._vertex;
        mH->array[v]= newMinHeapNode(v,dist[v]);
        mH->pos[v]=v;
    }
    mH->array[source]=newMinHeapNode(source,dist[source]);
    _path[source]=startNode;
    mH->pos[source]=source;
    dist[source]=0;
    decreaseKey(mH, source, dist[source]);
    mH->size=size;
    while(!isEmpty(mH))
    {
        struct MinHeapNode* mHN=extractMin(mH);
        int row=mHN->v;
        node* crawl=_graph[row].link;
        while(crawl!=NULL)
        {
            std::string t=crawl->_vertex;
            int point=0;
            for (int i=0;i<_graph.size();i++)
            {
                if(_graph[i]._vertex==t)
                {
                    point=i;
                    break;
                }
            }
            if(isInMinHeap(mH,point) && dist[row]!=20000000 && crawl->_weight+dist[row]<dist[point])
            {
                dist[point]=dist[row]+crawl->_weight;
                _path[point]=_path[row]+crawl->_vertex;
                decreaseKey(mH, point, dist[point]);
            }
            crawl=crawl->link;
        }
    }
    for(int i=0;i<size;i++)
    {
        std::vector<char> pathvec(_path[i].begin(),_path[i].end());
        _pathvec.push_back(pathvec);
    }
    std::vector<int> ret;
    for (int i=0;i<size;i++)
        ret.push_back(dist[i]);
    return ret;
}

std::vector<char> Graph::getPath(int i)
{
    return (_pathvec[i]);
}

std::string Graph::getVertexName(int i)
{
    return (_graph[i]._vertex);
}

int Graph::getSizeOfGraph()
{
    return (_graph.size());
}
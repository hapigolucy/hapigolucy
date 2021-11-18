#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <exception>

using namespace std;

class Graph
{
    int v; //No. of vertices
    vector<list<int>> adj;
    void DFSRecursion(int v, vector<bool>& visited);
    bool directed = false;
    public:
        Graph(int v, bool directed = false);
        void addEdge(int v, int w);
        void DFS();
        void DFSAbitrary(int i);
};

class InvalidNodeException : public exception
{
    int node;
    public:
    InvalidNodeException(int node):node{node}
    {}
    string what()
    {
        return "Invalid node entered -> " + to_string(node);
    }
};

void demoGraph();

#pragma once

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct GraphNode;

using NodeShPtr = shared_ptr<GraphNode>;

struct GraphNode
{
    int destNodeNum;
    int edgeWeight;
    GraphNode( int dest, int weight):destNodeNum{dest}, edgeWeight(weight) {}
};

class GraphOld
{
    int numNodes;
    int numEdges;
    vector<vector<NodeShPtr>> graph;

    public:
        GraphOld(int nodes, int edges):numNodes(nodes),numEdges(edges)
        {}
        ~GraphOld();
        void createGraph();
        void displayGraph();
};

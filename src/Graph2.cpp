#include "Graph2.h"

using namespace std;

Graph::Graph(int v, bool directed):directed{directed}
{
    this->v = v;
    adj.resize(v+1);
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    if(!directed)
        adj[w].push_back(v);
}

void Graph::DFSRecursion(int v, vector<bool>& visited)
{
    visited[v] = true;
    cout << v << " ";

    for(auto i : adj[v])
        if(!visited[i])
            DFSRecursion( i, visited);
}

//void Graph::DFSStack(int )

void Graph::DFS()
{
    vector<bool> visited(v, false);//Mark all nodes as not visited.

    int i = adj[0].size() ? 0 : 1;
    for(; i < v; ++i)
        if(!visited[i])
            DFSRecursion(i, visited);
}

void Graph::DFSAbitrary(int i)
{
    vector<bool> visited(v, false);//Mark all nodes as not visited.
    if( i < v) {
        if(!visited[i])
            DFSRecursion(i, visited);
    }
    else {
        //throw std::runtime_error("Invalid Node Entered!!! Check the starting node.");
        throw InvalidNodeException(i);
    }
}

void demoGraph()
{
    Graph g(6);
    g.addEdge(4, 5);
    g.addEdge(1, 4);
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 6);
    g.addEdge(4, 6);

    cout << "\n*****************\nDepth First Traversal\n*****************\n";
    g.DFS();

    /*
    Graph g(4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.addEdge(3, 4);
    g.addEdge(4, 4);
    */
    Graph dg(5, true);
    dg.addEdge(0, 1);
    dg.addEdge(0, 2);
    dg.addEdge(0, 3);
    dg.addEdge(1, 2);
    dg.addEdge(2, 4);
    dg.addEdge(3, 3);
    dg.addEdge(4, 4);

    cout << "\n*****************\nDepth First Traversal\n*****************\n";
    int node = 0;
    cin >> node;
    try {
        dg.DFSAbitrary(node);
    }
    catch(InvalidNodeException& e)
    {
        cout << "Invalid node entered. " << e.what() << endl;
    }
    catch(std::exception& e)
    {
        cerr << "Exception encountered. " << e.what() << endl;
    }

}

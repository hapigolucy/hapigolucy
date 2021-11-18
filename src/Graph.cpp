#include "Graph.h"

GraphOld::~GraphOld()
{
}

void GraphOld::createGraph() {
    graph.resize(numNodes + 1);
    while(numEdges--){
        int s, d, w;
        cout << "Enter Source Node : " ;
        cin >> s;
        cout << " Enter Destination Node : " ;
        cin >> d;
        cout << " Enter Weight of the edge : " ;
        cin >> w;
        shared_ptr<GraphNode> node1 = make_shared<GraphNode>(d, w);
        graph[s][d] = node1;
        shared_ptr<GraphNode> node2 = make_shared<GraphNode>(s, w);
        graph[d][s]= (make_shared<GraphNode>(s, w));
    }
}

void GraphOld::displayGraph() {
    for(int i = 1; i < numNodes; ++i) {
        for(int j = 1; j < numEdges; ++j) {
            cout << i << j << (graph[i][j])->edgeWeight << "  ";
        }
        cout << endl;
    }
}

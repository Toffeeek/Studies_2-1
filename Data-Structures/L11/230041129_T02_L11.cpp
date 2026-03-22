#include <iostream>
#include <map>
#include <list>
#include<vector>
using namespace std;

int main()
{
    int V, E;
    cin >> V >> E;

    map<int, list<int>>adjList;
    

    for(int i = 0; i < E; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
    
    

        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);

    }

    cout << "Adjacency List:\n";
    for(auto bucket : adjList)
    {
        cout << bucket.first << ": ";
        for(auto node : bucket.second)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    cout << "\n";

    vector<int> vertexEdges(V, 0);

    for(auto bucket : adjList)
    {
        vertexEdges[bucket.first-1] = bucket.second.size();
    }
    cout << "\n\n";

    for(int i = 0; i < V; i++)
    {
        if(vertexEdges[i] != vertexEdges[0])
        {
            cout << "No." << endl;
            return 0;
        }
    }

    cout << "Yes." << endl;
    return 0;   
}
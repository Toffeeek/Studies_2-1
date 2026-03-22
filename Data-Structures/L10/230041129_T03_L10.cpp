#include <iostream>
#include <map>
#include <list>
using namespace std;

int main()
{
    int V, E;
    cin >> V >> E;

    map<int, list<int>>adjList;
    int adjMatrix[V][V];
    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    for(int i = 0; i < E; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
    
    

        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);

        adjMatrix[v1-1][v2-1] = 1;
        adjMatrix[v2-1][v1-1] = 1;
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
    cout << "\n\n";
    cout << "Adjacency Matrix:\n";

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;   
}
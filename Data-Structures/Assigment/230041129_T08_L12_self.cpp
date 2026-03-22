#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>
using namespace std;




class Graph
{
    int V;
    vector<bool> visited;
    vector<vector<int>> adjList;
    bool findPathRec(int curr, int dest, vector<int>& path)
    {
        visited[curr] = true;
        path.push_back(curr);

        if(curr == dest)
            return true;

        for(const auto& adjacentVertex : adjList[curr])
        {
            if(visited[adjacentVertex] == false)
            {
                if(findPathRec(adjacentVertex, dest, path))
                {
                    return true;
                }
            }
        }
        path.pop_back();
        return false;
    }

public:
    Graph(const vector<vector<int>>& adjList) 
        : V(adjList.size()), adjList(adjList), visited(V, false)
    {

    }
    void printAdjList() const
    {
        cout << "Printing adjacency list:\n";
        int rowIndex = 0;
        for(const auto& row : adjList)
        {
            cout << ++rowIndex << ": ";
            for(int v : row)
            {
                cout << v+1 << " ";
            }
            cout << endl;
        }
    }
    void findPath(int src, int dest)
    {
        vector<int> path;
        if(findPathRec(src, dest, path) == true)
        {
            cout << "Path: ";
            for(auto v: path)
            {
                cout << v+1 << " -> ";
            }
            cout << endl;
        }
        else
        {
            cout << "No path exists\n";
        }
    }

};




int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<int>> adjList(V);
    for(int i = 0; i < E; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;

        adjList[v1-1].push_back(v2-1);
    }

    Graph g(adjList);
    g.printAdjList();
    int src, dest;
    cin >> src >> dest;
    g.findPath(src-1, dest-1);


    



    return 0;
}
#include <iostream>
#include <map>
#include <list>
#include <queue>
#include<vector>
using namespace std;

struct BFSresult
{
    vector<int> print;
    vector<int> predecessor;
    vector<int> distance;
    vector<bool> visited;
    vector<pair<int, int>> tree_edges;
};

BFSresult bfsSearch(const map<int, list<int>>& adjList, int V, int startVertex)
{
    BFSresult res;
    res.predecessor.assign(V, -1);
    res.distance.assign(V, -1);   
    res.visited.assign(V, false);

    queue<int> q;
    q.push(startVertex);
    res.visited[startVertex] = true;
    res.distance[startVertex] = 0;

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        res.print.push_back(curr);

        auto it = adjList.find(curr);

        if(it == adjList.end())
            continue;

        for(int neighbor : it->second)
        {
            if(!res.visited[neighbor])
            {
                res.visited[neighbor] = true;
                res.predecessor[neighbor] = curr;
                res.distance[neighbor] = res.distance[curr] + 1;
                q.push(neighbor);
                res.tree_edges.push_back({curr, neighbor});
            }
        }
    }
    return res;
}

auto getPath(vector<int> predecessors, int V, int source, BFSresult res)
{
    vector<int> path;

    while(V != source)
    {
        path.insert(path.begin(), V);
        V = res.predecessor[V];
    }
    path.insert(path.begin(), V);
    return path;
}





int main()
{
    int V, E, s;
    cin >> V >> E >> s;

    map<int, list<int>>adjList;
    

    for(int i = 0; i < E; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
    
    

        adjList[v1-1].push_back(v2-1);
        adjList[v2-1].push_back(v1-1);

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

    

    BFSresult res = bfsSearch(adjList, V, s-1);

    cout << "BFS Print: ";
    for(int i : res.print)
    {
        cout << i+1 << " ";
    }
    cout << endl;

    cout << "Distance from the source: ";
    for(int v : res.print)
    {
        cout << v+1 << "(" << res.distance[v] << ") ";
    }
    cout << endl;

    for(int i = 0; i < V; i++)
    {
        cout << i+1 << ": ";
        vector<int> path = getPath(res.predecessor, i, s-1, res);
        for(int j : path)
        {
            cout << j+1 << "->";
        }
        cout << endl;
    }

    cout << "Tree edges: ";
    for(auto i : res.tree_edges)
    {
        cout << i.first+1 << " " << i.second+1 << endl;
    }


    return 0;
}
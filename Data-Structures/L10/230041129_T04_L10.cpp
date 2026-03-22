#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int V, E;
    cin >> V >> E;

    map<int, list<int>> adjList;

    // Build in-degree adjacency list
    for (int i = 0; i < E; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;

        // adjList[v1].push_back(v2);  
        adjList[v2].push_back(v1);     
    }

    cout << "In-degree Adjacency List:\n";

    for (auto bucket : adjList)
    {
        cout << bucket.first << ": ";

        for (auto node : bucket.second)
        {
            cout << node << " ";
        }

        cout << endl;
    }

    cout << "Topological Sort: ";

    queue<int> inDegreeZero;
    vector<bool> pushed(V, false);

    for (int i = 0; i < V; i++)
    {
        if (adjList[i].empty())
        {
            inDegreeZero.push(i);
            pushed[i] = true;
        }
    }

    if(inDegreeZero.empty())
        cout << "[]";

    while (!inDegreeZero.empty())
    {
        int i = inDegreeZero.front();
        inDegreeZero.pop();

        cout << i << " ";

        adjList.erase(i);

        for (auto &bucket : adjList)
        {
            bucket.second.remove(i);

            if (bucket.second.empty())
            {
                if(!pushed[bucket.first])
                {
                    inDegreeZero.push(bucket.first);
                    pushed[bucket.first] = true;
                }
            }
        }
    }

    return 0;
}

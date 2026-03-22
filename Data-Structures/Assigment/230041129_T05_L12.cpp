#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <iomanip>
using namespace std;


class Graph
{
    int V, E;
    vector<string> cities;
    vector<vector<int>> adjList;
    vector<bool> visited;
    vector<int> path;

    int getIndex(string city) const
    {
        for(int i = 0; i < V; i++)
        {
            if(cities[i] == city)
            {
                return i;
            }
        }
        cout << "INVALID INDEX\n";
        return -1;
    }
    string getCity(int i) const
    {
        if(i < V)
            return cities[i];
        else
            return "CITY INDEX OUT OF BOUNDS";
    }
    void buildAdjList(const vector<pair<string, string>>& edges)
    {
        for(int i = 0; i < E; i++)
        {
            int v1 = getIndex(edges[i].first); 
            int v2 = getIndex(edges[i].second);
            
            adjList[v1].push_back(v2);
            adjList[v2].push_back(v1);
        }
    }
    bool findPathDFS(int curr, int dest)
    {
        visited[curr] = true;
        path.push_back(curr);

        if(curr == dest)
            return true;

        for(int next : adjList[curr])
        {
            if(!visited[next])
            {
                if(findPathDFS(next, dest))
                    return true;
            }
        }

        path.pop_back();
        return false;
    }

public:
    Graph(const vector<string>& cities, const vector<pair<string, string>>& edges)
        : cities(cities), V(cities.size()), E(edges.size())
    {
        adjList.resize(V);
        visited.assign(V, false);
        buildAdjList(edges);
    }
    void printAdjList() const
    {
        cout << "PRINTING CITIES: \n";
        for(int i = 0; i < V; i++)
        {
            cout << setw(12) << left << getCity(i) << ": ";
            for(int j = 0; j < adjList[i].size(); j++)
            {
                cout << setw(12) << left << getCity(adjList[i][j]) << " ";
            }
            cout << endl;
        }
    }
    void query(string _src, string _dest, int jsize)
    {
        int src  = getIndex(_src);
        int dest = getIndex(_dest);

        visited.assign(V, false);
        path.clear();
        bool pathExists = findPathDFS(src, dest);

        if(pathExists && (path.size() - 1) % jsize == 0)
        {
            cout << "PATH: ";
            for(int i = 0; i < path.size(); i += jsize)
            {
                cout << getCity(path[i]) << " -> ";
            }
            cout << endl;
        }
        else
        {
            cout << "NO\n";
        }

    }

};



int main()
{
    int V, E, Q;
    cin >> V >> E >> Q;
    vector<string> vertices;
    for(int i = 0; i < V; i++)
    {
        string v;
        cin >> v;
        vertices.push_back(v);
    }

    vector<pair<string, string>> edges;

    for(int i = 0; i < E; i++)
    {
        string ct1, ct2;
        cin >> ct1 >> ct2;

        edges.push_back({ct1, ct2});
    }

    Graph g(vertices, edges);
    g.printAdjList();

    for(int i = 0; i < Q; i++)
    {
        string ct1, ct2;
        int jsize;
        cin >> ct1 >> ct2 >> jsize;
        g.query(ct1, ct2, jsize);
    }



    return 0;
}
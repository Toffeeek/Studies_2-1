#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <queue>
using namespace std;

enum EdgeType
{
    TreeEdge,
    BackEdge,
    ForwardEdge,
    CrossEdge,
    Unknown
};

string getEdgeType(EdgeType e)
{
    if (e == TreeEdge)    return "TreeEdge";
    if (e == BackEdge)    return "BackEdge";
    if (e == ForwardEdge) return "ForwardEdge";
    if (e == CrossEdge)   return "CrossEdge";
    return "Unknown";
}

class Graph
{
    int N;
    vector<vector<pair<int, EdgeType>>> adjList;
    int currTime;

    vector<int> DFSpred;
    vector<bool> visited;
    vector<pair<int, int>> DFStimestamp;
    vector<int> dfsOrder;

    vector<int> BFSpred;
    vector<bool> pushed;
    vector<int> BFStimestamp;
    vector<int> bfsOrder;

    void dfs(int source)
    {
        currTime = 0;
        visited.assign(N, false);
        DFSpred.assign(N, -1);
        DFStimestamp.assign(N, {-1, -1});
        dfsOrder.clear();

        dfsRec(source);

        for (int i = 0; i < N; i++)
        {
            if (!visited[i])
            {
                dfsRec(i);
            }
        }
    }

    void dfsRec(int curr)
    {
        visited[curr] = true;
        dfsOrder.push_back(curr);
        DFStimestamp[curr].first = currTime++;

        for (int i = 0; i < adjList[curr].size(); i++)
        {
            int nextVer = adjList[curr][i].first;

            if (!visited[nextVer])
            {
                DFSpred[nextVer] = curr;
                dfsRec(nextVer);
            }
        }

        DFStimestamp[curr].second = currTime++;
    }

    void classifyEdges()
    {
        for (int u = 0; u < N; u++)
        {
            for (int i = 0; i < adjList[u].size(); i++)
            {
                int v = adjList[u][i].first;

                // u is a direct predecessor of v
                if (DFSpred[v] == u)
                {
                    adjList[u][i].second = TreeEdge;
                }
                // v is discovered first but u is finished first
                else if (DFStimestamp[v].first < DFStimestamp[u].first &&
                         DFStimestamp[u].second < DFStimestamp[v].second)
                {
                    adjList[u][i].second = BackEdge;
                }
                // 
                else if (DFStimestamp[u].first < DFStimestamp[v].first &&
                         DFStimestamp[v].second < DFStimestamp[u].second)
                {
                    adjList[u][i].second = ForwardEdge;
                }
                else
                {
                    adjList[u][i].second = CrossEdge;
                }
            }
        }
    }

    void bfs(int source)
    {
        currTime = 0;
        BFStimestamp.assign(N, -1);
        pushed.assign(N, false);
        BFSpred.assign(N, -1);
        bfsOrder.clear();

        bfsHelper(source);

        for (int i = 0; i < N; i++)
        {
            if (!pushed[i])
            {
                bfsHelper(i);
            }
        }
    }

    void bfsHelper(int curr)
    {
        queue<int> q;
        q.push(curr);
        pushed[curr] = true;
        BFStimestamp[curr] = currTime++;

        while (!q.empty())
        {
            int ver = q.front();
            q.pop();
            bfsOrder.push_back(ver);

            for (const auto& p : adjList[ver])
            {
                if (!pushed[p.first])
                {
                    q.push(p.first);
                    pushed[p.first] = true;
                    BFStimestamp[p.first] = currTime++;
                    BFSpred[p.first] = ver;
                }
            }
        }
    }

public:
    Graph(const vector<vector<int>>& inputAdjList) : N(inputAdjList.size()), currTime(0)
    {
        adjList.resize(N);

        for (int i = 0; i < N; i++)
        {
            for (int v : inputAdjList[i])
            {
                adjList[i].push_back({v, Unknown});
            }
        }

        dfs(0);
        classifyEdges();
        bfs(0);
    }

    void printDFSOrder() const
    {
        cout << "DFS Order:\n";
        for (int ver : dfsOrder)
        {
            cout << ver << " {"
                 << left << setw(2) << DFStimestamp[ver].first << ","
                 << left << setw(2) << DFStimestamp[ver].second << "}\n";
        }
    }

    void printBFSOrder() const
    {
        cout << "BFS Order:\n";
        for (int ver : bfsOrder)
        {
            cout << ver << " {" << left << setw(2) << BFStimestamp[ver] << "}\n";
        }
    }

    void printEdges() const
    {
        for (int i = 0; i < N; i++)
        {
            for (const auto& p : adjList[i])
            {
                cout << i << " -> " << p.first << " : " << getEdgeType(p.second) << '\n';
            }
        }
    }
};

int main()
{
    vector<vector<int>> graph =
    {
        {1, 2},   // 0
        {2, 3},   // 1
        {0},      // 2
        {}        // 3
    };

    Graph g(graph);
    g.printDFSOrder();
    g.printBFSOrder();
    cout << '\n';
    g.printEdges();

    return 0;
}
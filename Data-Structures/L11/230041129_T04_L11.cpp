#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

enum EdgeClassification {Tree_Edge , Forward_Edge, 
                         Back_Edge, Cross_Edge, Undetermined};

string edgeToString(EdgeClassification e)
{
    switch (e)
    {
        case Tree_Edge:     return "Tree_Edge";
        case Forward_Edge:  return "Forward_Edge";
        case Back_Edge:     return "Back_Edge";
        case Cross_Edge:    return "Cross_Edge";
        case Undetermined:  return "Undetermined";
        default:            return "Unknown";
    }
}


class Graph_DFS
{
    int V;
    int E;
    int currTime;
    vector<vector<int>> adjList;
    vector<bool>visited;
    vector<pair<int, int>> timestamps;
    vector<int>predecessor;
    void DFSrecursive(int S);
    void classifyEdgesRecursive(int S, vector<int>& localVisits);

    vector<int> DFSorder;
    vector<vector<EdgeClassification>> edgeClassification;

public:
    Graph_DFS(vector<vector<int>> adjList, int V, int E) : 
        adjList(adjList), V(V), E(E), currTime(1)
    {
        visited.assign(V, false);
        timestamps.assign(V, {-1, -1});
        predecessor.assign(V, -1);
        
        edgeClassification.resize(V);
        for(int i = 0; i < adjList.size(); i++)
        { 
            for(int j = 0; j < adjList[i].size(); j++)
            {
                edgeClassification[i].push_back(Undetermined);
            }
        }
    }
    int getPredecessor(int i) const;
    void printAdjList();
    void DFSsearch(int S);
    void printDFSorder() const;
    void printTimestamps() const;
    void classifyEdges(int S);
    void printEdgeClassification() const;
};

int Graph_DFS::getPredecessor(int i) const
{
    return predecessor[i];
}
void Graph_DFS::printAdjList()
{
    for(int i = 0; i < adjList.size(); i++)
    {
        cout << i+1 << ": ";
        for(int j = 0; j < adjList[i].size(); j++)
        {
            cout << adjList[i][j]+1 << " ";
        }
        cout << endl;
    }
}

void Graph_DFS::DFSsearch(int S)
{
    DFSrecursive(S);
    for(int i = 0; i < V; i++)
    {
        if(!visited[i])
        {
            DFSrecursive(i);
        }
    }
}
void Graph_DFS::DFSrecursive(int S)
{
    
    visited[S] = true;
    DFSorder.push_back(S);
    timestamps[S].first = currTime++;        
        
    for(int v: adjList[S])
    {
        if(!visited[v])
        {
            predecessor[v] = S;
            DFSrecursive(v);
        }
        
    }
    timestamps[S].second = currTime++;
}
bool inVisitStack(const vector<int>& stack, int target)
{
    return find(stack.begin(), stack.end(), target) != stack.end();
}
void Graph_DFS::classifyEdges(int S)
{
    visited.assign(V, false);
    vector<int>visitStack;
    classifyEdgesRecursive(S, visitStack);

    for(int i = 0; i < V; i++)
    {
        if(!visited[i])
        {
            visitStack.clear();
            classifyEdgesRecursive(i, visitStack);
        }
    }
}

void Graph_DFS::classifyEdgesRecursive(int S, vector<int>& visitStack)
{
    visited[S] = true;
    visitStack.push_back(S);

    for (int i = 0; i < (int)adjList[S].size(); i++)
    {
        int v = adjList[S][i];

        if (!visited[v])
        {
            edgeClassification[S][i] = Tree_Edge;
            classifyEdgesRecursive(v, visitStack);
        }
        else if (inVisitStack(visitStack, v))
        {
            edgeClassification[S][i] = Back_Edge;
        }
        else
        {
            // visited and NOT in stack => Forward or Cross (use timestamps)
            int du = timestamps[S].first, fu = timestamps[S].second;
            int dv = timestamps[v].first, fv = timestamps[v].second;

            if (du < dv && fv < fu) edgeClassification[S][i] = Forward_Edge;
            else                    edgeClassification[S][i] = Cross_Edge;
        }
    }

    visitStack.pop_back();
}
void Graph_DFS::printDFSorder() const
{
    cout << "DFS order: ";
    for(int i : DFSorder)
    {
        cout << i+1 << " ";
    }
    cout << endl;
}
void Graph_DFS::printTimestamps() const
{
    cout << "Timestamps:\n";
    for(int i = 0; i < DFSorder.size(); i++)
    {
        cout << DFSorder[i]+1 << "(" << timestamps[i].first << "/" 
        << timestamps[i].second << ")" << endl;
    }
}
void Graph_DFS::printEdgeClassification() const
{
    for(int i = 0; i < adjList.size(); i++)
    { 
        for(int j = 0; j < adjList[i].size(); j++)
        {
            cout << i+1 << "," << adjList[i][j]+1 << ": " <<  edgeToString(edgeClassification[i][j]) << endl;
        }
    }
}
    
    
    
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
    Graph_DFS dfs(adjList, V, E);

    int S = 1;
    // cout << "Enter source node: ";
    // cin >> S;
    dfs.printAdjList();
    dfs.DFSsearch(S-1);
    dfs.printDFSorder();
    dfs.printTimestamps();
    dfs.classifyEdges(S-1);
    dfs.printEdgeClassification();
    






    return 0;
}
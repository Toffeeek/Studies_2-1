#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int V, E;
    cin >> V >> E;
    map<string, vector<string>> adj;
    for (int i = 0; i < V; i++)
    {
        string s;
        cin >> s;
        adj[s];
    }
    for (int i = 0; i < E; i++)
    {
        string u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    string src, dst;
    int k;
    while (cin >> src >> dst >> k)
    {
        map<string, bool> vis;
        map<string, string> par;
        vector<string> path;
        queue<string> q;
        q.push(src);
        vis[src] = "";
        while (!q.empty())
        {
            string u = q.front();
            q.pop();
            if (u == dst)
                break;
            for (string v : adj[u])
            {
                if (!vis[v])
                {
                    par[v] = u;
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        if (!vis[dst])
        {
            cout << "NO" << endl;
            continue;
        }
        for (string v = dst; v != ""; v = par[v])
        {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        int n = path.size() - 1;
        if (n % k == 0 && n / k >= 2)
        {
            for (int i = 0; i <= n; i += k)
            {
                cout << path[i] << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}
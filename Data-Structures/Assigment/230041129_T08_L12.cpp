#include <queue>
#include <iostream>
#include <vector>

using namespace std;



int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    
    
    int src, dst;
    cin >> src >> dst;
    queue<int> q;
    q.push(src);
    vector<bool> vis(N + 1, false);
    vis[src] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == dst)
            break;
        for (int v : adj[u])
        {
            if (!vis[v])
            {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    vis[dst] ? cout << "YES\n" : cout << "NO\n";

}
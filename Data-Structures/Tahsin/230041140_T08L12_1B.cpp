#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int src, dst;

int main() {
    cin >> N >> M;
    vector<vector<int>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    cin >> src >> dst;
    queue<int> q;
    q.push(src);
    vector<bool> vis(N+1, false);
    vis[src] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dst) break;
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    if (!vis[dst]) cout << "No\n";
    else cout << "Yes\n";
}
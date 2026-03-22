#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define endl "\n"

int main() {
    int V; cin >> V;
    vector<vector<int>> adj(V);
    for (int u = 0; u < V; u++) {
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    queue<int> q;
    vector<int> color(V, -1);
    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (auto &v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if (color[v] == color[u]) {
                        cout << "NO" << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "YES" << endl;
}
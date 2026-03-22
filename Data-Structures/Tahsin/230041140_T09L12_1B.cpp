#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

int main() {
    int V, E; cin >> V >> E;
    int Q; cin >> Q;
    map<string, int> name_to_id;
    vector<string> id_to_name(V);
    for (int i = 0; i < V; i++) {
        cin >> id_to_name[i];
        name_to_id[id_to_name[i]] = i;
    }
    vector<vector<int>> adj(V);
    vector<int> indegree(V, 0);
    for (int i = 0; i < E; i++) {
        string u_name, v_name; cin >> u_name >> v_name;
        int u = name_to_id[u_name];
        int v = name_to_id[v_name];
        adj[v].push_back(u);
        indegree[u]++;
    }
    queue<int> q;
    vector<int> topo;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    if (topo.size() != V) {
        cout << "NOT POSSIBLE" << endl;
        return 0;
    }
    map<int, int> mp;
    for (int i = 0; i < V; i++) {
        mp[topo[i]] = i;
    }
    for (int i = V - 1; i >= 0; i--) {
        cout << id_to_name[topo[i]] << " ";
    }
    cout << endl << endl;
    while (Q--) {
        string student1, student2;
        cin >> student1 >> student2;
        int u = name_to_id[student1];
        int v = name_to_id[student2];
        if (mp[u] < mp[v]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
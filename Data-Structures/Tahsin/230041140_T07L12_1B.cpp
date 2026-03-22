#include <iostream>
#include <vector>
using namespace std;

int m, n, ans;
vector<string> grid;
vector<vector<bool>> vis;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

void island_dfs(int r, int c) {
    vis[r][c] = true;
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i];
        int nc = c + dy[i];
        if (nr>=0&&nr<m && nc>=0&&nc<n) {
            if (!vis[nr][nc] && grid[nr][nc]=='1') {
                island_dfs(nr, nc);
            }
        }
    }
}

void ocean_dfs(int r, int c) {
    vis[r][c] = true;
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i];
        int nc = c + dy[i];
        if (nr>=0&&nr<m && nc>=0&&nc<n) {
            if (!vis[nr][nc]) {
                if (grid[nr][nc]=='0') {
                    ocean_dfs(nr,nc);
                } else {
                    ans++;
                    island_dfs(nr,nc);
                }
            } 
        }
    }
}

int main() {
    cin >> m >> n;
    grid.resize(m+2,string(n+2,'0'));
    for (int i = 1; i <= m; i++) {
        string row; cin >> row;
        for (int j = 1; j <= n; j++) {
            grid[i][j] = row[j-1];
        }
    }
    m+=2;
    n+=2;
    vis.assign(m,vector<bool>(n, false));
    ocean_dfs(0,0);
    cout << ans << endl;
}
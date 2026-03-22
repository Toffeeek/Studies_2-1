#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define endl "\n"

int m, n;
// R, D = Red, L, U = Green
//           R,L,D, U
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
void dfs(vector<vector<int>> &mat, vector<vector<bool>> &vis, int r, int c) {
    vis[r][c] = true;
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i];
        int nc = c + dy[i];
        if (nr>=0&&nr<m&&nc>=0&&nc<n) {
            if (!vis[nr][nc]&&mat[nr][nc]>=mat[r][c]) {
                dfs(mat,vis,nr,nc);
            }
        }
    }
}

int main() {
    cin >> m >> n;
    vector<vector<int>> mat(m, vector<int>(n,0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    vector<vector<bool>> green(m,vector<bool>(n,false));
    vector<vector<bool>> red(m,vector<bool>(n,false));
    for (int i=0; i<m; i++) dfs(mat,green,i,0);
    for (int j=0; j<n; j++) dfs(mat,green,0,j);;

    for (int i=0; i<m; i++) dfs(mat,red,i,n-1);
    for (int j=0; j<n; j++) dfs(mat,red,m-1,j);

    for (int i=0 ;i<m; i++) {
        for (int j=0; j<n; j++) {
            if (green[i][j] && red[i][j]) {
                cout << "O ";
            } else {
                cout << "X ";
            }
        }
        cout << endl;
    }

}
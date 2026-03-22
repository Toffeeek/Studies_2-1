#include <iostream>
#include <vector>
#include <utility>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;

#define optimize() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

const int N = 2e5 + 9;
const int K = 20;
int table[N][K], a[N], lg[N];

void build_log() {
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i / 2] + 1;
    }
}

void build(int n) {
    build_log();
    for(int j = 1; j <= lg[n]; j++) {
        for(int i = 0; i + (1 << j) - 1 < n; i++) {
            table[i][j] = max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int L, int R) {
    int window = R - L + 1;
    int j = lg[window];
    return max(table[L][j], table[R - (1 << j) + 1][j]);
}

int main() {
    optimize();
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        table[i][0] = a[i];
    }
    build(n);
    int ans = 0;
    // 0 based indexing sparse table
    while (q--) {
        int L, R; 
        cin >> L >> R; 
        --L; --R;
        if (L >= R - 1) ans++; 
        else if (query(L + 1, R - 1) <= a[L]) ans++;
    }
    cout << ans << endl;
    return 0;
}
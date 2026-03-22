#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;
    int q; cin >> q;
    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> pre[i];
    for (int i = 1; i <= n; i++) pre[i] += pre[i-1];

    while (q--) {
        int L, R;
        cin >> L >> R;
        int len = R - L + 1;
        if (len & 1) {
            cout << -1 << endl;
        } else { 
            int ones = pre[R] - pre[L - 1];
            int ans = abs(len / 2 - ones);
            cout << ans << endl;
        }
    }

    return 0;
}
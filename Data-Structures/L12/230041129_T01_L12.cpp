#include <iostream>
#include <vector>
using namespace std;

int main() {


    string s;
    cin >> s;
    int n = s.size();

    
    vector<vector<int>> pref(n + 1, vector<int>(26, 0));

    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1];                 
        pref[i][s[i - 1] - 'a']++;             
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int L, R;            
        cin >> L >> R;

        int bestChar = 0;
        int bestCount = -1;

        for (int c = 0; c < 26; c++) {
            int cnt = pref[R][c] - pref[L - 1][c];
            if (cnt > bestCount) {
                bestCount = cnt;
                bestChar = c;
            }
            
            
        }

        cout << char('a' + bestChar) << ":" << bestCount << "\n";
    }

    return 0;
}
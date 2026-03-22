#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int query(const vector<vector<int>>& st, int L, int R)
{
    int len = R - L + 1;
    int k = (int)log2(len);
    return min(st[L][k], st[R - (1 << k) + 1][k]);


    // [L,R] interveral broken into two subinvervals each of length log2(len) = k
    //    sparse table index of left subinterval  -> [L][k] 
    //    sparse table index of right subinterval -> [R - (1 << k) + 1][k]
    //                       starting index                | ending index
    //                       --------------------------------------------------------
    //  left subinterval        arr[L]                     | arr[L + (1 << k) - 1]
    //  right subinterval       arr[R - (1 << k) + 1]      | arr[R]
}

int main()
{
    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; i++) cin >> arr[i];

    int K = (int)log2(N);
    vector<vector<int>> st(N, vector<int>(K + 1));

    // j = 0
    for (int i = 0; i < N; i++)
    {
        st[i][0] = arr[i];
    } 

    // build
    for (int j = 1; j <= K; j++)
    {
        int len = 1 << j;
        for (int i = 0; i + len - 1 < N; i++)
        {
            st[i][j] = min(st[i][j - 1], st[i + (len >> 1)][j - 1]);
            // Equivalent to: st[i][j] = st[i][j-1] , st[i + (2^j)/2][j-1]
        }
    }

    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= K && i + (1 << j) - 1 < N; j++)
            cout << st[i][j] << " ";
        cout << "\n";
    }

    int Q;
    cin >> Q;

    for(int i = 0; i < Q; i++)
    {
        int L, R;
        cin >> L >> R;
        cout << L << " " << R << ": " << query(st, L, R) << endl;
    }

    // cout << "Query: 2,6: " << query(st, 2, 6) << "\n";
    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class OrSparseTable
{
    int N, K;
    vector<vector<int>> st;
    vector<int> lg;

public:
    OrSparseTable(const vector<int>& arr)
    {
        N = arr.size();
        K = log2(N) + 1;

        st.assign(K, vector<int>(N));
        lg.assign(N + 1, 0);

        for(int i = 2; i <= N; i++)
            lg[i] = lg[i / 2] + 1;

        for(int i = 0; i < N; i++)
            st[0][i] = arr[i];

        for(int j = 1; j < K; j++)
        {
            for(int i = 0; i + (1 << j) <= N; i++)
            {
                st[j][i] = st[j-1][i] | st[j-1][i + (1 << (j-1))];
            }
        }
    }

    int query(int L, int R) const
    {
        int ans = 0;
        int len = R - L + 1;

        for(int j = K - 1; j >= 0; j--)
        {
            if((1 << j) <= len)
            {
                ans |= st[j][L];
                L += (1 << j);
                len -= (1 << j);
            }
        }
        return ans;
    }
};

int main()
{
    int N, Q;
    cin >> N;

    vector<int> arr(N);
    for(int i = 0; i < N; i++)
        cin >> arr[i];

    OrSparseTable st(arr);

    cin >> Q;
    while(Q--)
    {
        int L, R, X;
        cin >> L >> R >> X;   

        int res = st.query(L - 1, R - 1);

        if(res == arr[X - 1])
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
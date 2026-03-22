#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class gcdSparseTable
{
    int N;
    int K;
    vector<int> arr;
    vector<vector<int>> table;

    void resizeTable()
    {
        table.resize(N);
        for (int i = 0; i < N; i++)
        {
            table[i].resize(K);
        }
    }

    void generateTable()
    {
        for (int i = 0; i < N; i++)
        {
            table[i][0] = arr[i];
        }

        for (int j = 1; j < K; j++)
        {
            int len = 1 << j;
            for (int i = 0; i + len <= N; i++)
            {
                table[i][j] = __gcd(table[i][j - 1], table[i + (len >> 1)][j - 1]);
            }
        }
    }

public:
    gcdSparseTable(const vector<int>& arr) : arr(arr), N(arr.size())
    {
        K = log2(N) + 1;
        resizeTable();
        generateTable();
    }

    void printTableRanges() const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < K; j++)
            {
                if (i + (1 << j) <= N)
                {
                    cout << "(" << i << "," << i + (1 << j) - 1 << ") ";
                }
            }
            cout << endl;
        }
    }

    void printTable() const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < K; j++)
            {
                if (i + (1 << j) <= N)
                    cout << table[i][j] << " ";
            }
            cout << endl;
        }
    }

    int query(int L, int R) const
    {
        int len = R - L + 1;
        int k = log2(len);
        return __gcd(table[L][k], table[R - (1 << k) + 1][k]);
    }
};

int main()
{
    int N, Q;
    cin >> N;
    vector<int> arr;


    for(int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }

    
    gcdSparseTable st(arr);  
    cout << "Printing table: \n";
    st.printTable(); 
    
    cin >> Q;

    for(int i = 0; i < Q; i++)
    {
        int L, R;
        cin >> L >> R;
        cout << st.query(L,R) << endl;
    }

}


#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;

class minSparseTable
{
    int N;
    vector<int> arr;
    vector<vector<int>> table;
    void resizeTable()
    {
        int k = log2(N) + 1;

        table.resize(N);

        for (int i = 0; i < N; i++)
        {
            table[i].resize(k);
        }
    }
    void generateTable()
    {  
        int k = log2(N);

        for(int i = 0; i < N; i++)
        {
            table[i][0] = arr[i];
        }

        for(int j = 1; j <= k; j++)
        {
            int len = 1 << j;
            for(int i = 0; i + len - 1 < N; i++)
            {
                table[i][j] = min(table[i][j-1], table[i + (len >> 1)][j-1]);
            }
        }
    }

public:
    minSparseTable(const vector<int>& arr) : arr(arr), N(arr.size())
    {
        resizeTable();
        generateTable();
    }
    void printTableRanges() const
    {
        int k = log2(N);

        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j <= k; j++)
            {
                if(i + (1 << j) <= N)
                {
                    cout << "(" << i << "," << i + (1 << j) - 1 << ")" << " "; 
                }
            }
            cout << endl;
        }
    }
    void printTable() const
    {
        int k = log2(N);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j <= k; j++)
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

        return min(table[L][k], table[R - (1 << k) + 1][k]);
    }
};



int main()
{
    int N;
    cin >> N;
    vector<int> arr;


    for(int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }

    minSparseTable st(arr);  
    cout << "Printing table: \n";
    st.printTable(); 

    while(1)
    {
        int L, R;
        cout << "Query: ";
        cin >> L >> R;
        cout << "Min: " << st.query(L,R) << endl;
    }

    return 0;
}


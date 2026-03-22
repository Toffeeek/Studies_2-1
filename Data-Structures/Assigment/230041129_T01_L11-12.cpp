#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;

class maxSparseTable
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
                table[i][j] = max(table[i][j-1], table[i + (len >> 1)][j-1]);
            }
        }
    }

public:
    maxSparseTable(const vector<int>& arr) : arr(arr), N(arr.size())
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

        return max(table[L][k], table[R - (1 << k) + 1][k]);
    }
};



int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> arr;


    for(int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }

    maxSparseTable st(arr);  
    cout << "Printing table: \n";
    st.printTable(); 


    int count = 0;
    for(int i = 0; i < Q; i++)
    {
        int L, R;
        cout << "Query " << i+1 << ": ";
        cin >> L >> R;

        int max;
        if(L-1 < R-1-1)
        {
            max = st.query(L-1,R-1-1);
    
        }
        else
        {
            max = arr[L-1];
        }

        
        
        // cout << "max in range: " << max << endl;
        // cout << ""
        if(max <= arr[L-1])
        {
            // cout << "Count increased\n";
            count++;
        }
        else
        {
            // cout << "Count not increased\n";
        }

    }
    cout << "No of balls making it to B: " << count << endl;

    return 0;
}


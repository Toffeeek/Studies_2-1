#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

class minSparseTable
{
private:
    int N;
    vector<int> arr;
    vector<vector<int>> st;
    void resize()
    {
        st.resize(N);
        for (int i = 0; i < N; i++)
        {
            st[i].resize(log2(N) + 1);
        }
    }
    void build()
    {
        for(int i = 0; i < N; i++)
        {
            st[i][0] = arr[i];
        }

        for(int j = 1; j <= log2(N); j++)
        {
            for(int i = 0; i + (1 << j) - 1 < N; i++)
            {
                st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }

public:
    minSparseTable(vector<int> arr)
        : arr(arr), N(arr.size())
    {
        resize(); 
        build();
    }
    void displayTable() const
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j <= log2(N); j++)
            {
                cout << setw(3) << st[i][j] << " ";
            }
            cout << endl;
        }
    }
    int query(int l, int r)
    {
        int len = r - l + 1;
        int leftOutElements = len - log2(len);

        return min(st[l][log2(len)], st[l + leftOutElements][log2(len)]);
    }
};

int main()
{
    vector<int> arr = {5, 3, 1, -6, 8, 10, -3, 15};
    minSparseTable st(arr);
    st.displayTable();

    cout << "query (0,2): " << st.query(0, 2);

    return 0;
}
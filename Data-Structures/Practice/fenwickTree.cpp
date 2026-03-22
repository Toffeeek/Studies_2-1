#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;


int getLSB(int num)
{
    return num & -num;
}

class FenwickTree
{
    int N;
    vector<int> arr;
    vector<int> ft;
    void build()
    {
        for(int i = 0; i < N; i++)
        {
            int lsb = getLSB(i+1);
            if(i + lsb < N)
                ft[i+lsb] += ft[i];            
        }
    }
public:
    FenwickTree(const vector<int>& arr) : arr(arr), N(arr.size()), ft(arr)
    {
        build();
    }
    void displayTree() const
    {
        for(int i = 0; i < N; i++)
        {
            cout << "idx " << setw(2) << i+1 << ": " << ft[i] << endl;
        }
    }
    int sumUpto(int idx) const
    {
        int sum = 0;
        while (idx >= 0)
        {
            sum += ft[idx];
            idx = idx - getLSB(idx + 1);
        }
        return sum;
    }
    int query(int L, int R) const // assumes zero based indexing
    {
        return sumUpto(R) - sumUpto(L-1);
    }
    void pointUpdate(int newVal, int idx)   // zero-based indexing
    {
        int delta = newVal - arr[idx];
        arr[idx] = newVal;

        while (idx < N)
        {
            ft[idx] += delta;
            idx += getLSB(idx + 1);
        }
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
    FenwickTree ft(arr);
    ft.displayTree();

    int Q;
    cin >> Q;

    while(Q--)
    {
        int L, R;
        cin >> L >> R;
        cout << "[" << L << "," << R << "] " << ft.query(L-1, R-1) << endl;
    }

    return 0;
}
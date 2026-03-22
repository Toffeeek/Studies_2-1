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
        cout << "Printing Fenwick Tree:\n";
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
    void pointUpdate(int addVal, int idx)   // zero-based indexing
    {

        arr[idx] = addVal;

        while (idx < N)
        {
            ft[idx] += addVal;
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

        int choice;
        cout << "Enter choice and relevant arguments: ";
        cin >> choice;
        switch(choice)
        {
            case 1:
            {
                int L, R;
                cin >> L >> R;
                cout << "Sum " << "[" << L << "," << R << "] " << ft.query(L-1, R-1) << endl;
                break;
            }
            case 2:
            {
                int i, newVal;
                cin >> i >> newVal;
                ft.pointUpdate(newVal, i-1);
                break;
            }
            default: break;
        }
        ft.displayTree();

    }

    return 0;
}
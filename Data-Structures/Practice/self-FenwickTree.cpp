#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class FenwickTree
{
    int N;
    vector<int> arr;
    vector<int> ft;
    void build()
    {
        for(int i = 1; i <= N; i++)
        {
            int parent = (i-1 + LSB(i));
            if(parent < N) 
            {
                ft[parent] += ft[(i-1)];
            }
        }
    }
    // takes 0 based idx
    int sumUpto(int idx)
    {
        int sum = 0;
        idx++;
        while(idx > 0)
        {
            sum += ft[idx-1];
            idx -= LSB(idx);
        }
        return sum;
    }
public:
    FenwickTree(vector<int> arr)
        : arr(arr), ft(arr), N(arr.size()) 
    {
        build();
    }
    int LSB(int val) const
    {
        return val & -val;
    }
    void printTree() const
    {
        for(int i = 1; i <= N; i++)
        {
            cout << "idx " << i << ": " << ft[i-1] << endl;
        }
    }
    // takes 0 based idx
    int query(int l, int r)
    {
        return sumUpto(r) - sumUpto(l - 1);
    }
    // takes 0 based idx
    void update(int idx, int newVal)
    {
        int delta = newVal - arr[idx];
        arr[idx] = newVal;
        idx++;

        while(idx <= N)
        {
            ft[idx-1] += delta;
            idx += LSB(idx);
        }
    }
};

int main()
{
    vector<int> arr = {5, 10, -3, 6, 8, 10, -5, 15};
    FenwickTree ft(arr);
    ft.printTree();
    cout << "query(1,3): " << ft.query(1,3) << endl;
    ft.update(2, 2);
    cout << "updated query(1,3): " << ft.query(1,3) << endl;
    


    return 0;
}
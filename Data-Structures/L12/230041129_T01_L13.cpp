#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class minSegmentTree
{
private:

    vector<int> segTree;
    int n;

    int queryRec(int left, int right, int qleft, int qright, int pos)
    {
        if (qleft > right || qright < left)
            return INT_MAX;
        if (qleft <= left && qright >= right)
            return segTree[pos];
        int mid = (left + right) / 2;
        return min(queryRec(left, mid, qleft, qright, 2 * pos + 1),
                   queryRec(mid + 1, right, qleft, qright, 2 * pos + 2));
    }
    void init(vector<int> &arr, int left, int right, int pos)
    {
        if (left == right)
        {
            segTree[pos] = arr[left];
            return;
        }
        int mid = (left + right) / 2;
        init(arr, left, mid, 2 * pos + 1);
        init(arr, mid + 1, right, 2 * pos + 2);
        segTree[pos] = min(segTree[2 * pos + 1], segTree[2 * pos + 2]);
    }

public:
    minSegmentTree(vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        init(arr, 0, n - 1, 0);
    }

    int query(int left, int right)
    {
        return queryRec(0, n - 1, left, right, 0);
    }

};

int main()
{
//    cout << "Test1\n";
    int N, Q;
    cin >> N >> Q;
    vector<int> arr;
    for(int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
//    cout << "Test2\n";
    minSegmentTree segTree(arr);
//    cout << "Test3\n";


    for(int i = 0; i < Q; i++)
    {
        int L, R;
        cin >> L >> R;
        cout << segTree.query(L-1, R-1) << "\n";
    }




    return 0;
}

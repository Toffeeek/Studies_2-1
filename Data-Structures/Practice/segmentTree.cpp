#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

class segmentTree_min
{
    int N;
    vector<int> arr;
    vector<int> tree;
    void init(int node, int begin, int end)
    {
        if(begin == end)
        {
            // we are now at a leaf node
            tree[node] = arr[begin];
            return;
        }

        int left  = node * 2 + 1;
        int right = node * 2 + 2;
        int mid   = (begin + end) / 2;

        init(left, begin, mid);
        init(right, mid+1, end);

        tree[node] = min(tree[right], tree[left]);
    }
    int queryRec(int node, int begin, int end, int qleft, int qright)
    {
        if(end < qleft || begin > qright)      // no overlap - out of query range
        {
            return INT_MAX;
        }
        else if(begin >= qleft && end <= qright) // full overlap
        {
            return tree[node];
        }
        else   // partial overlap - gotta look into left and right childen
        {
            int left  = node * 2 + 1; 
            int right = node * 2 + 2;
            int mid   = (begin + end) / 2;
    
            int resLeft  = queryRec(left, begin, mid, qleft, qright);
            int resRight = queryRec(right, mid+1, end, qleft, qright);
    
            return min(resRight, resLeft);
        }
    }
    void updateRec(int node, int begin, int end, int i, int newVal) // 0 based indexing
    {
        if(i > end || i < begin)        // out of range
        {
            return;
        }
        else if(begin == i && end == i) // at the leaf node where the value of index i is stored
        {
            tree[node] = newVal;
        }
        else
        {
            int left  = node * 2 + 1;
            int right = node * 2 + 2;
            int mid   = (left + right) / 2;

            updateRec(left, begin, mid, i, newVal);
            updateRec(right, mid+1, end, i, newVal);

            tree[node] = tree[left] + tree[right];
         }
    }

public:
    segmentTree_min(const vector<int>& arr) : N(arr.size()), arr(arr)
    {
        tree.resize(N*4);
        init(0, 0, N-1);
    }
    void printTree() const
    {
        for(int i = 0; i < 4*N; i++)
        {
            cout << tree[i] << " ";
        }
    }
    int query(int qleft, int qright)
    {
        return queryRec(0, 0, N-1, qleft, qright);
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
    segmentTree_min st(arr);
    st.printTree();

    while(Q--)
    {
        int l, r;
        cin >> l >> r;
        cout << "min" << "[" << l << "," << r << "] " << st.query(l-1,r-1) << endl;
    }


    return 0;
}
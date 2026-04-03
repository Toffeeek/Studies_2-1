#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

class segmentTree_sum
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

        tree[node] = tree[right] + tree[left];
    }
    int queryRec(int node, int begin, int end, int qleft, int qright)
    {
        if(end < qleft || begin > qright)      // no overlap - out of query range
        {
            return 0;
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
    
            return resRight + resLeft;
        }
    }
    int updateRec(int node, int begin, int end, int i, int newVal, int returnVal=-1) // 0 based indexing
    {
        if(i > end || i < begin)        // out of range
        {
            return -1;
        }
        else if(begin == i && end == i) // at the leaf node where the value of index i is stored
        {
            returnVal  = tree[node];
            tree[node] = newVal;
            return returnVal;
        }
        else
        {
            int left  = node * 2 + 1;
            int right = node * 2 + 2;
            int mid   = (begin + end) / 2;

            int valL = updateRec(left, begin, mid, i, newVal, returnVal);
            int valR = updateRec(right, mid+1, end, i, newVal, returnVal);

            if(valL != -1)
                returnVal = valL;
            if(valR != -1)
                returnVal = valR;

            tree[node] = tree[left] + tree[right];
            return returnVal;
         }
         return 0;
    }
    void addRec(int node, int begin, int end, int i, int amount) // 0 based indexing
    {
        if(i > end || i < begin)        // out of range
        {
            return;
        }
        else if(begin == i && end == i) // at the leaf node where the value of index i is stored
        {
            tree[node] += amount;
        }
        else
        {
            int left  = node * 2 + 1;
            int right = node * 2 + 2;
            int mid   = (begin + end) / 2;

            addRec(left, begin, mid, i, amount);
            addRec(right, mid+1, end, i, amount);

            tree[node] = tree[left] + tree[right];
         }
    }

public:
    segmentTree_sum(const vector<int>& arr) : N(arr.size()), arr(arr)
    {
        tree.resize(N*4);
        init(0, 0, N-1);
    }
    void printTree() const
    {
        cout << "Printing Segment Tree: ";
        for(int i = 0; i < 4*N; i++)
        {
            cout << tree[i] << " ";
        }
        cout << endl;
    }
    int query(int qleft, int qright)
    {
        return queryRec(0, 0, N-1, qleft, qright);
    }
    int update(int i, int newVal) 
    {
        arr[i] = newVal;
        return updateRec(0, 0, N-1, i, newVal, 0);
    }
    void add(int amount, int i)
    {
        addRec(0, 0, N-1, i, amount);
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
    segmentTree_sum st(arr);
    st.printTree();

    while(Q--)
    {
        int choice;
        cout << "Enter choice and relevant arguments: ";
        cin >> choice;
        switch(choice)
        {
        case 1: 
        {       
            int i;
            cin >> i;
            cout << "The poor gets: " << st.update(i-1, 0) << endl;
            st.printTree();
            break;
        }

        case 2:
        {
            int i, v;
            cin >> i >> v;
            st.add(v, i-1);
            st.printTree();
            break;
        }  

        case 3:  
        {
            int l, r;
            cin >> l >> r;
            cout << "amount in the interval: " << st.query(l-1, r-1) << endl;
            break;
        }

        default: break;
        }
    }


    return 0;
}
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class sumSegmentTree
{
private:
    int N;
    vector<int> arr;
    vector<int> st;
    vector<int> lazy;
    void buildRec(int curr, int b, int e)
    {
        if(b == e)
        {
            st[curr] = arr[b];
            return;
        }
        int left = curr * 2 + 1;
        int right = curr * 2 + 2;
        int mid = (b+e) / 2;

        buildRec(left, b, mid);
        buildRec(right, mid+1, e);

        st[curr] = st[left] + st[right];
    }
    int queryRec(int curr, int currL, int currR, int qL, int qR)
    {

        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int mid = (currL + currR) / 2;

        int nNodes = currR - currL + 1;
        int nLeftNodes = mid - currL + 1;
        int nRightNodes = currR - (mid + 1) + 1;

        if(lazy[curr] != 0)
        {
            st[curr] += lazy[curr];

            if(currL != currR)
            {
                lazy[left] += lazy[curr] * (nLeftNodes / nNodes);
                lazy[right] += lazy[curr] * (nRightNodes / nNodes);
            }
            lazy[curr] = 0;
        }

        if(currR < qL || currL > qR)
        {
            return 0;
        }
        else if(currL >= qL && currR <= qR)
        {
            return st[curr];
        }

        int leftRes = queryRec(left, currL, mid, qL, qR);
        int rightRes = queryRec(right, mid+1, currR, qL, qR);

        return leftRes + rightRes;
    }
    // lazy propagation
    void rangeUpdateRec(int curr, int currL, int currR, int uL, int uR, int inc)
    {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int mid = (currL + currR) / 2;

        int nNodes = currR - currL + 1;
        int nLeftNodes = mid - currL + 1;
        int nRightNodes = currR - (mid + 1) + 1;

        if(lazy[curr] != 0)
        {
            st[curr] += lazy[curr];

            if(currL != currR)
            {
                lazy[left] += lazy[curr] * (nLeftNodes / nNodes);
                lazy[right] += lazy[curr] * (nRightNodes / nNodes);
            }
            lazy[curr] = 0;
        }

        if(currR < uL || currL > uR)
            return;

        if(currL >= uL && currR <= uR)
        {
            st[curr] += inc * nNodes;

            if(currL != currR)
            {
                lazy[left] += inc * nLeftNodes;
                lazy[right] += inc * nRightNodes;  
            }
            return;
        }

        rangeUpdateRec(left, currL, mid, uL, uR, inc);
        rangeUpdateRec(right, mid+1, currR, uL, uR, inc);

        st[curr] = st[right] + st[left];
    }
    void build()
    {
        buildRec(0, 0, N-1);
    }
public:
    sumSegmentTree(vector<int> arr)
        : arr(arr), N(arr.size())
    {
        st.resize(4*N);
        lazy.assign(4*N, 0);

        build();
    }
    int query(int ql, int qr)
    {
        return queryRec(0, 0, N-1, ql, qr);
    }
    void rangeUpdate(int uL, int uR, int inc)
    {
        rangeUpdateRec(0, 0, N-1, uL, uR, inc);
    }
};

int main()
{
    vector<int> arr = {5, 3, 1, -6, 8, 10, -3, 15};
    sumSegmentTree st(arr);

    cout << st.query(2, 6) << endl;   // 10
    st.rangeUpdate(2, 5, 4);
    cout << st.query(2, 6) << endl;   // 26
    cout << st.query(0, 7) << endl;   // original sum 33, after +16 => 49

    return 0;
}
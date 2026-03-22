#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define int long long
const int INF = (int)1e18;

struct node {
    int lazy;
    int val;
    node() : lazy(0), val(0) {}
};

node merge(node a, node b) {
    node ans;
    ans.val = min(a.val, b.val);
    return ans;
}

vector<int> arr;
vector<node> tree;

void push(int id, int l, int r) {
    if (tree[id].lazy) {
        tree[id].val += tree[id].lazy;
        if (l != r) {
            tree[id << 1].lazy += tree[id].lazy;
            tree[id << 1 | 1].lazy += tree[id].lazy;
        }
        tree[id].lazy = 0;
    }
}

void build(int id, int l, int r) {
    if (l == r) {
        tree[id].val = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    tree[id] = merge(tree[id << 1], tree[id << 1 | 1]);
}

void update(int id, int l, int r, int L, int R, int v) {
    push(id, l, r);
    if (R < l || L > r) return;
    if (L <= l && R >= r) {
        tree[id].lazy += v;
        push(id, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    update(id << 1, l, mid, L, R, v);
    update(id << 1 | 1, mid + 1, r, L, R, v);
    tree[id] = merge(tree[id << 1], tree[id << 1 | 1]);
}

int query(int id, int l, int r, int L, int R) {
    push(id, l, r);
    if (R < l || L > r) return INF;
    if (L <= l && R >= r) return tree[id].val;
    int mid = (l + r) >> 1;
    int left = query(id << 1, l, mid, L, R);
    int right = query(id << 1 | 1, mid + 1, r, L, R);
    return min(left, right);
}

void status(int n) {
    int size = 2 * n - 1;
    
    for (int i = 1; i <= size; i++) {
        cout << tree[i].val << (i == size ? "" : " ");
    }
    cout << "\n";
    
    for (int i = 1; i <= size; i++) {
        cout << tree[i].lazy << (i == size ? "" : " ");
    }
    cout << "\n\n";
}

signed main() {
    int n, q;
    cin >> n >> q;
    arr.resize(n + 1);
    tree.resize(4 * n + 5);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1,1,n);
    status(n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 2) {
            int L, R; cin >> L >> R;
            int val; cin >> val;
            update(1,1,n,L,R,val);
            status(n);
        } else {
            int L, R; cin >> L >> R;
            cout << query(1,1,n,L,R) << endl;
            status(n);
        }
    }
    return 0;
}


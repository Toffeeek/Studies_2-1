#include <iostream>
#include <vector>
using namespace std;

#define int long long

int n, q;
vector<int> tree, arr;

int add(int a, int b) {
    return a + b;
}

void build(int id, int begin, int end) {
    if (begin == end) {
        tree[id] = arr[begin];
        return;
    }
    int mid = (begin + end) / 2;
    int left = 2 * id;
    int right = 2 * id + 1;
    build(left, begin, mid);
    build(right, mid + 1, end);
    tree[id] = add(tree[left], tree[right]);
}

void update(int id, int begin, int end, int pos, int val) {
    if (pos < begin || pos > end) return; 
    if (begin == end) {
        tree[id] += val;
        arr[begin] += val;
        return;
    }
    int mid = (begin + end) / 2;
    int left = 2 * id;
    int right = 2 * id + 1;
    update(left, begin, mid, pos, val);
    update(right, mid + 1, end, pos, val);
    tree[id] = add(tree[left], tree[right]);
}

int query(int id, int begin, int end, int i, int j) {
    if (i > end || j < begin) return 0;
    if (i <= begin && end <= j) return tree[id];
    int mid = (begin + end) / 2;
    int left = 2 * id;
    int right = 2 * id + 1;
    int lq = query(left, begin, mid, i, j);
    int rq = query(right, mid + 1, end, i, j);
    return add(lq, rq);
}

void status() {
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
}

signed main() {
    cin >> n >> q;
    arr.resize(n + 1, 0);
    tree.resize(4 * n, 0);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int i; cin >> i;
            cout << arr[i] << " ";
            update(1,1,n,i,-arr[i]);
            cout << "(";
            status();
            cout << ")" << endl;
        } else if (type == 2) {
            int i, v; cin >> i >> v;
            update(1,1,n,i,v);
            status();
            cout << endl;
        } else {
            int i, j;
            cin >> i >> j;
            cout << query(1, 1, n, i, j) << endl;
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

int n, q;
vector<int> tree, arr;

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
    tree[id] = min(tree[left], tree[right]);
}

int query(int id, int begin, int end, int i, int j) {
    if (i > end || j < begin) return 1e9;
    if (i <= begin && end <= j) return tree[id];
    int mid = (begin + end) / 2;
    int left = 2 * id;
    int right = 2 * id + 1;
    int min1 = query(left, begin, mid, i, j);
    int min2 = query(right, mid + 1, end, i, j);
    return min(min1, min2);
}

int main() {
    cin >> n >> q;
    arr.resize(n + 1, 0);
    tree.resize(4 * n, 0);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int i, j;
        cin >> i >> j;
        cout << query(1, 1, n, i, j) << endl;
    }
    return 0;
}

/*
5 3
78 1 22 12 3
1 2
3 5
4 4


1
3
12


*/
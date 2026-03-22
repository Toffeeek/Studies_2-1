#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

#define mx 100100
int ar[mx];
int tree[mx];

int read(int idx){
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx, int val, int n){
    while (idx <= n){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

void status(int n) {
    for (int i = 1; i <= n; i++) {
        cout << i << ":" << tree[i] << " ";
    }
    cout << endl << endl;
}

int main() {
    ios_base::sync_with_stdio(false);   
    cin.tie(NULL);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) { cin >> ar[i]; update(i, ar[i], n); }
    cout << "Status of Fenwick Tree (idx: value):" << endl;
    status(n);

    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int type; cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            int x = read(r);
            int y = read(l - 1);
            int sum = x - y;
            cout<<"Query: "<<" Sum="<<sum<<endl;
        } else {
            int i; cin >> i;
            int val; cin >> val;
            update(i, val, n);
            cout << "Updated tree:" << endl;
            status(n);
        }
    }

    return 0;
}


/*
Status of Fenwick Tree (idx: value):
1:5 2:15 3:5 4:30 5:5 6:15 7:5 8:60 9:5 10:15 11:5 12:30 13:5 14:15 15:5 16:120 

Query:  Sum=50
Query:  Sum=80
Query:  Sum=35
Updated tree:
1:5 2:15 3:5 4:30 5:5 6:15 7:5 8:60 9:20 10:30 11:5 12:45 13:5 14:15 15:5 16:135 

Query:  Sum=95
Query:  Sum=35

*/
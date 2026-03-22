#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define gcd __gcd

const int N = 2e5 + 9;
const int K = 20;
int table[N][K], a[N], lg[N];

void build_log(int n) {
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }
}

void build(int n) {
    build_log(n);
    for (int j = 1; j <= lg[n]; j++) {
        for(int i = 0; i + (1 << j) <= n; i++) {
            table[i][j] = gcd(table[i][j-1], table[i+(1<<(j-1))][j-1]);
        }
    }
}

int query(int L, int R) {
    int window = R - L + 1;
    int j = lg[window];
    return gcd(table[L][j], table[R-(1<<j)+1][j]);
}

void ranges_stored(int n) {
    cout << "Ranges to be stored in Sparse Table:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; i+(1<<j) <= n ; j++) {
            cout<<"("<<i<<","<<(i+(1<<j)-1)<<")"<<" ";
        }
        cout << endl;
    }
    cout << endl;
}

void status(int n) {
    cout << "Status of Sparse Table:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; i+(1<<j) <= n ; j++) {
            cout<<table[i][j]<<" ";
            // cout<<query(i,i+(1<<j)-1)<<" ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        table[i][0] = a[i];
    }
    build(n);
    ranges_stored(n);
    status(n);
    int q; cin >> q;
    for (int i = 1; i <= q; i++) {
        int L, R; cin >> L >> R;
        int j = lg[R-L+1];
        cout<<"Query-"<<i<<": GCD="; 
        cout<<query(L,R)<<" ";
        cout<<"gcd(["<<L<<","<<L+(1<<j)-1<<"],["<<R-(1<<j)+1<<","<<R<<"])"<<endl;
    }
    return 0;
}
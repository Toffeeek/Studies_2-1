#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 2e5 + 9;
const int K = 20;
int table[N][K], a[N], lg[N];

int merge(int a, int b)
{
    return (a | b);
}

void build_log(int n)
{
    for (int i = 2; i <= n; i++)
    {
        lg[i] = lg[i / 2] + 1;
    }
}

void build(int n)
{
    build_log(n);
    for (int j = 1; j <= lg[n]; j++)
    {
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int L, int R)
{
    int window = R - L + 1;
    int j = lg[window];
    return merge(table[L][j], table[R - (1 << j) + 1][j]);
}

int main()
{
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        table[i][0] = a[i];
    }
    build(n);
    int Q;
    cin >> Q;
    while (Q--)
    {
        int L, R, t_id;
        cin >> L >> R >> t_id;
        cout << (query(L, R) == a[t_id] ? "YES" : "NO") << endl;
    }
    return 0;
}
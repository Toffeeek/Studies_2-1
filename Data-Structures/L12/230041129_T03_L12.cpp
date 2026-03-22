#include <iostream>
#include <vector>
using namespace std;

int LSB(int num)
{
    return num & -num;
}

void construct(vector<int>& fenwickTree)
{
    for(int i = 1; i <= fenwickTree.size(); i++)
    {
        int j = i + LSB(i);
        if(j <= fenwickTree.size())
        {
            fenwickTree[j-1] = fenwickTree[j-1] + fenwickTree[i-1];
        }

    }
}

int calculateSum(const vector<int>& fenwickTree, int idx)
{
    int sum = 0; 
    
    while(idx > 0)
    {
        sum += fenwickTree[idx - 1]; 
        int lsb = LSB(idx);
        idx -= lsb;
    }
    return sum;
}
int calculateRangeSum(vector<int> fenwickTree, int L, int R)
{
    return calculateSum(fenwickTree, R) - calculateSum(fenwickTree, L-1); 
}

int main()
{
    int N;
    cin >> N;
    vector<int> arr;
    for(int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }

    cout << "Ranges to be stored: \n";
    for(int i = 1; i <= N; i++)
    {
        cout << i  << ": " <<  "(" <<  i - LSB(i) + 1 << "," << i << ")" << endl; 
    }

    vector<int> fenwickTree = arr;
    construct(fenwickTree);

    for(int i = 1; i <= fenwickTree.size(); i++)
    {
        cout << i << ": " << fenwickTree[i-1] << endl;
    }

    int Q;
    cin >> Q;
    for(int i = 0; i < Q; i++)
    {
        int L, R;
        cin >> L >> R;
        cout << "Sum in range [" << L << "," << R << "]: " << calculateRangeSum(fenwickTree, L, R) << endl;
    }

    

    

    return 0;
}

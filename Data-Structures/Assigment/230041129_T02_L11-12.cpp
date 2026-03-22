#include <iostream>
#include <vector>
using namespace std;

class prefixSum_bincount
{
    vector<int> bits;
    vector<int> count1;
    int totalOneCount;
    void build()
    {
        int oneCount = 0;
        for(int i = 0; i < bits.size(); i++)
        {
            if(bits[i] == 1)
            {
                count1[i] = ++oneCount;
            }
            else
            {
                count1[i] = oneCount;
            }
        }
        totalOneCount = oneCount;
    }
public:
    prefixSum_bincount(vector<int> arr) : bits(arr), totalOneCount(0)
    {
        count1.assign(arr.size(), 0);
        build();
    }
    void print() const
    {
        cout << "B: ";
        for(int i = 0; i < bits.size(); i++)
        {
            cout << bits[i] << " ";
        }
        cout << "\n1: ";
        for(int i = 0; i < bits.size(); i++)
        {
            cout << count1[i] << " ";
        }
        cout << endl;
    }
    int query(int L, int R)
    {
        int size = R - L + 1;
        if(size % 2 == 1)
            return -1;

        int ones;
        if(L > 0)
            ones = count1[R] - count1[L-1];
        else
            ones = count1[R];
        
        int zeroes = size - ones;

        int higher, lower;

        cout << "zeroes: " << zeroes << endl;
        cout << "ones: " << ones << endl;

        if(zeroes > ones)
        {
            higher = zeroes;
            lower = ones;
        }
        else
        {
            higher = ones;
            lower = zeroes;
        }

        return (higher - lower) / 2;
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

    prefixSum_bincount ps(arr);
    ps.print();

    for(int i = 0; i < Q; i++)
    {
        int L, R;
        cin >> L >> R;
        int bitsFlipped = ps.query(L-1, R-1);
        cout << "Bits flipped: " << bitsFlipped << endl;
        
    }


    return 0;
}
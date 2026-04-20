#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
using namespace std;

class DisjoinSet
{
    int N;
    vector<pair<int, int>> repArray;
public:
    DisjoinSet(int n) : N(n)
    {
        for(int i = 0; i < N; i++)
        {
            repArray.push_back({i, 0});
        }
    }
    void set_union(int first, int second)
    {
        int firstRep = find(first);
        int secondRep = find(second);

        if (firstRep == secondRep)
            return;

        int rank1 = repArray[firstRep].second;
        int rank2 = repArray[secondRep].second;

        if (rank1 < rank2)
        {
            repArray[firstRep].first = secondRep;
        }
        else if (rank1 > rank2)
        {
            repArray[secondRep].first = firstRep;
        }
        else
        {
            repArray[secondRep].first = firstRep;
            repArray[firstRep].second++;
        }
    }
    // takes zero based indexing
    int find(int idx)
    {
        if(idx == repArray[idx].first)
        {
            return idx;
        }
        else
        {
            repArray[idx].first = find(repArray[idx].first);
            return repArray[idx].first;
        }
    }
    void printSet() const
    {
        cout << "idx: ";
        for(int i = 0; i < N; i++)
        {
            cout << setw(2) << i << " ";
        }
        cout << endl << "rep: ";
        for(auto p : repArray)
        {
            cout << setw(2) << p.first << " ";
        }
        cout << endl;
    }

};

int main()
{
    int N = 10;
    DisjoinSet ds(N);
    ds.set_union(0, 1);
    ds.set_union(1, 2);
    ds.set_union(2, 3);
    ds.set_union(4, 5);
    ds.set_union(4, 6);
    ds.set_union(4, 7);
    ds.set_union(4, 8);
    ds.set_union(4, 9);
    ds.set_union(4, 9);
    ds.printSet();
    // cout << "Rep of 3: " << ds.find(3) << endl;
    // ds.printSet();



    return 0;
}
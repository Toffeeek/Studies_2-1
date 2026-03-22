#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

void repArr_init(int repArr[], int N)
{
    for(int i = 0; i < N; i++)
    {
        repArr[i] = i;
    }
}

int find(int repArr[], int item)
{
    if(repArr[item] == item)
    {
        return item;
    }
    else
        return find(repArr, repArr[item]);
}
void _union(int repArr[], int u, int v)
{
    int u_rep = find(repArr, u);
    int v_rep = find(repArr, v);
    cout << "rep(" << u << ") = " << u_rep << endl;
    cout << "rep(" << v << ") = " << v_rep << endl;

    if(u_rep != v_rep)
    {
        repArr[v_rep] = u_rep;
    }
    else
    {
        return;
    }

}

int findLargestSet(int repArr[], int N)
{
    vector<int> setSizes(N, 0);
    for(int i = 0; i < N; i++)
    {
        int rep = find(repArr, i);
        setSizes[rep]++;
    }
    int maxSize = 0;
    for(int i : setSizes)
    {
        if(i > maxSize)
            maxSize = i;
    }
    return maxSize;
}
int countTotalSets(int repArr[], int N)
{
    int totalSets = 0;
    for(int i = 0; i < N; i++)
    {
        int rep = find(repArr, i);
        if(rep == i)
        {
            totalSets++;
        }
    }
    return totalSets; 
}


int main()
{
    int N, M;
    cin >> N >> M;
    int repArr[N];
    repArr_init(repArr, N);
    unordered_map<int, list<int>> table;

    for(int i = 0; i < M; i++)
    {
        int r1, r2;
        cin >> r1 >> r2;
        r1--; r2--;
        _union(repArr, r1, r2);
        
        int largestSet = findLargestSet(repArr, N);
        int totalSets = countTotalSets(repArr, N);

        cout << "Total number of sets: " << totalSets << endl;
        cout << "Largest set size: " << largestSet << endl;
    
    } 
        
    // cout << "Representative array: ";
    // for(int i : repArr)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    

    return 0;
}
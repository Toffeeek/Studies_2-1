#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;



class TopologicalSort
{
    int N;
    vector<vector<int>> adjList;
    vector<int> inDegree;
    vector<int> tsortRes;
    bool noCycles;
public:
    TopologicalSort(vector<vector<int>> adjList)
        : adjList(adjList), N(adjList.size()), noCycles(true)
    {
        inDegree.resize(N);       
        for(const auto& vec : adjList)
        {
            for(int v : vec)
            {
                inDegree[v]++;
            }
        }

        displayInDegree();
        tsort();
    }
    void displayInDegree() const
    {
        int i = 0;
        cout << "In degrees: \n";
        cout << "ver  : ";
        for(const auto& vec : inDegree)
        {
            cout << setw(2) << i++ << " ";
        }
        cout << endl << "indeg: ";
        for(const auto& v : inDegree)
        {
            cout << setw(2) << v << " ";
        }
        cout << endl;
    }
    void displayList() const
    {
        int i = 0;

        cout << "ADJ LIST: \n";
        for(const auto& vec : adjList)
        {
            cout << setw(2) << i++ << ": ";
            for(int v : vec)
            {
                cout << v << ", ";
            }
            cout << endl;
        }
    }
    void tsort()
    {
        queue<int> q;
        int i = 0;
        for(int deg : inDegree)
        {
            if(deg == 0)
            {
                q.push(i);
            }
            i++;
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            tsortRes.push_back(u);

            for (int v : adjList[u])
            {
                inDegree[v]--;
                if (inDegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        if (tsortRes.size() != N)
        {
            noCycles = false;
        }
    }
    void displaySort() const
    {
        if(noCycles)
        {
            cout << "TOPOLOGICAL SORT: ";
            for(auto val : tsortRes)
            {
                cout << val << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "The graph has a cycle, topological sort is not possible\n";
        }
    }
};

int main()
{
    int N = 10;
    vector<vector<int>> adjList = 
    {
        {1, 2},        // 0
        {3},       // 1
        {3, 4},       // 2
        {5},    // 3
        {5},       // 4
        {},    // 5
        {7},       // 6
        {8},       // 7
        {9},       // 8
        {}        // 9
    };
    TopologicalSort ts(adjList);
    ts.displayList();
    ts.displaySort();




    return 0;
}
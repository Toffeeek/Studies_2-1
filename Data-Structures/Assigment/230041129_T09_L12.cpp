#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <iomanip>
#include <algorithm>
using namespace std;



// METHODS TO ERASE FROM A VECTOR

// method 1: removes all the elements of the given val
// #include <algorithm>
// v.erase(remove(v.begin(), v.end(), val), v.end());


// method 2: removes the first element of the given val
// auto it = find(v.begin(), v.end(), 2);
// if(it != v.end())
//     v.erase(it);

// method 3: delete by index
// v.erase(v.begin() + index);


class Graph
{
    int V, E;
    vector<string> students;
    vector<vector<int>> adjList;
    vector<bool> added;
    vector<pair<int, int>> sortOrder;
    
    int getIndex(string student) const
    {
        for(int i = 0; i < V; i++)
        {
            if(students[i] == student)
            {
                return i;
            }
        }
        cout << "INVALID INDEX\n";
        return -1;
    }
    string getStudent(int i) const
    {
        if(i < V)
        return students[i];
        else
        return "STUDENT INDEX OUT OF BOUNDS";
    }
    void buildAdjList(const vector<pair<string, string>>& edges)
    {
        for(int i = 0; i < E; i++)
        {
            int v1 = getIndex(edges[i].first); 
            int v2 = getIndex(edges[i].second);
            
            // adjList[v1].push_back(v2);
            adjList[v2].push_back(v1);
        }
    }
    void topologicalSort() 
    {
        vector<vector<int>> adjList(this->adjList);
        
        queue<int> zeroInorderVertices;
        added.assign(V, false);
        // vector<pair<int, int>> sortOrder;
        
        int level = 0;
        
        for(int i = 0; i < V; i++)
        {
            if(adjList[i].empty() && !added[i])
            {
                cout << getStudent(i) << " pushed into the queue\n";
                zeroInorderVertices.push(i);
                sortOrder.push_back({i, level++});
                added[i] = true;
            }
        }
        
        while(!zeroInorderVertices.empty())
        {
            int frontVertex = zeroInorderVertices.front();
            zeroInorderVertices.pop();
            cout << getStudent(frontVertex) << " popped into the queue\n";
            
            for(int i = 0; i < V; i++)
            {
                adjList[i].erase(remove(adjList[i].begin(), adjList[i].end(), frontVertex), adjList[i].end());
                if(adjList[i].empty() && !added[i])
                {
                    cout << getStudent(i) << " pushed into the queue\n";   
                    zeroInorderVertices.push(i);
                    sortOrder.push_back({i, level});
                    added[i] = true;
                }
            }
            level++;
            
        }
        
        if(sortOrder.size() == V)
        isDAG = true;
    }
    
    int getSortIndex(int target)
    {
        for(int i = 0; i < V; i++)
        {
            if(sortOrder[i].first == target)
            return i;
        }
        return -1;
    }
    
    public:
    Graph(const vector<string>& student, const vector<pair<string, string>>& edges)
    : students(student), V(student.size()), E(edges.size())
    {
        adjList.resize(V);
        // visited.assign(V, false);
        buildAdjList(edges);
        topologicalSort();
    }
    void printAdjList() const
    {
        cout << "PRINTING STUDENTS: \n";
        for(int i = 0; i < V; i++)
        {
            cout << setw(8) << left << getStudent(i) << ": ";
            for(int j = 0; j < adjList[i].size(); j++)
            {
                cout << setw(12) << left << getStudent(adjList[i][j]) << " ";
            }
            cout << endl;
        }
    }
    void printSortOrder() const
    {
        cout << "PRINTING SORT ORDER: ";
        for(const auto& p : sortOrder)
        {
            cout << "(" << getStudent(p.first) << "," << p.second << ") ";
        }
        cout << endl;
    }
    void query(string bebullied, string dobully)
    {
        
        
        
        
        int bullierIndex = getSortIndex(getIndex(dobully));
        int bebulliedIndex = getSortIndex(getIndex(bebullied));
        
        if(bebulliedIndex > bullierIndex)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
        
    }
    bool isDAG;

};



int main()
{
    int V, E, Q;
    cin >> V >> E >> Q;
    vector<string> vertices;
    for(int i = 0; i < V; i++)
    {
        string v;
        cin >> v;
        vertices.push_back(v);
    }

    vector<pair<string, string>> edges;

    for(int i = 0; i < E; i++)
    {
        string ct1, ct2;
        cin >> ct1 >> ct2;

        edges.push_back({ct1, ct2});
    }

    Graph g(vertices, edges);
    g.printAdjList();
    g.printSortOrder();

    if(g.isDAG)
    {
        for(int i = 0; i < Q; i++)
        {
            string s1, s2;
            cin >> s1 >> s2;
            g.query(s1, s2);
    
        }
    }
    else
    {
        cout << "IMPOSSIBLE\n";
    }




    return 0;
}
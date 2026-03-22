#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

class Islands
{
    vector<vector<int>> map;
    vector<vector<pair<int, int>>> rep;
    int R, C, N;

    void resizeSet()
    {
        rep.resize(R);
        for(int i = 0; i < R; i++)
        {
            rep[i].resize(C);
        }
    }
    void makeSet()
    {
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < C; j++)
            {
                rep[i][j].first = i;
                rep[i][j].second = j;
            }
        }
    }
    // returns the leftmost col to the input coordinate that is 1
    int getLeftmost1(int r, int c) const
    {
        int _c = c;
        while(_c > 0 && map[r][_c - 1] == 1)
        {
            // cout << "topmostrow func\n";
            _c--;
        }
        return _c;
    }
    // returns the topmost row to the input coordinate that is 1
    int getTopmost1(int r, int c) const
    {
        int _r = r;
        while(_r > 0 && map[_r - 1][c] == 1)
        {
            // cout << "topmostrow func\n";
            _r--;
        }
        return _r;
    }
    auto calcRep(int r, int c) const
    {
        int repCol = getLeftmost1(r, c);
        int repRow = getTopmost1(r, repCol);

        int prevrow, prevcol;

        do
        {
            // cout << "getting rep index\n";

            prevcol = repCol;
            prevrow = repRow;
                  
            repCol = getLeftmost1(repRow, repCol);
            repRow = getTopmost1(repRow, repCol);

        } while(!(prevrow == repRow && prevcol == repCol));

        return pair{repRow, repCol};
    }
    void unifyIslands() 
    {
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < C; j++)
            {
                if(map[i][j] == 1)
                {
                    rep[i][j] = calcRep(i, j);
                    
                }
            }
        }
    }

public:
    Islands(const vector<vector<int>>& map) 
        : map(map), R(map.size()), C(map[0].size()), N(0)
    {
        // cout << "resizing\n";
        resizeSet();
        // cout << "making set\n";
        makeSet();
        unifyIslands();

        
    }
    void printMap() const
    {
        cout << "PRINTING MAP:\n";
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < C; j++)
            {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }
    void printIslands() const
    {
        cout << "PRINTING ISLANDS:\n";
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < C; j++)
            {
                cout << "(" << rep[i][j].first << "," << rep[i][j].second << ") ";
            }
            cout << endl;
        }
    }
    int countIslands() const
    {
        int n = 0;
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < C; j++)
            {
                if(rep[i][j].first == i && rep[i][j].second == j && map[i][j] == 1)
                {
                    n++;
                }
            }
        }
        return n;
    }
};




int main()
{
    int R, C;
    cin >> R >> C;
    vector<vector<int>> map(R, vector<int>(C, 0));
    // cout << "taking input\n";
    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            int x;
            cin >> x;
            map[i][j] = x;
        }
    }

    // cout << "input taken\n";

    Islands i(map);
    i.printMap();
    i.printIslands();

    cout << "Number of islands: " << i.countIslands() << endl;



    return 0;
}
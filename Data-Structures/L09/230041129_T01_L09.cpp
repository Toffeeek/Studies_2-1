#include <iostream>
#include <cmath>

using namespace std;

int insertedElements = 0;

int hash2(int x)
{
    return 7 - (x % 7); 
}

void insert(int table[], int N, int x, int type)
{
        int k = x % N;
        int idx;
        
        for(int i = 0; i < 6; i++)
        {
            if(type == 1 || type == 2)
            {
                idx = int((k + pow(i , type))) % N;
            }
            else
            {
                idx = int((k + i * hash2(x))) % N;
            }
    
            if(table[idx] == 0)
            {
                table[idx] = x;
                cout << "Inserted at index: " << idx << " ";
                insertedElements++;
                cout << "Load factor: " << float(insertedElements)/float(N) << endl;
                return;
            }
            else
            {
                cout << "Collision at index: " << idx << endl;
            }
        }
        cout << "Could not insert, abandoning the element\n";   
    
}

int main()
{
    int choice, N,  Q;
    cin >> choice >> N >> Q;

    int table[N] = {0};

    for(int i = 0; i < Q; i++)
    {
        int x;
        cin >> x;
        insert(table, N, x, choice);
    }

    for(int i = 0; i < N; i++)
    {
        cout << i << ": ";
        if(table[i] != 0)   
            cout << table[i];
        cout << endl;
    }


    return 0;
}
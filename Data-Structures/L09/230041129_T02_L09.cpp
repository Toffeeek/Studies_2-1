#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    unordered_map<int , int > table;

    while(1)
    {
        int x;
        cin >> x;
        if(x == -1)
            break;
        
        table[x]++;
    }

    for(auto &bucket : table)
    {
        cout << bucket.first << ": " << bucket.second << endl;
    }

    int target; 
    cin >> target;

    bool pairFound = false;
    for(auto &bucket : table)
    {
        if(target - bucket.first >= 0 && table[target - bucket.first] > 0)
        {
            cout << "(" << bucket.first << ", " << target - bucket.first << ")" << endl;
            table[target - bucket.first]--;
            bucket.second--;
            pairFound = true;
        }
    }

    if(!pairFound)
        cout << "No pairs found :( \n";

    


    return 0;
}
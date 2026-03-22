#include <iostream>
#include <unordered_map>
#include <map>
#include <cctype>
#include <vector>
#include <list>
using namespace std;

bool isWord(string str)
{
    for(int i = 0; i < str.size(); i++)
    {
        // follow
        // follow,
        if(!isalpha(str[i]))
        {
            return false;
        }
    }
    return true;
}

auto formWord(string str)
{
    string word = "";

    for(int i = 0; i < str.size(); i++)
    {
        if(isalpha(str[i]))
        {
            word += str[i];
        }
    }
    return word;
}

int main()
{
    map<int, list<int>> adjList;
    // v1 -> v2
    // v1 -> v3
    
    adjList[5].push_back(5);
    adjList[1].push_back(2);
    adjList[1].push_back(3);
    adjList[2].push_back(5);
    adjList[3].push_back(5);
    adjList[4].push_back(1);

    // v1 : v2, v3


    for(auto &bucket : adjList)
    {
        cout << bucket.first << ": ";
        for(int &ver : bucket.second)
        {
            cout << ver << " "; 
        }
        cout << endl;
    }


    unordered_map<string, int> table;

    auto val = 5;
    auto str = "tawfiq";

    while(1)
    {
        string word;
        cin >> word;
        if(word == "-1")
            break;

        if(!isWord(word))
            word = formWord(word);

        if(word != "")
            table[word]++;
    }



    


    for(auto &bucket : table)
    {
        /*
        bucket.first;
        bucket.second;
        1. space complexity increase
        2. cannot modify original values 
        */

        if(bucket.second > 1)
            cout << bucket.first << ": " << bucket.second << endl;
    }

    


    
    

    return 0;
}
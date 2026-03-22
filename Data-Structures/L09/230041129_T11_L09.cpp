#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

int hasher(string str)
{
    int hashVal = 0;
    int freq[26] = {0};
    for(int i = 0; i < str.size(); i++)
    {
        char ch = tolower(str[i]);
        freq[ch - 'a']++;
    }
    for(int i = 0; i < 26; i++)
    {
        if(freq[i] == 0)
        {
            hashVal += ('a' + i) * 37;
        }
    }
    return hashVal;   
}

int main()
{
    unordered_map<int, list<string>> table;

    while(1)
    {
        string word;
        cin >> word;
        cin.ignore();
        if(word == "-1")
            break;

        int hash = hasher(word);
        table[hash].push_front(word);
    }

    string key;
    cin >> key;
    cin.ignore();
    int keyHash = hasher(key);
        

    for(auto &l : table[keyHash])
    {
        cout << l << " ";
    }



    return 0;
}
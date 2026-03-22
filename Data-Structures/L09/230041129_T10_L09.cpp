#include <iostream>
#include <unordered_map>

using namespace std;

const string morse[] =    
{
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",
    ".---","-.-",".-..","--","-.","---",".--.","--.-",
    ".-.","...","-","..-","...-",".--","-..-","-.--","--.."
};

string morseTransform(string word)
{
    string transform = "";
    for(int i = 0; i < word.size(); i++)
    {
        transform += morse[word[i] - 'a'];
    }
    return transform;
}


int main()
{
    unordered_map<string, int> table;
    int N;
    cin >> N;

    // cout << morseTransform("cab");

    while(N--)
    {
        string word;
        cin >> word;
        cin.ignore();
        table[morseTransform(word)]++;
    }

    int count = 0;
    for(auto &bucket : table)
    {
        if(bucket.second > 0)
            count++;
    }
    cout << "Total unique transformations: " << count << endl;
    for(auto &bucket : table)
    {
        cout << bucket.first << endl;
    }

    

    return 0;
}
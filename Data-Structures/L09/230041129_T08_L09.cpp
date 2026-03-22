#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

typedef struct Node
{
    bool endmark;
    Node *next[26*2];
    Node()
    {
        endmark = false;
        for (int i = 0; i < 26*2; i++)
            next[i] = NULL;
    }
} Node;
Node* root = new Node();
void insert(string str)
{
    Node *curr = root;
    for (int i = 0; i < str.size(); i++)
    {
        int idx;
        if(isupper(str[i])) 
        {
            idx = str[i] - 'A';
            idx += 26;
        }
        else
        {
            idx = str[i] - 'a';
        }
            
        if (curr->next[idx] == NULL)
            curr->next[idx] = new Node();
        curr = curr->next[idx];
    }
    curr->endmark = 1;
}

bool checkAbbreviation(string word, string abbr)
{
    int i = 0;
    int j = 0;
    for(i; i < word.size(); i++)
    {
        //cout << "i: " << i << endl;
        //cout << word[i] << " " << abbr[j] << endl;

        if(isupper(word[i]) && word[i] != abbr[j])
        {   
            //cout << "Caps in the middle\n";
            return false;
        }

        if(word[i] == abbr[j])
        {
            //cout << "matched\n";
            j++;
        }
        if(j == abbr.size())
        {
            i++;
            break;
        }
    }
    if(j != abbr.size())
    {
        //cout << "False not all abbr letters found. ";
        return false;
    }
    for(i; i < word.size(); i++)
    {
        //cout << word[i] << " ";
        if(isupper(word[i]))
        {
            // << "False, extra uppers found. ";
            return false;
        }
    }
    return true;
}
void display(Node* curr, string abbr, string currString="")
{
    if(curr->endmark == true)
    {
        cout  << currString << " ";
        checkAbbreviation(currString, abbr) ? 
            cout << "T " :
            cout << "F";
        cout << endl;
    }

    for(int i = 0; i < 26*2; i++)
    {
        if(curr->next[i] != NULL)
        {
            char ch;
            if(i < 26)
                ch = 'a' + i;
            else
                ch = 'A' + i - 26;
            
            display(curr->next[i], abbr, currString + ch);
        }
    }
    //cout << endl;
}

int main()
{
    while(1)
    {
        string str;
        cin >> str;
        cin.ignore();
        if(str == "-1")
            break;

        insert(str);
    }
    
    string abbr;
    cin >> abbr;
    cin.ignore();
    
    display(root, abbr);


    return 0;
}
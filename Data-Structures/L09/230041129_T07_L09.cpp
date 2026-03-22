#include <iostream>
#include <cstring>

using namespace std;

typedef struct node
{
    bool endmark;
    node *next[26];
    node()
    {
        endmark = false;
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
    }
} node;

node* root = new node();

void insert(const char *str, int len)
{
    node *curr = root;
    for (int i = 0; i < len; i++)
    {
        int idx = str[i] - 'a';
        if (curr->next[idx] == NULL)
            curr->next[idx] = new node();
        curr = curr->next[idx];
    }
    curr->endmark = 1;
}

bool search(const char *str, int len)
{
    node *curr = root;
    for (int i = 0; i < len; i++)
    {
        int id = str[i] - 'a';
        if (curr->next[id] == NULL)
            return false;
        curr = curr->next[id];
    }
    return curr->endmark;
}

bool isSegment(string word)
{
    string searchSegment = "";
    for(int i = 0; i < word.size(); i++)
    {
        searchSegment += word[i];
        // cout << "searching for " << searchSegment << endl;
        if(search(searchSegment.c_str(), searchSegment.size()) == true)
        {
            // i += searchSegment.size();
            searchSegment = "";
        }
    }
    return searchSegment == "";
}

int main()
{
    
    
    while(1)
    {
        string product;
        cin >> product;
        cin.ignore();

        if(product == "-1")
            break;

        insert(product.c_str(), product.size());
    }

    string word;
    cin >> word;
    cin.ignore();

    isSegment(word) ? cout << "True\n" : cout << "False\n";


    return 0;
}
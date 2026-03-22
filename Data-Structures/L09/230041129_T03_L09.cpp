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

void display(node* curr, string currString)
{
    if(curr->endmark == true)
    {
        cout << currString << endl;
    }

    for(int i = 0; i < 26; i++)
    {
        if(curr->next[i] != NULL)
        {
            char ch = 'a' + i;
            // cout << ch;
            display(curr->next[i], currString + ch);
        }
    }
}

int main()
{
    int N;
    cin >> N;

    

    for(int i = 0; i < N; i++)
    {
        char word[100];
        cin >> word;
        cin.ignore();
        insert(word, strlen(word));
    }

    display(root, "");

    // search("toy", 3) ? cout << "YES\n" : cout << "NO\n";
    search("toyo", 4) ? cout << "YES\n" : cout << "NO\n";
    search("cat", 3) ? cout << "YES\n" : cout << "NO\n";

    return 0;
}
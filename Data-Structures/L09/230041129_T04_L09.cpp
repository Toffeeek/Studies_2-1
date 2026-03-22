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

int wordCountRoot(node* root)
{
    int count;
    if(root->endmark == true)   count = 1;
    else                        count = 0;

    for (int i = 0; i < 26; i++)
    {
        if(root->next[i] != NULL)
        {
            // cout << "cout: " << count << endl;

            count += wordCountRoot(root->next[i]);
        }
    }
    return count;
}

int wordCountPrefix(const char prefix[])
{
    node *curr = root;
    int len = strlen(prefix);
    for (int i = 0; i < len; i++)
    {
        int id = prefix[i] - 'a';
        if (curr->next[id] == NULL)
            return -1;
        curr = curr->next[id];
    }

    return wordCountRoot(curr);
}



int main()
{
    int N, Q;
    cin >> N >> Q;

    

    for(int i = 0; i < N; i++)
    {
        char word[100];
        cin >> word;
        cin.ignore();

        for(int i = 0; i < strlen(word); i++)
        {
            if(word[i] >= 'A' && word[i] <= 'Z')
            {
                int offset = 'a' - 'A';
                word[i] += offset; 
            }
        }

        insert(word, strlen(word));
    }

    display(root, "");

    for(int i = 0; i < Q; i++)
    {
        char prefix[100];
        cin >> prefix;
        cin.ignore();

        for(int i = 0; i < strlen(prefix); i++)
        {
            if(prefix[i] >= 'A' && prefix[i] <= 'Z')
            {
                int offset = 'a' - 'A';
                prefix[i] += offset; 
            }
        }

        cout << wordCountPrefix(prefix) << endl;
    }

    cout << wordCountRoot(root) << endl;
    cout << wordCountPrefix("abc") << endl;
    

    return 0;
}
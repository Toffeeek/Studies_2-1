#include <iostream>
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
int printCount = 0;

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

void display3(node* curr, string currString, string prefix)
{
    if(printCount == 3)
        return;


    if(curr->endmark == true)
    {
        cout << prefix << currString << " ";
        printCount++;
    }

    for(int i = 0; i < 26; i++)
    {
        if(curr->next[i] != NULL)
        {
            char ch = 'a' + i;
            // cout << ch;
            display3(curr->next[i], currString + ch, prefix);
        }
    }
    //cout << endl;
}

int main()
{
    int N;
    cin >> N;

    while(N--)
    {
        string product;
        cin >> product;
        cin.ignore();
        insert(product.c_str(), product.size());
    }

    string searchWord;
    cin >> searchWord;
    cin.ignore();

    node* curr = root;
    string prefix = "";

    bool wordExists = true;

    for(int i = 0; i < searchWord.size(); i++)
    {
        prefix += searchWord[i];
        int idx = searchWord[i] - 'a';
        cout << prefix << ": "; 

        if(curr->next[idx] != NULL && wordExists)
        {
            curr = curr->next[idx];
    
            display3(curr, "", prefix);
            cout << endl;
    
            printCount = 0;
        }
        else
        {
            wordExists = false;
            cout << "NULL\n";
        }
    }
    

    return 0;
}
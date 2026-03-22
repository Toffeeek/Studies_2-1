#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
using namespace std;


typedef struct Node
{
    bool endmark;
    Node *next[2];
    Node()
    {
        endmark = false;
        for (int i = 0; i < 2; i++)
            next[i] = NULL;
    }
} Node;
Node* root = new Node();
void insert(string str)
{
    Node *curr = root;
    for (int i = 0; i < str.size(); i++)
    {
        int idx = str[i] - '0';
        if (curr->next[idx] == NULL)
            curr->next[idx] = new Node();
        curr = curr->next[idx];
    }
    curr->endmark = 1;
}
void display(Node* curr, string currString="")
{
    if(curr->endmark == true)
    {
        cout  << currString << endl;
    }

    for(int i = 0; i < 2; i++)
    {
        if(curr->next[i] != NULL)
        {
            char ch = '0' + i;
            // cout << ch;
            display(curr->next[i], currString + ch);
        }
    }
    //cout << endl;
}

string int2bin(int n)
{
    string bits = "";
    
    if(n == 0)
        return "0";
    
    for(int i = 0; n > 0; n /= 2)
    {
        int bit;
        bit = n % 2;
        bits = to_string(bit) + bits; 
    }
    return bits;
}

int getMaxXOR()
{
    string branch1 = "";
    string branch2 = "";
    
    Node* curr1 = root;
    Node* curr2 = root;

    if(curr1->next[0] != NULL && curr2->next[1])
    {

    }


}

int main()
{   
    int N;
    cin >> N;
    vector<int> nums;

    for(int i = 0; i < N; i++)
    {
        int n;
        cin >> n;
        nums.push_back(n);
    }

    for(int i = 0; i < N; i++)
    {
        string bits = int2bin(nums[i]);
        insert(bits);
    }

    display(root);

    // for(int i = 0; i < N; i++)
    // {
    //     cout << nums[i].first << ": " << int2bin(nums[i]) << endl;;
    // }

    // string str;
    // cin > str;

    return 0;
}
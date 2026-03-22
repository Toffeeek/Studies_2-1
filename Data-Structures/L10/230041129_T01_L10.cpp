#include <iostream>
using namespace std;

void repArr_init(int repArr[], int N)
{
    for(int i = 0; i < N; i++)
    {
        repArr[i] = i;
    }
}

int find(int repArr[], int item)
{
    if(repArr[item] == item)
    {
        return item;
    }
    else
        return find(repArr, repArr[item]);
}
void _union(int repArr[], int u, int v)
{
    int u_rep = find(repArr, u);
    int v_rep = find(repArr, v);
    cout << "rep(" << u << ") = " << u_rep << endl;
    cout << "rep(" << v << ") = " << v_rep << endl;

    if(u_rep != v_rep)
    {
        repArr[v_rep] = u_rep;
    }
    else
    {
        return;
    }

}

int main()
{
    int N;
    cin >> N;
    int repArr[N];

    while(1)
    {
        int choice;
        cout << "Choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1: repArr_init(repArr, N);
                    break;

            case 2: int item;
                    cin >> item;
                    cout << find(repArr, item) << endl;
                    break;

            case 3: int u, v;
                    cin >> u >> v;
                    _union(repArr, u, v);
                    break;

            default:break;
        }
        cout << "Representative array: ";
        for(int i : repArr)
        {
            cout << i << " ";
        }
        cout << endl;
    }


    return 0;
}
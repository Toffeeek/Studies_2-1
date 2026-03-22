#include <iostream>
using namespace std;

void repArr_init(pair<int, int> repArr[], int N)
{
    for(int i = 0; i < N; i++)
    {
        repArr[i].first = i;
        repArr[i].second = 0;
    }
}

auto find(pair<int, int> repArr[], int item)
{
    cout << "find(" << item << ") ";
    if(repArr[item].first == item)
    {
        cout << endl;
        return repArr[item];
    }
    else
    {
        auto setRep = find(repArr, repArr[item].first);
        repArr[item].first = setRep.first;
        return setRep;
    }
}
void _union(pair<int, int> repArr[], int u, int v)
{
    auto u_rep = find(repArr, u);
    auto v_rep = find(repArr, v);
    cout << "rep(" << u << ") = " << u_rep.first << endl;
    cout << "rep(" << v << ") = " << v_rep.first << endl;

    if(u_rep.first == v_rep.first)
        return;

    // self implementation
    // if(v_rep.second <= u_rep.second)
    // {
    //     cout << "equal ranks\n";
    //     repArr[v_rep.first].first = u_rep.first;
    //     if(v_rep.second == u_rep.second)
    //         repArr[u_rep.first].second++;
    // }
    // else
    // {
    //     cout << "unequal ranks\n";cout << "equal ranks\n";
    //     repArr[u_rep.first].first = v_rep.first;
    // }


    // slide implementation
    if(u_rep.second <= v_rep.second)
    {
        cout << "equal ranks\n";
        repArr[u_rep.first].first = v_rep.first;
        if(u_rep.second == v_rep.second)
            repArr[v_rep.first].second++;
    }
    else
    {
        cout << "unequal ranks\n";
        repArr[v_rep.first].first = u_rep.first;
    }

}

int main()
{
    int N;
    cin >> N;
    pair<int, int> repArr[N];

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
                    cout << find(repArr, item).first << endl;
                    continue;

            case 3: int u, v;
                    cin >> u >> v;
                    _union(repArr, u, v);
                    break;

            default:break;
        }
        cout << "Representative array: ";
        for(auto i : repArr)
        {
            cout << i.first << "(" << i.second << ") ";
        }
        cout << endl;
    }


    return 0;
}
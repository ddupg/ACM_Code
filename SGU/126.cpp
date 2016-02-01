#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <set>
#include <queue>
using namespace std;
set<int> s;
queue<int> q;

int main()
{
    long long x, y;
    cin>>x>>y;
    if(x>y)swap(x, y);
    if(x==0)
    {
        cout<<0<<endl;
        return 0;
    }
    int ans=0;
    while(true)
    {
        y-=x, x*=2;
        ans++;
        if(y==0)
        {
            cout<<ans<<endl;
            return 0;
        }
        if(y<x)break;
    }
    cout<<-1<<endl;
    return 0;
}

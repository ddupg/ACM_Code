#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <list>
using namespace std;
typedef long long LL;

int n;
list<int> lst;

bool judge()
{
    list<int>::iterator it=lst.begin();
    for(int i=1; i<=n; i++, it++)
        if(*it!=i)
            return false;
    return n==lst.size();
}

void solve()
{
    list<int>::iterator i, j;
    int cnt=0;
    while(!judge())
    {
        j=i=lst.begin();
        j++;
        int t=*i, tt=*j;
        if((t==n && tt==1) || t<tt)
        {
            lst.pop_front();
            lst.push_back(t);
            printf("2");
            if(++cnt>2*n*n)
                while(1);
        }
        else
        {
            lst.erase(j);
            lst.push_front(tt);
            printf("1");
            if(++cnt>2*n*n)
                while(1);
        }
    }
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        lst.clear();
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            lst.push_back(x);
        }
        solve();
        puts("");
    }
    return 0;
}

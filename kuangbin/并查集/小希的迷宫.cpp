#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
const int maxn=110000;

int p[maxn];
set<int> setv;

void init()
{
    for(int i=0; i<maxn; i++)
        p[i]=i;
    setv.clear();
}

int find(int x)
{
    return p[x]==x?x:p[x]=find(p[x]);
}

bool add(int u, int v)
{
    setv.insert(u);
    setv.insert(v);
    u=find(u), v=find(v);
    if(u==v)return false;
    p[u]=v;
    return true;
}

bool judge()
{
    set<int>::iterator it=setv.begin();
    int fa=find(*it);
    for(it++; it!=setv.end(); it++)
        if(fa!=find(*it))
            return false;
    return true;
}

int main()
{
    int u, v;
    while(~scanf("%d%d", &u, &v) && ~u)
    {
        if(!u && !v)
        {
            puts("Yes");
            continue ;
        }
        init();
        int ok=1;
        if(!add(u, v))
            ok=0;
        while(~scanf("%d%d", &u, &v) && u)
            if(!add(u, v))
                ok=0;

        if(!ok || !judge())
            puts("No");
        else puts("Yes");
    }
    return 0;
}

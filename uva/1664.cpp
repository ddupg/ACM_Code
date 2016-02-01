#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int maxn=300000+100;

inline int scan()
{
    int x=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0', c=getchar();
    return x;
}

struct Edge
{
    int u, v, c;
    bool operator < (const Edge& a)const
    {
        return c>a.c;
    }
} E[maxn];

int n, sz[maxn], f[maxn];
LL mx[maxn];

void init()
{
    for(int i=1; i<=n; i++)
        f[i]=i, sz[i]=1, mx[i]=0;
}

int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        for(int i=0; i<n-1; i++)
            E[i].u=scan(), E[i].v=scan(), E[i].c=scan();
        sort(E, E+n-1);
        for(int i=0; i<n-1; i++)
        {
            int u=find(E[i].u), v=find(E[i].v);
            mx[u]=max(1LL*E[i].c*sz[u]+mx[v], 1LL*E[i].c*sz[v]+mx[u]);
            sz[u]+=sz[v];
            f[v]=u;
        }
        printf("%lld\n", mx[find(1)]);
    }
    return 0;
}

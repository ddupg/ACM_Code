#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <functional>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define mp make_pair
using namespace std;
typedef long long LL;
typedef pair<LL, int> pli;

const int maxn=200000+100;
const LL oo=0x3f3f3f3f3f3f3f3f;

int n, fa[maxn], l[maxn], r[maxn], c[maxn];
LL d[maxn];

priority_queue<pli, vector<pli>, greater<pli> >q;

void init()
{
    for(int i=0; i<maxn; i++)
        fa[i]=i;
    clr(d, 0x3f);
}

int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        for(int i=1; i<=n; i++) scanf("%d", l+i);
        for(int i=1; i<=n; i++) scanf("%d", r+i);
        for(int i=1; i<=n; i++) scanf("%d", c+i);

        d[1]=c[1];
        q.push(mp(d[1], 1));
        while(!q.empty())
        {
            int u=q.top().snd;
            q.pop();
            for(int i=-1; i<=1; i+=2)
            {
                int L=l[u]*i+u;
                int R=r[u]*i+u;
                if(L>R)swap(L, R);
                L=max(L, 1);
                L=min(L, n+1);
                for(int v=L; ; v++)
                {
                    v=find(v);
                    if(v>n || v>R)break;
                    if(d[v]>d[u]+c[v])
                    {
                        d[v]=d[u]+c[v];
                        q.push(mp(d[v], v));
                    }
                    fa[find(v)]=find(v+1);
                }
            }
        }
        for(int i=1; i<=n; i++)
            printf("%I64d%c", d[i]==oo?-1:d[i]-c[i], " \n"[i==n]);
    }
    return 0;
}

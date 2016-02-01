#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define rep1(i,x,y) for(int i=x;i<=(int)y;i++)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=100000+100;

int n, m, fa[maxn], dis[maxn];
bool vis[maxn];
pii e[maxn];
vector<int> G[maxn];

void relax(int u)
{
    for(int i=0; i<G[u].size(); i++)
    {
        int v=e[G[u][i]].snd;
        if(fa[v])continue ;
        fa[v]=u;
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++)
            G[i].clear();
        clr(fa, 0);
        clr(dis, 0);
        clr(vis, 0);
        for(int i=0; i<m; i++)
        {
            scanf("%d%d", &e[i].fst, &e[i].snd);
            G[e[i].fst].pb(i);
        }
        relax(1);
        fa[1]=-1;
        dis[1]=0;
        vis[1]=1;
        int pre=2, last=n, now=1;
        while(pre<=last)
        {
            if(fa[pre] && !vis[pre])
            {
                dis[pre]=now++;
                vis[pre]=true;
                relax(pre++);
            }
            if(fa[last] && !vis[last])
            {
                dis[last]=now++;
                vis[last]=true;
                relax(last--);
            }
        }
        for(int i=0; i<m; i++)
        {
            int u=e[i].fst, v=e[i].snd;
            if(fa[v]==u)
                printf("%d\n", dis[v]-dis[u]);
            else printf("%d\n", n);
        }
    }
    return 0;
}

#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <queue>
#include <deque>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

const int maxn=1000000+10;
const int oo=0x3f3f3f3f;

struct SPFA
{
    struct Edge
    {
        int v, w, nxt;
    } E[maxn<<1];
    int d[maxn], vis[maxn], cnt[maxn], H[maxn], tot;
    deque<int> q;
    void init()
    {
        clr(d, 0x3f);
        clr(vis, 0);
        clr(cnt, 0);
        clr(H, 0xff);
    }
    void add(int u, int v, int w)
    {
        E[tot].v=v, E[tot].w=w;
        E[tot].nxt=H[u];
        H[u]=tot++;
    }
    void spfa(int s)
    {
        d[s]=0;
        vis[s]=cnt[s]=1;
        q.push_back(1);
        while(!q.empty())
        {
            int u=q.front();
            q.pop_front();
            vis[u]=0;
            for(int i=H[u]; ~i; i=E[i].nxt)
            {
                int v=E[i].v, w=E[i].w;
                if(d[v]>d[u]+w)
                {
                    d[v]=d[u]+w;
                    if(!vis[v])
                    {
                        vis[v]=true;
                        ++cnt[v];
//                        if(cnt[v]>=n)return -1;
                        if(!q.empty())
                        {
                            if(d[v]>d[q.front()])
                                q.push_back(v);
                            else q.push_front(v);
                        }
                        else q.push_back(v);
                    }
                }
            }
        }
    }
} s[2];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        s[0].init(), s[1].init();
        while(m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            s[0].add(u, v, w);
            s[1].add(v, u, w);
        }
        s[0].spfa(1);
        s[1].spfa(1);
        int ans=0;
        for(int i=1; i<=n; i++)
            ans+=s[0].d[i]+s[1].d[i];
        printf("%d\n", ans);
    }
    return 0;
}

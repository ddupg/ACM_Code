#include <bits/stdc++.h>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define fst first
#define snd second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;

const int maxn=100000+100;
const int oo=0x3f3f3f3f;

int n, m, preu[maxn], prew[maxn];
vector<pii> G[maxn];
vector<int> ansv, answ;
int q[maxn], dis[maxn];

vector<int> vec[2];
int pre=0, cur=1;
bool was[maxn], vis[maxn];

void solve()
{
    clr(preu, 0xff);
    clr(dis, 0xff);
    int head=0, tail=0;
    dis[0]=0;
    q[tail++]=0;
    while(head<tail)
    {
        int u=q[head++];
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i].fst, w=G[u][i].snd;
            if(~dis[v])continue ;
            dis[v]=dis[u]+1;
            q[tail++]=v;
        }
    }

    clr(was, 0);
    clr(vis, 0);
    head=tail=0;
    q[tail++]=n-1;
    was[n-1]=true;
    vis[n-1]=true;
    while(head<tail)
    {
        int u=q[head++];
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i].fst, w=G[u][i].snd;
            if(!vis[v] && w==0)
            {
                vis[v]=was[v]=true;
                preu[v]=u, prew[v]=0;
                q[tail++]=v;
            }
        }
    }

    int ddd=dis[n-1];
    for(int i=0; i<n; i++)
        if(was[i])
            ddd=min(ddd, dis[i]);
    for(int i=0; i<n; i++)
        if(was[i] && dis[i]==ddd)
            vec[pre].pb(i);

    for(; ddd>0; ddd--)
    {
        int best=oo;
        for(int i=0; i<vec[pre].size(); i++)
        {
            int u=vec[pre][i];
            for(int j=0; j<G[u].size(); j++)
            {
                int v=G[u][j].fst, w=G[u][j].snd;
                if(dis[v]==dis[u]-1)
                    best=min(best, w);
            }
        }

        vec[cur].clear();
        for(int i=0; i<vec[pre].size(); i++)
        {
            int u=vec[pre][i];
            for(int j=0; j<G[u].size(); j++)
            {
                int v=G[u][j].fst, w=G[u][j].snd;
                if(dis[v]==dis[u]-1 && best==w)
                {
                    vec[cur].pb(v);
                    preu[v]=u;
                    prew[v]=w;
                }
            }
        }
        swap(pre, cur);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<n; i++)
        G[i].clear();
    for(int i=0; i<m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].pb(pii(v, w));
        G[v].pb(pii(u, w));
    }
    solve();
    for(int u=0; ~u; u=preu[u])
    {
        ansv.pb(u);
        if(~preu[u])answ.pb(prew[u]);
    }
    int p=0;
    for(int i=answ.size()-1; i>0; i--)
        if(answ[i])
        {
            p=i;
            break;
        }
    for(int i=p; i>=0; i--)
        printf("%d", answ[i]);
    puts("");
    printf("%d\n", ansv.size());
    for(int i=0; i<ansv.size(); i++)
        printf("%d%c", ansv[i], " \n"[i==ansv.size()-1]);
    return 0;
}

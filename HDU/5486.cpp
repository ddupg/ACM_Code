#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fst first
#define snd second
using namespace std;
typedef pair<int, int> pii;

const int maxn=3000000+100;

struct Edge
{
    int v, nxt;
} E[maxn];

pii p[maxn];
int n, nx, ny, tot, H[maxn], x[maxn], y[maxn];
int cx, cy, sz[maxn];
bool vis[maxn];
int q[maxn];

void init()
{
    for(int i=0; i<(n<<1); i++)
        H[i]=-1, vis[i]=false, sz[i]=0;
    tot=0;
}

void AddEdge(int u, int v)
{
    ++sz[u];
    E[tot].v=v, E[tot].nxt=H[u];
    H[u]=tot++;
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        for(int i=0; i<n; i++)
            scanf("%d%d", &p[i].fst, &p[i].snd), x[i]=p[i].fst, y[i]=p[i].snd;
        sort(x, x+n);
        nx=unique(x, x+n)-x;
        sort(y, y+n);
        ny=unique(y, y+n)-y;
        sort(p, p+n);
        n=unique(p, p+n)-p;
        for(int i=0; i<n; i++)
        {
            int u=lower_bound(x, x+nx, p[i].fst)-x;
            int v=lower_bound(y, y+ny, p[i].snd)-y+nx;
            AddEdge(u, v);
            AddEdge(v, u);
        }
        int A=0, B=0, C=0;
        for(int i=0; i<nx; i++)
        {
            if(vis[i])continue ;
            cx=cy=0;
            int head=0, tail=0;
            q[tail++]=i;
            while(head!=tail)
            {
                int u=q[head++];
                if(u<nx)++cx;
                else ++cy;
                vis[u]=true;
                for(int i=H[u]; ~i; i=E[i].nxt)
                {
                    int v=E[i].v;
                    if(vis[v])continue ;
                    q[tail++]=v;
                }
            }

            if(cx>1 && cy>1)continue ;
            if(cx==cy && cx==1)C++;
            else if(cx==1)A++;
            else B++;
        }
        printf("Case #%d: %d %d %d\n", ++kase, A, B, C);
    }
    return 0;
}

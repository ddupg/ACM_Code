#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=1100;

struct Node
{
    int val, x, y;
    bool operator < (const Node a)const
    {
        return val>a.val;
    }
    Node(int v=0, int x=0, int y=0):val(v), x(x), y(y) {}
} nd[maxn*maxn];

struct Query
{
    int h, id;
    bool operator < (const Query a)const
    {
        return h>a.h;
    }
    Query(int h=0, int id=0):h(h), id(id) {}
} q[100010];

bool vis[maxn][maxn];
int n, m, ans[100010], pre[maxn*maxn];
const int dx[]= {0, 0, -1, 1};
const int dy[]= {1, -1, 0, 0};

int find(int x)
{
    if(pre[x]==-1)return x;
    return pre[x]=find(pre[x]);
}

bool inside(int x, int y)
{
    return x && y && x<=n && y<=m;
}

int judge(int x, int y)
{
    int v[5], cnt=0;
    for(int i=0; i<4; i++)
    {
        int nx=x+dx[i], ny=y+dy[i];
        if(inside(nx, ny) && vis[nx][ny])
        {
            v[cnt++]=find(m*(nx-1)+ny);
        }
    }
    sort(v, v+cnt);
    cnt=unique(v, v+cnt)-v;
    for(int i=0; i<cnt; i++)
        pre[v[i]]=m*(x-1)+y;
    return 1-cnt;
}

int main()
{
    int T, t;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        int tot=0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            {
                int v;
                scanf("%d", &v);
                nd[tot]=Node(v, i, j);
                tot++;
            }
        scanf("%d", &t);
        for(int i=0; i<t; i++)
        {
            int v;
            scanf("%d", &v);
            q[i]=Query(v, i);
        }
        sort(nd, nd+tot);
        sort(q, q+t);
        memset(vis, 0, sizeof vis);
        memset(pre, -1, sizeof pre);
        int cnt=0;
        for(int i=0, j=0; i<t; i++)
        {
            for(; nd[j].val>q[i].h && j<tot; j++)
            {
                cnt+=judge(nd[j].x, nd[j].y);
                vis[nd[j].x][nd[j].y]=1;
            }
            ans[q[i].id]=cnt;
        }
        for(int i=0; i<t; i++)
            printf("%d ", ans[i]);
        puts("");
    }
    return 0;
}

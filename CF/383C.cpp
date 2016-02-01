#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define lson l, mid, rt<<1
#define rson mid+1, r, rt<<1|1
const int maxn=400000;

vector<int> G[maxn];
int tot;
struct Node
{
    int l, r, type, val;
} nd[maxn];

struct SegmentTree
{
    int add[maxn<<2];
    void init()
    {
        memset(add, 0, sizeof add);
    }
    void pushdown(int rt)
    {
        if(!add[rt])return ;
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        add[rt]=0;
    }
    void update(int L, int R, int val, int l, int r, int rt)
    {
        if(L<=l && R>=r)
        {
            add[rt]+=val;
            return ;
        }
        int mid=(l+r)>>1;
        if(L<=mid)update(L, R, val, lson);
        if(R>mid)update(L, R, val, rson);
    }
    int query(int x, int l, int r, int rt)
    {
        if(l==r)return add[rt];
        int mid=(l+r)>>1;
        pushdown(rt);
        if(x<=mid)return query(x, lson);
        else return query(x, rson);
    }
} st[2];

void dfs(int u, int fa, int type)
{
    nd[u].type=type;
    nd[u].l=++tot;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==fa)continue ;
        dfs(v, u, type^1);
    }
    nd[u].r=++tot;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n; i++)
        scanf("%d", &nd[i].val);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1, 0);
    st[0].init();
    st[1].init();
    while(m--)
    {
        int op, x, val;
        scanf("%d", &op);
        if(op==1)
        {
            scanf("%d%d", &x, &val);
            st[nd[x].type].update(nd[x].l, nd[x].r, val, 1, tot, 1);
            st[nd[x].type^1].update(nd[x].l, nd[x].r, -val, 1, tot, 1);
        }
        else
        {
            scanf("%d", &x);
            printf("%d\n", nd[x].val+st[nd[x].type].query(nd[x].l, 1, tot, 1));
        }
    }
    return 0;
}

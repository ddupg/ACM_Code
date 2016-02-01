#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
#define pb push_back
using namespace std;
typedef long long LL;

const double PI=acos(-1.0);
const int maxn=50050;

int n, rt, sz[maxn], num[maxn], tot_sz, dep[maxn], fa[maxn];
vector<int> G[maxn];
LL ans[maxn];
bool vis[maxn], pri[maxn];
int Q[maxn];

struct Com
{
    double a,b;
    Com(double aa=0,double bb=0) { a=aa; b=bb; }
    Com operator +(const Com &e) { return Com(a+e.a,b+e.b); }
    Com operator -(const Com &e) { return Com(a-e.a,b-e.b); }
    Com operator *(const Com &e) { return Com(a*e.a-b*e.b,a*e.b+b*e.a); }
} cd[maxn*4];
void change(Com y[],int n)
{
    for(int i = 0, j = 0; i < n; i++)
    {
        if(j > i) swap(y[i], y[j]);
        int k = n;
        while(j & (k >>= 1)) j &= ~k;
        j |= k;
    }
}
void FFT(Com y[],int len,int on)
{
    change(y, len);
    for(int h=2; h<=len; h<<=1)
    {
        Com wn(cos(-on*2*PI/h), sin(-on*2*PI/h));
        for(int j=0; j<len; j+=h)
        {
            Com w(1, 0);
            for(int k=j; k<j+h/2; k++)
            {
                Com u=y[k];
                Com t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
        for(int i=0; i<len; i++)
            y[i].a/=len;
}

void init()
{
    for(int i=2; i<maxn; i++)
        pri[i]=1;
    for(int i=2; i*i<maxn; i++)
        if(pri[i])
            for(int j=i*i; j<maxn; j+=i)
                pri[j]=0;
}

void getroot(int u, int f)
{
    sz[u]=1, num[u]=0;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(vis[v] || f==v)continue ;
        getroot(v, u);
        num[u]=max(num[u], sz[v]);
        sz[u]+=sz[v];
    }
    num[u]=max(num[u], tot_sz-sz[u]);
    if(rt==-1 || num[u]<num[rt])
        rt=u;
}

void cal(int u, int len, int flag)
{
    int head=0, tail=0, mx=0;
    dep[u]=len, fa[u]=-1;
    Q[tail++]=u;
    while(head<tail)
    {
        int x=Q[head++];
        mx=max(dep[x], mx);
        for(int i=0; i<G[x].size(); i++)
        {
            int y=G[x][i];
            if(vis[y] || y==fa[x])continue ;
            dep[y]=dep[x]+1;
            fa[y]=x;
            Q[tail++]=y;
        }
    }
    sz[u]=head;
    int n=1;
    while(mx*2>=n)n<<=1;
    for(int i=0; i<n; i++) cd[i]=Com(0, 0);
    for(int i=0; i<head; i++) cd[dep[Q[i]]].a++;
    FFT(cd, n, 1);
    for(int i=0; i<n; i++) cd[i]=cd[i]*cd[i];
    FFT(cd, n, -1);
    for(int i=2; i<n; i++)if(pri[i])
        ans[i]+=flag*((LL)(cd[i].a+0.5));
}

void dfs(int u)
{
    vis[u]=true;
    cal(u, 0, 1);
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(vis[v])continue ;
        cal(v, 1, -1);
        tot_sz=sz[v];
        rt=-1;
        getroot(v, -1);
        dfs(rt);
    }
}

int main()
{
    init();
    scanf("%d", &n);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].pb(v);
        G[v].pb(u);
    }
    rt=-1;
    tot_sz=n;
    getroot(1, -1);
    dfs(rt);
    LL tot=0;
    for(int i=2; i<=n; i++)if(pri[i])
            tot+=ans[i];
    printf("%.10f\n", 1.0*tot/n/(n-1));
    return 0;
}


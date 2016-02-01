#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
using namespace std;
typedef long long LL;
#define clr(a, x) memset(a, x, sizeof a)

const int maxn=100000+100;
const int oo=0x3f3f3f3f;

map<string, int> mp;
int tot=0;
int init_cnt[maxn], init_len[maxn], cnt[maxn], len[maxn];
int a[maxn];
bool vis[maxn];
string s;
vector<int> G[maxn];

void tolower(string& s)
{
    for(int i=0; i<s.length(); i++)
        if(s[i]>='A' && s[i]<='Z')
            s[i]=s[i]-'A'+'a';
}

int getr(string s)
{
    int ans=0;
    for(int i=0; i<s.length(); i++)
        if(s[i]=='r' || s[i]=='R')
            ans++;
    return ans;
}

int getid(string str)
{
    if(mp.count(str))return mp[str];
    mp[str]=++tot;
    init_cnt[tot]=getr(str);
    init_len[tot]=str.length();
    return tot;
}

struct Edge
{
    int v, nxt;
};

struct Tarjan
{
    int pre[maxn], low[maxn], dfn, scc, bel[maxn];
    int head[maxn], tot;
    Edge edge[maxn<<1];
    bool ins[maxn];
    stack<int> S;
    void init()
    {
        clr(head, -1);
        clr(pre, 0);
        clr(ins, 0);
        clr(bel, 0);
        tot=dfn=scc=0;
    }
    void AddEdge(int u, int v)
    {
        edge[tot].v=v;
        edge[tot].nxt=head[u];
        head[u]=tot++;
    }
    void tarjan(int u)
    {
        pre[u]=low[u]=++dfn;
        S.push(u);
        ins[u]=1;
        for(int i=head[u]; ~i; i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(!pre[v])
            {
                tarjan(v);
                low[u]=min(low[u], low[v]);
            }
            else if(ins[v])
                low[u]=min(low[u], pre[v]);
        }
        if(low[u]==pre[u])
        {
            ++scc;
            while(true)
            {
                int v=S.top();
                S.pop();
                ins[v]=false;
                bel[v]=scc;
                if(cnt[scc]>init_cnt[v])
                    cnt[scc]=init_cnt[v], len[scc]=init_len[v];
                else if(cnt[scc]==init_cnt[v])
                    len[scc]=min(len[scc], init_len[v]);
                if(v==u)break;
            }
        }
    }
    void solve(int n)
    {
        clr(cnt, 0x3f);
        for(int i=1; i<=n; i++)
            if(!pre[i])
                tarjan(i);
    }
} SCC;

void dfs(int u)
{
    vis[u]=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(!vis[v]) dfs(v);
        if(cnt[v]<cnt[u])
            cnt[u]=cnt[v], len[u]=len[v];
        else if(cnt[u]==cnt[v])
            len[u]=min(len[u], len[v]);
    }
}

int main()
{
    int n, m;
    SCC.init();
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>s;
        tolower(s);
        a[i]=getid(s);
    }
    cin>>m;
    while(m--)
    {
        string u, v;
        cin>>u>>v;
        tolower(u), tolower(v);
        SCC.AddEdge(getid(u), getid(v));
    }
    SCC.solve(tot);
    for(int u=1; u<=tot; u++)
        for(int i=SCC.head[u]; ~i; i=SCC.edge[i].nxt)
        {
            int v=SCC.edge[i].v;
            if(SCC.bel[v]!=SCC.bel[u])
                G[SCC.bel[u]].push_back(SCC.bel[v]);
        }
    for(int i=1; i<=SCC.scc; i++)
        if(!vis[i])
            dfs(i);
    LL ans1=0, ans2=0;
    for(int i=0; i<n; i++)
        ans1+=cnt[SCC.bel[a[i]]], ans2+=len[SCC.bel[a[i]]];
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}

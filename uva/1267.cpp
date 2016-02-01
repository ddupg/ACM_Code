#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn=1100;

int n, s, k;
vector<int> mp[maxn];

struct Node
{
    int u, deep, pre;
    bool isleaf, ok;
    bool operator < (const Node a)const
    {
        return deep<a.deep;
    }
} node[maxn];

priority_queue<Node> q;

void init()
{
    for(int i=0; i<=n; i++)
        mp[i].clear();
}

void build(int u, int pre, int d)
{
    node[u]=Node{u, d, pre, mp[u].size()==1, 1};
    for(int i=0; i<mp[u].size(); i++)
        if(mp[u][i]!=pre)
            build(mp[u][i], u, d+1);
    if(node[u].isleaf)
        q.push(node[u]);
}

void deleteV(int u, int step, int pre)
{
    if(step<0)return ;
    if(node[u].isleaf)
        node[u].ok=false;
    for(int i=0; i<mp[u].size(); i++)if(pre!=mp[u][i])
        deleteV(mp[u][i], step-1, u);
}

int findfather(int u, int step)
{
    if(step==0)
        return u;
    return findfather(node[u].pre, step-1);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &s, &k);
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            mp[u].push_back(v);
            mp[v].push_back(u);
        }
        build(s, -1, 1);
        deleteV(s, k, -1);

        int ans=0;
        while(!q.empty())
        {
            Node x=q.top();
            q.pop();
            if(!node[x.u].ok) continue ;
            int root=findfather(x.u, k);
            deleteV(root, k, -1);
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
struct Node
{
    int u, v, len;
    Node(int u, int v, int l):u(u), v(v), len(l){}
};
int n, k;
queue<Node> q;
vector<int> g[110000];
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &k);
        for(int i=0; i<=n; i++)g[i].clear();
        while(!q.empty())q.pop();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            q.push(Node(u, v, 1));
            q.push(Node(v, u, 1));
            g[u].push_back(v);
            g[v].push_back(u);
        }
        LL ans=0;
        int cnt=0;
        for(int i=0; i<2*k && !q.empty(); i++)
        {
            Node x=q.front();
            q.pop();
            ans+=x.len;
            for(int j=0; j<g[x.u].size() && cnt<=2*k+10; j++)
                if(g[x.u][j]!=x.v)
                {
                    q.push(Node(g[x.u][j], x.u, x.len+1));
                    ++cnt;
                }
        }
        printf("%I64d\n", ans>>1);
    }
    return 0;
}

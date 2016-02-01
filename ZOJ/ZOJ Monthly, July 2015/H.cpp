#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
#define fst first
#define snd second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=50000+100;

vector<int> G[maxn];
int sum[maxn<<2], ans[maxn];
bool cov[maxn<<2];
priority_queue<pii> Q;

void init()
{
    for(int i=0; i<maxn; i++)
        G[i].clear();
    clr(ans, 0);
}

int main()
{
    int n, m, q;
    while(~scanf("%d%d%d", &n, &m, &q))
    {
        init();
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
        }
        for(int i=0; i<q; i++)
        {
            int x;
            scanf("%d",&x);
            Q.push(pii(x, i));
        }
        int y=n;
        int Min[2];
        Min[0]=Min[1]=-1;
        while(!Q.empty())
        {
            pii x=Q.top();
            Q.pop();
            for(; y>=x.fst; y--)
            {
                for(int i=0; i<G[y].size(); i++)
                {
                    int v=G[y][i];
                    if(Min[0]==-1 || Min[0]>v)
                    {
                        Min[1]=Min[0];
                        Min[0]=v;
                    }
                    else if(Min[0]==v)
                        Min[1]=v;
                    else if(Min[1]==-1 || Min[1]>v)
                        Min[1]=v;
                }
            }
            if(Min[1]>-1 && Min[1]<x.fst)
                ans[x.snd]+=x.fst-Min[1];
        }
        for(int i=0; i<q; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}

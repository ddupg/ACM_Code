#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <list>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define pb push_back
using namespace std;
typedef long long LL;

const int maxn=500000+100;

vector<int> w[maxn][26], G[maxn];
int n, m, L[maxn], R[maxn], idx=0;
char str[maxn];

void dfs(int u, int d)
{
    L[u]=++idx;
    w[d][str[u]-'a'].pb(idx);
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        dfs(v, d+1);
    }
    R[u]=idx;
}

int main()
{
    while(scanf("%d%d", &n, &m)==2)
    {
        for(int i=2; i<=n; i++)
        {
            int x;
            scanf("%d", &x);
            G[x].pb(i);
        }
        scanf("%s", str+1);
        dfs(1, 1);
        while(m--)
        {
            int u, h;
            scanf("%d%d", &u, &h);
            int odd=0;
            for(int i=0; i<26; i++)
            {
                int cnt=upper_bound(ALL(w[h][i]), R[u])-lower_bound(ALL(w[h][i]), L[u]);
                odd+=(cnt&1);
            }
            if(odd<=1)puts("Yes");
            else puts("No");
        }
    }
    return 0;
}

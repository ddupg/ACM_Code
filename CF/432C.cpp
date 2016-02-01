#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define rep1(i,x,y) for(int i=x;i<=(int)y;i++)
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=100000+100;

vector<int> pri;
bool vis[maxn];

void init()
{
    for(int i=2; i*i<maxn; i++)if(!vis[i])
        for(int j=i*i; j<maxn; j+=i)
            vis[j]=true;
    for(int i=2; i<maxn; i++)
        if(!vis[i])
            pri.pb(i);
}

int n, a[maxn], p[maxn];
vector<pii> ans;

int main()
{
    init();
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d", a+i);
        p[a[i]]=i;
    }
    for(int i=1; i<=n; i++)
    {
        if(p[i]==i)continue ;
        while(p[i]-i)
        {
            int k=pri[upper_bound(ALL(pri), p[i]-i+1)-pri.begin()-1];
            int x=p[i]-k+1, y=p[i];
            ans.pb(pii(x, y));
            swap(p[a[x]], p[a[y]]);
            swap(a[x], a[y]);
        }
    }
    printf("%d\n", ans.size());
    for(int i=0; i<ans.size(); i++)
        printf("%d %d\n", ans[i].fst, ans[i].snd);
    return 0;
}

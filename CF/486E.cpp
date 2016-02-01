#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define pb push_back
using namespace std;

const int maxn=100000+100;
int n, a[maxn], d[maxn], g[maxn], mx;
int ans[maxn], cnt[maxn];

vector<int> v[maxn];

void dp()
{
    clr(g, 0x3f);
    for(int i=0; i<n; i++)
    {
        int k=lower_bound(g+1, g+1+n, a[i])-g;
        d[i]=k;
        g[k]=a[i];
        mx=max(mx, d[i]);
    }
}

void solve()
{
    for(int i=n-1; i>=0; i--)
    {
        int t=v[d[i]+1].end()-upper_bound(ALL(v[d[i]+1]), a[i]);
        if(t==0 && d[i]!=mx)
            ans[i]=1;
        else
        {
            v[d[i]].pb(a[i]);
            ++cnt[d[i]];
        }
    }
    for(int i=0; i<n; i++)if(ans[i]==0)
        {
            if(cnt[d[i]]==1)
                ans[i]=3;
            else ans[i]=2;
        }
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", a+i);
    dp();
    solve();
    for(int i=0; i<n; i++)
        printf("%d", ans[i]);
    puts("");
    return 0;
}

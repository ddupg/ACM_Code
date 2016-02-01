#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define fst first
#define snd second
#define ALL(a) a.begin(), a.end()
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

int n;
vector<pii> v;

LL dfs(int L, int R, int dir)
{
    if(dir==0 && L<0)return 0;
    if(dir==1 && R>=n)return 0;
    LL ans=0;
    if(dir==0) ans=dfs(L-1, R, 1)+v[L].snd;
    else ans=dfs(L, R+1, 0)+v[R].snd;
    return ans;
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        v.push_back(pii(a, b));
    }
    sort(ALL(v));
    int p=lower_bound(ALL(v), pii(0, 0))-v.begin();
    int L=p-1, R=p;
    LL ans=0;
    if(v[p].fst==0)
    {
        R++;
        ans+=v[p].snd;
    }
    dfs(L, R, 0);
    ans+=max(dfs(L, R, 0), dfs(L, R, 1));
    cout<<ans<<endl;
    return 0;
}

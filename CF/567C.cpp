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
#include<cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define rep1(i,x,y) for(int i=x;i<=(int)y;i++)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=200000+100;

int n, k, a[maxn], b[maxn];
vector<int> p[maxn];
set<int> s;

int main()
{
    scanf("%d%d", &n, &k);
    for(int i=0; i<n; i++)
    {
        scanf("%d", a+i);
        b[i]=a[i];
        s.insert(a[i]);
    }
    sort(b, b+n);
    int cnt=unique(b, b+n)-b;
    for(int i=0; i<n; i++)
        p[lower_bound(b, b+cnt, a[i])-b].pb(i);
    LL ans=0;
    for(int i=0; i<n; i++)
    {
        if(a[i]%k)continue ;
        LL t1=a[i]/k, t2=1LL*a[i]*k;
        if(!s.count(t1) || !s.count(t2))continue ;
        int p1=lower_bound(b, b+cnt, t1)-b;
        int p2=lower_bound(b, b+cnt, t2)-b;
        LL c1=lower_bound(ALL(p[p1]), i)-p[p1].begin();
        LL c2=p[p2].size()-(upper_bound(ALL(p[p2]), i)-p[p2].begin());
        ans+=c1*c2;
    }
    cout<<ans<<endl;
    return 0;
}

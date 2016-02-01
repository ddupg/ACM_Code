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
typedef pair<LL, int> pli;

const int maxn=200000+100;

int n;
LL m;

vector<pli> ori;
vector<pli> low, up;
vector<LL> sl, su;

int main()
{
    scanf("%d%I64d", &n, &m);
    sl.pb(0), su.pb(0);
    for(int i=0; i<n; i++)
    {
        LL cap;
        int t;
        scanf("%I64d%d", &cap, &t);
        ori.pb(mp(cap, t));
        if(t)low.pb(mp(cap, i+1)), sl.pb(cap);
        else up.pb(mp(cap, i+1)), su.pb(cap);
    }

    sort(ALL(ori));
    reverse(ALL(ori));
    sort(ALL(low));
    reverse(ALL(low));
    sort(ALL(up));
    reverse(ALL(up));
    sort(sl.begin()+1, sl.end());
    reverse(sl.begin()+1, sl.end());
    sort(su.begin()+1, su.end());
    reverse(su.begin()+1, su.end());

    for(int i=1; i<sl.size(); i++)
        sl[i]+=sl[i-1];
    for(int i=1; i<su.size(); i++)
        su[i]+=su[i-1];

    int ans=0, cnt=0;
    LL sum=0;
    for(int i=0; i<ori.size(); i++)
    {
        ans++, sum+=ori[i].fst;
        if(sum>=m)
            break;
    }
    for(cnt=low.size(); cnt>=0; cnt--)
        if(ans-cnt<=up.size() && sl[cnt]+su[ans-cnt]>=m)
            break;

    printf("%d %d\n", ans, cnt);
    bool first=true;
    for(int i=0; i<cnt; i++)
    {
        if(!first)putchar(' ');
        first=false;
        printf("%d", low[i].snd);
    }
    for(int i=0; i<ans-cnt; i++)
    {
        if(!first)putchar(' ');
        first=false;
        printf("%d", up[i].snd);
    }
    return 0;
}

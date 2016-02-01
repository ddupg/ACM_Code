#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define fst first
#define snd second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=400000+100;

LL c[maxn];
int n, m, cnt, a[maxn], b[maxn], w[maxn];
pii op[maxn];

void add(int x, LL v)
{
    for(; x<=cnt; x+=(x&-x))
        c[x]+=v;
}

LL qry(int x)
{
    LL ans=0;
    for(; x; x-=(x&-x))
        ans+=c[x];
    return ans;
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d%d", &op[i].fst, &op[i].snd);
        b[++m]=op[i].fst, b[++m]=op[i].snd;
    }
    sort(b+1, b+m+1);
    m=unique(b+1, b+m+1)-b-1;
    for(int i=1; i<=m; i++)
    {
        if(b[i]!=a[cnt]+1)
        {
            int t=a[cnt];
            a[++cnt]=t+1, w[cnt]=b[i]-t-1;
        }
        a[++cnt]=b[i], w[cnt]=1;
    }
    memcpy(b, a, sizeof a);
    for(int i=0; i<n; i++)
    {
        int x=lower_bound(b+1, b+cnt+1, op[i].fst)-b;
        int y=lower_bound(b+1, b+cnt+1, op[i].snd)-b;
        swap(a[x], a[y]);
    }
    LL ans=0;
    for(int i=cnt; i; i--)
    {
        int k=lower_bound(b+1, b+cnt+1, a[i])-b;
        ans+=1LL*w[i]*qry(k-1);
        add(k, w[i]);
    }
    cout<<ans<<endl;
    return 0;
}

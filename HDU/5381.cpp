#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=10010;

int gcd[maxn][20], mm[maxn];
int n, m, a[maxn], unit;
vector<pii> lef[maxn], rig[maxn];
LL ans[maxn];

void init()
{
    mm[0]=-1;
    for(int i=1; i<=n; i++)
    {
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
        gcd[i][0]=a[i];
    }
    for(int j=1; j<=mm[n]; j++)
        for(int i=1; i+(1<<j)-1<=n; i++)
            gcd[i][j]=__gcd(gcd[i][j-1], gcd[i+(1<<j-1)][j-1]);
}

int query(int x, int y)
{
    int k=mm[y-x+1];
    return __gcd(gcd[x][k], gcd[y-(1<<k)+1][k]);
}

void gao()
{
    for(int i=1; i<=n; i++)
        lef[i].clear(), rig[i].clear();
    for(int i=1; i<=n; i++)
    {
        int L=1, R=i, mid, g=a[i];
        while(true)
        {
            while(L<R)
            {
                mid=L+R>>1;
                if(query(mid, i)==g)R=mid;
                else L=mid+1;
            }
            lef[i].pb(mp(g, L));
            if(L==1)break;
            R=L-1, L=1, g=query(R, i);
        }
    }
    for(int i=1; i<=n; i++)
    {
        int L=i, R=n, mid, g=a[i];
        while(true)
        {
            while(L<R)
            {
                mid=L+R+1>>1;
                if(query(i, mid)==g)L=mid;
                else R=mid-1;
            }
            rig[i].pb(mp(g, L));
            if(L==n)break;
            L=L+1, R=n, g=query(i, L);
        }
    }
}

struct Query
{
    int L,R,id;
} nd[maxn];

bool cmp(Query a,Query b)
{
    if(a.L/unit != b.L/unit)return a.L/unit < b.L/unit;
    else return a.R < b.R;
}

LL Left(int x, int L)
{
    int p=x;
    LL ans=0;
    for(int i=0; i<lef[x].size(); i++)
    {
        int g=lef[x][i].fst, pos=max(L, lef[x][i].snd);
        ans+=1LL*g*(p-pos+1);
        p=pos-1;
        if(p<L)break;
    }
    return ans;
}

LL Right(int x, int R)
{
    int p=x;
    LL ans=0;
    for(int i=0; i<rig[x].size(); i++)
    {
        int g=rig[x][i].fst, pos=min(R, rig[x][i].snd);
        ans+=1LL*g*(pos-p+1);
        p=pos+1;
        if(p>R)break;
    }
    return ans;
}

void work()
{
    long long temp = 0;
    int L = 1;
    int R = 0;
    unit=(int)sqrt(n);
    sort(nd, nd+m, cmp);
    LL cnt=0;
    for(int i = 0; i < m; i++)
    {
        for(; R < nd[i].R; R++)
            cnt+=Left(R+1, L);
        for(; R > nd[i].R; R--)
            cnt-=Left(R, L);
        for(; L < nd[i].L; L++)
            cnt-=Right(L, R);
        for(; L > nd[i].L; L--)
            cnt+=Right(L-1, R);
        ans[nd[i].id]=cnt;
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
            scanf("%d", a+i);
        init();
        gao();
        scanf("%d", &m);
        for(int i=0; i<m; i++)
        {
            scanf("%d%d", &nd[i].L, &nd[i].R);
            nd[i].id=i;
        }
        work();
        for(int i=0; i<m; i++)
            printf("%I64d\n", ans[i]);
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int maxn=30000;

struct BT
{
    int n;
    LL bit[maxn];
    void init(int n)
    {
        this->n=n;
        memset(bit, 0, sizeof bit);
    }
    int lowbit(int x)
    {
        return x&(-x);
    }
    void update(int x, LL val)
    {
        for(; x<=n; x+=lowbit(x))
            bit[x]+=val;
    }
    LL query(int x)
    {
        LL ans=0;
        for(; x>0; x-=lowbit(x))
            ans+=bit[x];
        return ans;
    }
} bt, bts;

struct Node
{
    LL x, val, rank;
} nd[maxn];

bool cmp1(const Node& a, const Node& b)
{
    return a.val<b.val;
}
bool cmp2(const Node& a, const Node& b)
{
    return a.x<b.x;
}

int main()
{
    int n;
    scanf("%d", &n);
    bt.init(n);
    bts.init(n);
    for(int i=0; i<n; i++)
        scanf("%I64d%I64d", &nd[i].val, &nd[i].x);
    sort(nd, nd+n, cmp1);
    for(int i=0; i<n; i++)
        nd[i].rank=i+1;
    sort(nd, nd+n, cmp2);
    LL ans=0;
    for(int i=0; i<n; i++)
    {
        LL k=bt.query(nd[i].rank);
        LL s=bts.query(nd[i].rank);
        ans+=nd[i].val*(nd[i].x*k-s);
        bt.update(nd[i].rank, 1);
        bts.update(nd[i].rank, nd[i].x);
    }
    bt.init(n);
    bts.init(n);
    for(int i=n-1; i>=0; i--)
    {
        int k=bt.query(nd[i].rank);
        int s=bts.query(nd[i].rank);
        ans+=nd[i].val*(s-nd[i].x*k);
        bt.update(nd[i].rank, 1);
        bts.update(nd[i].rank, nd[i].x);
    }
    printf("%I64d\n", ans);
    return 0;
}

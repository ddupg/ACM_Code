#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;

const int maxn=100050;

struct SegmentTree
{
    int sum[maxn<<2], cov[maxn<<2];/**1: zero, 2: one**/

    void pushup(int rt)
    {
        sum[rt]=sum[ls]+sum[rs];
    }
    void pushdown(int rt, int m)
    {
        if(cov[rt]==1)
        {
            cov[ls]=cov[rs]=1;
            sum[ls]=sum[rs]=0;
        }
        if(cov[rt]==2)
        {
            cov[ls]=cov[rs]=2;
            sum[ls]=(m>>1);
            sum[rs]=m-sum[ls];
        }
        cov[rt]=0;
    }
    void upd_zero(int L, int R, int l, int r, int rt)
    {
        if(L<=l && R>=r)
        {
            cov[rt]=1;
            sum[rt]=0;
            return ;
        }
        int mid=l+r>>1;
        pushdown(rt, r-l+1);
        if(L<=mid)upd_zero(L, R, lson);
        if(R>mid)upd_zero(L, R, rson);
        pushup(rt);
    }
    void upd_one(int L, int R, int l, int r, int rt)
    {
        if(L<=l && R>=r)
        {
            cov[rt]=2;
            sum[rt]=r-l+1;
            return ;
        }
        int mid=l+r>>1;
        pushdown(rt, r-l+1);
        if(L<=mid)upd_one(L, R, lson);
        if(R>mid)upd_one(L, R, rson);
        pushup(rt);
    }
    int query(int L, int R, int l, int r, int rt)
    {
        if(L<=l && R>=r) return sum[rt];
        int mid=l+r>>1;
        pushdown(rt, r-l+r);
        int ans=0;
        if(L<=mid)ans+=query(L, R, lson);
        if(R>mid)ans+=query(L, R, rson);
        return ans;
    }

} st[27];
char str[maxn];

int main()
{
    int n, m, cnt[30];
    scanf("%d%d", &n, &m);
    scanf("%s", str+1);
    for(int i=1; i<=n; i++)
        st[str[i]-'a'].upd_one(i, i, 1, n, 1);
    while(m--)
    {
        int L, R, op;
        scanf("%d%d%d", &L, &R, &op);
        for(int i=0; i<26; i++)
        {
            cnt[i]=st[i].query(L, R, 1, n, 1);
            st[i].upd_zero(L, R, 1, n, 1);
        }
        if(op)
        {
            for(int i=0; i<26; L+=cnt[i++])if(cnt[i])
                    st[i].upd_one(L, L+cnt[i]-1, 1, n, 1);
        }
        else
        {
            for(int i=25; i>=0; L+=cnt[i--])if(cnt[i])
                    st[i].upd_one(L, L+cnt[i]-1, 1, n, 1);
        }
    }
    for(int i=1; i<=n; i++)
        for(int j=0; j<26; j++)
            if(st[j].query(i, i, 1, n, 1))
            {
                putchar(j+'a');
                break;
            }
    return 0;
}

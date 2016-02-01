#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define fst first
#define snd second
using namespace std;
typedef pair<int, int> pii;

const int maxn=400000+100;

struct BIT
{
    int n, bit[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            bit[i]=0;
    }
    void add(int x, int v)
    {
        for(; x<=n; x+=(x&-x))
            bit[x]+=v;
    }
    int query(int x)
    {
        int ans=0;
        for(; x; x-=(x&-x))
            ans+=bit[x];
        return ans;
    }
} lef, rig;

pii op[maxn], add[maxn];
int t[maxn];

int main()
{
    int n, kase=0;
    while(~scanf("%d", &n))
    {
        int cnt=0, tot=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d%d", &op[i].fst, &op[i].snd);
            if(!op[i].fst)
            {
                ++cnt;
                add[cnt]=pii(op[i].snd, op[i].snd+cnt);
                t[tot++]=op[i].snd, t[tot++]=op[i].snd+cnt;
            }
        }
        sort(t, t+tot);
        tot=unique(t, t+tot)-t;
        lef.init(tot), rig.init(tot);
        cnt=0;
        printf("Case #%d:\n", ++kase);
        for(int i=0; i<n; i++)
        {
            if(!op[i].fst)
            {
                cnt++;
                int x=op[i].snd, y=x+cnt;
                x=lower_bound(t, t+tot, x)-t+1;
                y=lower_bound(t, t+tot, y)-t+1;
                int ans=lef.query(tot)-lef.query(x-1);
                ans-=rig.query(tot)-rig.query(y);
                printf("%d\n", ans);
                lef.add(x, 1);
                rig.add(y, 1);
            }
            else
            {
                int x=add[op[i].snd].fst;
                int y=add[op[i].snd].snd;
                x=lower_bound(t, t+tot, x)-t+1;
                y=lower_bound(t, t+tot, y)-t+1;
                lef.add(x, -1);
                rig.add(y, -1);
            }
        }
    }
    return 0;
}

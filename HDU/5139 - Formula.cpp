#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD=1000000007;
struct Node
{
    int x, id, ans;
}node[100010];
int cmp1(const Node a, const Node b)
{
    return a.x<b.x || (a.x==b.x && a.id<b.id);
}
int cmp2(const Node a, const Node b)
{
    return a.id<b.id;
}
int main()
{
    int n=0;
    while(~scanf("%d", &node[++n].x))
        node[n].id=n;
    --n;
    sort(node+1, node+n+1, cmp1);
    int top=1;
    long long f=1, d=1;
    for(int i=1; top<=n && i<=10000000; i++)
    {
        d=d*i%MOD;
        f=d*f%MOD;
        while(node[top].x==i)
        {
            node[top].ans=f;
            ++top;
        }
    }
    sort(node+1, node+1+n, cmp2);
    for(int i=1;i<=n; i++)
        printf("%d\n", node[i].ans);
    return 0;
}

#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 1000100;
const int MOD =1000000007;
int d[maxn],f[maxn];
void init()
{
    d[0]=1;
    f[0]=1;
    int kk=1;
    long long td=1,fd=1;
    for(int i=2; i<=10000000; i++)
    {
        fd=fd*i%MOD;
        td=td*fd%MOD;
        if(i%10==0)
        {
            d[kk]=td;
            f[kk++]=fd;
        }
    }
}
int main()
{
    init();
    int n;
    while(scanf("%d",&n)==1)
    {
        int posi=n/10;
        int len=n%10;
        long long  td=d[posi],fd=f[posi];
        long long i=n/10*10+1;
        for(int cnt=1; cnt<=len; cnt++,i++)
        {
            fd=fd*i%MOD;
            td=td*fd%MOD;
        }
        printf("%d\n",td);
    }
    return 0;
}

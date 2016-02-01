#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1<<16;
const int oo=0x3f3f3f3f;

struct Node
{
    char name[110];
    int t, dt;
    bool operator < (const Node& a)const
    {
        return strcmp(name, a.name)<0;
    }
} nd[16];

int n, d[maxn], sum[maxn], pre[maxn];

void print(int x)
{
    if(!x)return ;
    print(1<<pre[x]^x);
    printf("%s\n", nd[pre[x]].name);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%s%d%d", nd[i].name, &nd[i].dt, &nd[i].t);
        for(int i=0; i<(1<<n); i++)
        {
            sum[i]=0;
            for(int j=0; j<n; j++)
                if(1<<j&i)
                    sum[i]+=nd[j].t;
        }
        memset(d, 0x3f, sizeof d);
        memset(pre, -1, sizeof pre);
        d[0]=0;
        for(int s=0; s<(1<<n); s++)if(d[s]<oo)
                for(int i=0; i<n; i++)
                    if(1<<i^s)
                    {
                        int tmp=d[s]+max(0, sum[s]+nd[i].t-nd[i].dt), s1=1<<i|s;
                        if(tmp<d[s1])
                        {
                            d[s1]=tmp;
                            pre[s1]=i;
                        }
                    }
        printf("%d\n", d[(1<<n)-1]);
        print((1<<n)-1);
    }
    return 0;
}

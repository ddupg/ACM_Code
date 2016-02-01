#include <cstdio>
#include <iostream>
using namespace std;

bool vis[10000000+10];
int pri[1000000+10], cnt=0;

void init()
{
    for(int i=2; i*i<=1e7; i++)
        if(!vis[i])for(int j=i*i; j<=1e7; j+=i)
            vis[j]=true;
    for(int i=2; i<=1e7; i++)
        if(!vis[i])
            pri[cnt++]=i;
}

int main()
{
    init();
    int T, n, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        int ans=0;
        for(int i=0; i<cnt && pri[i]<n && pri[i]<=n-pri[i]; i++)
            if(!vis[n-pri[i]])
                ans++;
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

bool vis[10000000+100];
vector<int> pri;
int cnt[1000000+100], sum[1000000+100], a[10000000+100];

void init()
{
    for(int i=2; i*i<=1e7; i++)if(!vis[i])
        for(int j=i*i; j<=1e7; j+=i)
            vis[j]=1;
    for(int i=2; i<1e7; i++)
        if(!vis[i])
            pri.push_back(i);
    pri.push_back(2e9+7);
}

int main()
{
    init();
    int n, m, x;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &x);
        a[x]++;
    }
    for(int i=0; i<pri.size(); i++)
        for(int j=pri[i]; j<=1e7; j+=pri[i])
            cnt[i]+=a[j];
    for(int i=1; i<pri.size(); i++)
        sum[i]=sum[i-1]+cnt[i-1];
    scanf("%d", &m);
    while(m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l=lower_bound(pri.begin(), pri.end(), l)-pri.begin();
        r=upper_bound(pri.begin(), pri.end(), r)-pri.begin();
        printf("%d\n", sum[r]-sum[l]);
    }
    return 0;
}

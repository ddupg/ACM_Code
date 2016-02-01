#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long LL;

vector<LL> pri, ans;
bool vis[1000000+10];

void init()
{
    for(int i=2; i*i<1e6; i++)
        for(int j=i*i; j<=1e6; j+=i)
            vis[j]=true;
    for(int i=2; i<=1e6; i++)
        if(!vis[i])
            pri.push_back(i);
    for(int i=0; i<pri.size(); i++)
    {
        LL tmp=pri[i]*pri[i];
        while(tmp<=1LL*1e6*1e6)
        {
            ans.push_back(tmp);
            tmp*=pri[i];
        }
    }
    sort(all(ans));
}

int main()
{
    init();
    int T;
    scanf("%d", &T);
    LL a, b;
    while(T--)
    {
        scanf("%lld%lld", &a, &b);
        printf("%d\n", upper_bound(all(ans), b)-lower_bound(all(ans), a));
    }
    return 0;
}

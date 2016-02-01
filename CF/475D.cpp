#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;

map<int, LL> mp[2], ans;

int main()
{
    int n, x, pre=0, cur=1;;
    scanf("%d", &n);
    while(n--)
    {
        int x;
        scanf("%d", &x);
        mp[cur].clear();
        for(map<int, LL>::iterator i = mp[pre].begin(); i!=mp[pre].end(); i++)
        {
            int k=(*i).first;
            int g=__gcd(k, x);
            ans[g]+=mp[pre][k];
            mp[cur][g]+=mp[pre][k];
        }
        ans[x]++;
        mp[cur][x]++;
        swap(cur, pre);
    }
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &x);
        printf("%I64d\n", ans[x]);
    }
    return 0;
}

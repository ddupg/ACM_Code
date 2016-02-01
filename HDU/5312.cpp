#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
typedef long long LL;
const int maxn=20000;

LL val[maxn];
set<LL> S;

int solve()
{
    LL x;
    scanf("%I64d", &x);
    if(S.count(x))
        return 1;
    for(int L=1, R=maxn-1; L<=R; )
    {
        if(val[L]+val[R]==x)return 2;
        if(val[L]+val[R]>x)R--;
        else L++;
    }
    for(int i=3; i<10; i++)
        if((x-i)%6==0)
            return i;
}

int main()
{
    for(int i=1; i<maxn; i++)
    {
        val[i]=3LL*i*(i-1)+1;
        S.insert(val[i]);
    }
    int T;
    scanf("%d", &T);
    while(T--)
        printf("%d\n", solve());
    return 0;
}

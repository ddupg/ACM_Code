#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;

const int maxn=100000+100;

int d[maxn], w[maxn], N, n, m;

void input_case()
{
    n=0;
    while(N--)
    {
        int tmp_n, tmp_c;
        scanf("%d%d", &tmp_n, &tmp_c);
        int num=1;
        while(tmp_n>=num)
        {
            w[n++]=tmp_c*num;
            tmp_n-=num;
            num*=2;
        }
        if(tmp_n>0)
            w[n++]=tmp_c*tmp_n;
    }
}

void dp()
{
    memset(d, 0, sizeof(d));
    for(int i=0; i<n; i++)
        for(int j=m; j>=w[i]; j--)
            d[j]=max(d[j], d[j-w[i]]+w[i]);
}

int main()
{
    while(~scanf("%d%d", &m, &N))
    {
        input_case();
        dp();
        printf("%d\n", d[m]);
    }
    return 0;
}

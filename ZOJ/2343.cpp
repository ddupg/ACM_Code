#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define snd second
using namespace std;
typedef pair<int, int> pii;
const int maxn=1100;

int n, m, y, ans[maxn], x[maxn];
pii nd[maxn];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n ,&m, &y);
        int s=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d", x+i);
            ans[i]=m*x[i]/y;
            s+=ans[i];
            nd[i]=pii(m*x[i]%y, i);
        }
        sort(nd, nd+n);
        for(int i=1; i<=m-s; i++)
            ans[nd[n-i].snd]++;
        for(int i=0; i<n; i++)
        {
            if(i)putchar(' ');
            printf("%d", ans[i]);
        }
        puts("");
        if(T)puts("");
    }
    return 0;
}

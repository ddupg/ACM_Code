#include <iostream>
#include <cstdio>
#include <set>
typedef long long LL;
typedef unsigned long long LLU;
using namespace std;

set<LL> s;
int n, a[20], max_len;

void dfs(int u, int b, int c, int d)
{
    if(b>max_len || c>max_len || d>max_len)
        return ;
    if(u==n)
    {
        if(c>=b && d>=c && b+c>d)
            s.insert(b*1LL*1e12 + c*1LL*1e6 + d);
        return ;
    }
    dfs(u+1, b+a[u], c, d);
    dfs(u+1, b, c+a[u], d);
    dfs(u+1, b, c, d+a[u]);
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        s.clear();
        scanf("%d", &n);
        max_len=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d", &a[i]);
            max_len+=a[i];
        }
        max_len=(max_len+1)/2;

        dfs(0, 0, 0, 0);
        printf("%d\n", s.size());
    }
    return 0;
}

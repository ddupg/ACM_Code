#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=1e5+100;

struct Node
{
    int u, v, color;
} node[maxn];
bool cmp1(const Node & a, const Node & b)
{
    return a.color<b.color;
}

int p[maxn], n, m, fb[maxn], flag;

void init_case()
{
    for(int i=1; i<=n; i++)
        p[i]=i;
}

int find(int x)
{
    return x==p[x] ? x : p[x]=find(p[x]);
}

void init()
{
    fb[0]=1;
    fb[1]=2;
    flag=2;
    while(fb[flag-1]<=1e5+100)
    {
        fb[flag]=fb[flag-1]+fb[flag-2];
        flag++;
    }
}

int main()
{
    init();
    int t, kase=0;
    scanf("%d", &t);
    while(t-- && ~scanf("%d%d", &n, &m))
    {
        for(int i=0; i<m; i++)
            scanf("%d%d%d", &node[i].u, &node[i].v, &node[i].color);
        sort(node, node+m, cmp1);

        init_case();
        int Min=0, Max=0, cnt=0;
        for(int i=0; i<m && cnt<n-1; i++)
        {
            int x=find(node[i].u), y=find(node[i].v);
            if(x!=y)
            {
                p[x]=y;
                cnt++;
                if(node[i].color)
                    Min++;
            }
        }

        if(cnt!=n-1)
        {
            printf("Case #%d: No\n", ++kase);
            continue ;
        }

        init_case();

        for(int i=m-1, cnt=0; i>=0 && cnt<n-1; i--)
        {
            int x=find(node[i].u), y=find(node[i].v);
            if(x!=y)
            {
                p[x]=y;
                cnt++;
                if(node[i].color)
                    Max++;
            }
        }
        int ok=0;
        for(int i=0; i<flag && fb[i]<=Max; i++)
            if(fb[i]>=Min && fb[i]<=Max)
            {
                ok=1;
                break;
            }

//        cout<<Min<<" "<<Max<<endl;

        if(ok)
            printf("Case #%d: Yes\n", ++kase);
        else printf("Case #%d: No\n", ++kase);
    }
    return 0;
}

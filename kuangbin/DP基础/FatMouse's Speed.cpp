#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=1100;

struct Node
{
    int a, b, id;
    bool operator < (const Node rhs)const
    {
        return a<rhs.a || (a==rhs.a && b>rhs.b);
    }
} nd[1100];

int main()
{
    int n=0, d[maxn], pre[maxn];
    while(~scanf("%d%d", &nd[n].a, &nd[n].b))
        nd[n].id=n+1, n++;
    sort(nd, nd+n);
    int ans=0, tmp=0;
    for(int i=0; i<n; i++)
    {
        d[i]=1;
        pre[i]=-1;
        for(int j=0; j<i; j++)
            if(nd[j].a<nd[i].a && nd[j].b>nd[i].b && d[j]+1>d[i])
                d[i]=d[j]+1, pre[i]=j;
        if(d[i]>ans)
            ans=d[i], tmp=i;
    }
    printf("%d\n", ans);
    vector<int> v;
    while(~tmp)
    {
        v.push_back(nd[tmp].id);
        tmp=pre[tmp];
    }
    for(int i=v.size()-1; i>=0; i--)
        printf("%d\n", v[i]);
    return 0;
}

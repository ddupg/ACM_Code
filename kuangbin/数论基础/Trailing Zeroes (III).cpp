#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct Node
{
    int x, id;
    bool operator < (const Node& a)const
    {
        return x<a.x;
    }
} nd[10000+10];
int ans[10000+10];

int main()
{
    memset(ans, -1, sizeof ans);
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d", &nd[i].x);
        nd[i].id=i+1;
    }
    sort(nd, nd+n);
    int cnt=0;
    for(int i=0, j=0; j<n; i+=5)
    {
        int tmp=i;
        while(tmp && tmp%5==0)
            cnt++, tmp/=5;
        while(cnt>nd[j].x && j<n)
            j++;
        while(cnt==nd[j].x && j<n)
            ans[nd[j].id]=i, j++;
    }
    for(int i=1; i<=n; i++)
    {
        printf("Case %d: ", i);
        if(ans[i]==-1)puts("impossible");
        else printf("%d\n", ans[i]);
    }
    return 0;
}



//#include <cstdio>
//using namespace std;
//
//int fun(int x)
//{
//    return x==0 ? 0 : x/5+fun(x/5);
//}
//
//int main()
//{
//    int T, kase=0;
//    scanf("%d", &T);
//    while(T--)
//    {
//        int n;
//        scanf("%d", &n);
//        int L=1, R=1000000000;
//        while(L<R)
//        {
//            int mid=(L+R)>>1;
//            if(fun(mid)>=n)
//                R=mid;
//            else L=mid+1;
//        }
//        if(fun(L)==n)
//            printf("Case %d: %d\n", ++kase, L);
//        else printf("Case %d: impossible\n", ++kase);
//    }
//    return 0;
//}

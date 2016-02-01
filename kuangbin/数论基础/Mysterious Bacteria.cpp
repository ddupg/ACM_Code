#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        double x;
        int flag=1;
        scanf("%lf", &x);
        if(x<0)flag=-1, x=-x;
        for(int i=32; i>=1; i--)
        {
            int t=(int)(pow(x, 1.0/i)+1e-7);
            if(((flag==-1 && i%2) || flag==1) && fabs(x-pow(t, i))<1e-7)
            {
                printf("Case %d: %d\n", ++kase, i);
                break;
            }
        }
    }
    return 0;
}

//#include <cstdio>
//#include <algorithm>
//using namespace std;
//typedef long long LL;
//const int maxn=1000000;
//
//bool vis[maxn+10];
//int pri[maxn+10], c;
//
//int main()
//{
//    for(int i=2; i*i<=maxn; i++)
//        if(!vis[i])for(int j=i*i; j<=maxn; j+=i)
//                vis[j]=true;
//    for(int i=2; i<=maxn; i++)
//        if(!vis[i])pri[c++]=i;
//
//    int T, kase=0;
//    scanf("%d", &T);
//    while(T--)
//    {
//        LL x;
//        int flag=1;
//        scanf("%lld", &x);
//        if(x<0)
//            x=-x, flag=-1;
//        int ans=0;
//        for(int i=0; x/pri[i]>=pri[i] && i<c; i++)
//            if(x%pri[i]==0)
//            {
//                int cnt=0;
//                while(x%pri[i]==0)
//                    x/=pri[i], cnt++;
//                if(flag==-1)
//                    while(cnt%2==0)
//                        cnt>>=1;
//                ans=__gcd(ans, cnt);
//            }
//        if(x>1)
//            ans=1;
//        printf("Case %d: %d\n", ++kase, ans);
//    }
//    return 0;
//}

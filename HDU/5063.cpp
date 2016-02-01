#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;
const int MOD=1e9+7;
const int maxn=100000+100;

LL POW(int x, int m)
{
    LL ans=x;
    while(m--)
    {
        ans=ans*ans;
        ans%=MOD;
    }
    return ans;
}

int op[maxn], n, cnt=0;

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        char c;
        int m, x;
        cnt=0;
        scanf("%d%d", &n, &m);
        while(m--)
        {
            getchar();
            scanf("%c%d", &c, &x);
            if(c!='Q')
                op[cnt++]=x;
            else
            {
                int flag=0;
                for(int i=cnt-1; i>=0; i--)
                {
                    if(op[i]==3)
                        flag++;
                    else if(op[i]==2)
                        x=n+1-x;
                    else
                    {
                        if(x<=(n+1)/2)
                            x=x*2-1;
                        else x=(x-(n+1)/2)*2;
                    }
                }
                printf("%I64d\n", POW(x, flag));
            }
        }
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

int num[100000+100];
int d[100000+100];

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
            scanf("%d", &num[i]);
        int max_sum=num[1], sum=num[1];
        int l=1, L=1, R=1;
        for(int i=2; i<=n; i++)
        {
            if(num[i]>num[i]+sum)
            {
                sum=num[i];
                l=i;
            }
            else
                sum+=num[i];
            if(sum>max_sum)
            {
                L=l;
                R=i;
                max_sum=sum;
            }
        }
        if(kase)puts("");
        printf("Case %d:\n", ++kase);
        printf("%d %d %d\n", max_sum, L, R);
    }
    return 0;
}

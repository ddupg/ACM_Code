#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
    int a[10];
    while(1)
    {
        int sum=0;
        for(int i=1; i<=6; i++)
        {
            scanf("%d", &a[i]);
            sum+=a[i];
        }
        if(!sum)break;

        int ans=0;
        ans+=a[6];
        if(a[5])
        {
            ans+=a[5];
            a[1]=a[1]-a[5]*11;
        }
        if(a[4])
        {
            ans+=a[4];
            if(a[2]>a[4]*5)
                a[2]-=a[4]*5;
            else
            {
                a[1]=a[1]-(a[4]*20-a[2]*4);
                a[2]=0;
            }
        }
        if(a[3])
        {
            ans+=a[3]/4;
            a[3]%=4;
            if(a[3])ans++;
            if(a[3]==1)
            {
                a[2]-=5;
                a[1]-=7;
            }
            else if(a[3]==2)
            {
                a[2]-=3;
                a[1]-=6;
            }
            else if(a[3]==3)
            {
                a[2]-=1;
                a[1]-=5;
            }
        }
        if(a[2]>0)
        {
            ans+=a[2]/9;
            a[2]%=9;
            if(a[2])ans++;
            a[1]=a[1]-(36-a[2]*4);
        }
        if(a[1]>0)
            ans+=(a[1]+35)/36;
        printf("%d\n", ans);
    }
    return 0;
}

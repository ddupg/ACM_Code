#include <cstdio>
#include <iostream>
using namespace std;

int euler[2000001];
void getEuler()
{
    euler[1] = 1;
    for(int i = 2; i <= 2000000; i++)
        if(!euler[i])
            for(int j = i; j <= 2000000; j += i)
            {
                if(!euler[j])
                    euler[j] = j;
                euler[j] = euler[j]/i*(i-1);
            }
}

int main()
{
    getEuler();
    for(int i=1; i<=2000000; i++)
        euler[i]=max(euler[i-1], euler[i]);
    euler[1]=0;
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        int n, x;
        long long ans=0;
        scanf("%d", &n);
        while(n--)
        {
            scanf("%d", &x);
            ans+=lower_bound(euler, euler+2000000, x)-euler;
        }
        printf("Case %d: %lld Xukha\n", ++kase, ans);
    }
    return 0;
}

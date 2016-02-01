#include <iostream>
#include <cstdio>
using namespace std;

bool judge(int x)
{
    if(x==1)return 1;
    for(int i=2; i*i<=x; i++)
        if(x%i==0)
            return 0;
    return 1;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int x, sum=0;
        while(n--)
            if(scanf("%d", &x) && judge(x))
                sum+=x;
        printf("%d\n", sum);
    }
    return 0;
}

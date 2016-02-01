#include <cstdio>
using namespace std;

int d[1000000+10];

bool judge(int x)
{
    bool flag=false;
    while(x)
    {
        int t=x%10;
        if(t==4)return false;
        if(t==6 && flag)
            return false;
        if(t==2)flag=true;
        else flag=false;
        x/=10;
    }
    return true;
}

void init()
{
    for(int i=1; i<=1000000; i++)
        d[i]=d[i-1]+judge(i);
}

int main()
{
    init();
    int a, b;
    while(~scanf("%d%d", &a, &b) && a+b)
        printf("%d\n", d[b]-d[a-1]);
    return 0;
}

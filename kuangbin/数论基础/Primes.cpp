#include <cstdio>
using namespace std;

bool judge(int x)
{
    if(x==1 || x==2)return false;
    for(int i=2; i*i<=x; i++)
        if(x%i==0)
            return false;
    return true;
}

int main()
{
    int x, kase=0;
    while(~scanf("%d", &x) && x>0)
        printf("%d: %s\n", ++kase, judge(x)?"yes":"no");
    return 0;
}

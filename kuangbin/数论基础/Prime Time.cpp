#include <cstdio>
using namespace std;
const int maxn=10010;
int ans[maxn];

bool isPrime(int x)
{
    for(int i=2; x/i>=i; i++)
        if(x%i==0)
            return false;
    return true;
}

void init()
{
    ans[0]=1;
    for(int i=1; i<maxn; i++)
        ans[i]=ans[i-1]+isPrime(i*i+i+41);
}

int main()
{
    init();
    int a, b;
    while(~scanf("%d%d", &a, &b))
    {
        if(!a)printf("%.2lf\n", 100.0*ans[b]/(b+1)+1e-7);
        else printf("%.2lf\n", 100.0*(ans[b]-ans[a-1])/(b-a+1)+1e-7);
    }
    return 0;
}

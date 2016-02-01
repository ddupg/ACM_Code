#include <iostream>
using namespace std;
typedef long long LL;
const int maxn=4000000;

int n;
LL phi[maxn+10], ans[maxn+10];

void init()
{
    phi[1]=1;
    for(int i=2; i<=maxn; i++)
        if(!phi[i])
            for(int j=i; j<=maxn; j+=i)
            {
                if(!phi[j])phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }

    for(int i=1; i<=maxn; i++)
        for(int j=i*2; j<=maxn; j+=i)
            ans[j]+=phi[j/i]*i;
    for(int i=2; i<=maxn; i++)
        ans[i]+=ans[i-1];
}

int main()
{
    init();
    while(cin>>n && n)
        cout<<ans[n]<<endl;
    return 0;
}

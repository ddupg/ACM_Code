#include <iostream>
using namespace std;
typedef long long LL;
const int maxn=1000000+10;

LL phi[maxn+10];

void init()
{
    phi[1]=1;
    for(int i=2; i<=maxn; i++)
        if(!phi[i])for(int j=i; j<=maxn; j+=i)
            {
                if(!phi[j])phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }
    for(int i=3; i<=maxn; i++)
        phi[i]+=phi[i-1];
}

int main()
{
    init();
    int n;
    while(cin>>n && n)
        cout<<phi[n]<<endl;
    return 0;
}

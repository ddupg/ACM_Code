#include <iostream>
#include <cstdio>
using namespace std;

int pow(int x, int b, int mod)
{
    int ans=1;
    while(b)
    {
        if(b&1)
            (ans*=x)%=mod;
        (x*=x)%=mod;
        b>>=1;
    }
    return ans;
}

int main()
{
    int n, m, k, ans=0, x;
    cin>>n>>m>>k;
    while(n--)
    {
        cin>>x;
        if(pow(x, m, k)==0)
            ans++;
    }
    cout<<ans<<endl;
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
using namespace std;
typedef long long LL;

const int mod=1000000007;

LL Pow(LL x, int b)
{
    LL ans=1;
    for(; b; b>>=1)
    {
        if(b&1)ans=ans*x%mod;
        x=x*x%mod;
    }
    return ans;
}


int main()
{
    int T, n;
    cin>>T;
    while(T--)
    {
        cin>>n;
        cout<<((Pow(2, n)-1-Pow(2, (n+1)/2-1+n/2))%mod+mod)%mod<<endl;
    }
    return 0;
}

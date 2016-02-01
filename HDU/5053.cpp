#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    unsigned long long a, b, ans;
    int t, kase=0;
    cin>>t;
    while(t--)
    {
        cin>>a>>b;
        ans=0;
        for(unsigned long long i=a; i<=b; i++)
            ans+=i*i*i;
        cout<<"Case #"<<++kase<<": "<<ans<<endl;
    }
    return 0;
}

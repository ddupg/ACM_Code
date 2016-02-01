#include <iostream>
using namespace std;
typedef long long LL;

int main()
{
    int n;
    cin>>n;
    LL l, r;
    while(n--)
    {
        cin>>l>>r;
        LL ans=l;
        for(int i=0; (1LL<<i)<=r; i++)
            if((ans&(1LL<<i))==0 && (ans|(1LL<<i))<=r)
                ans+=(1LL<<i);
        cout<<ans<<endl;
    }
    return 0;
}

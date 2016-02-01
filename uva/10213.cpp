#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;

int main()
{
    int T;
    LL n;
    cin>>T;
    while(T--)
    {
        cin>>n;
        LL V=0, E=0;
        for(int i=1; i<=n-3; i++)
        {
            V+=i*(n-2-i);
            E+=i*(n-2-i)+1;
        }
        V=V*n/4+n;
        E=E*n/2+n;
        cout<<2+E-V<<endl;
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1110;

int main()
{
    int T;
    LL val[maxn];
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        for(int i=0; i<n; i++)
            cin>>val[i];
        sort(val, val+n);
        int ans=0;
        for(int i=n-1; i>=0; i--)
        {
            int flag=1;
            for(int j=i+1; j<n; j++)
                if(val[j]%val[i]==0)
                {
                    flag=0;
                    break;
                }
            ans+=flag;
        }
        cout<<ans<<endl;
    }
    return 0;
}

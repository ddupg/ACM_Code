#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, x, y;

int main()
{
    while(cin>>n>>m>>x>>y)
    {
        if(n>m)swap(n, m), swap(x, y);
        int ans=(min(n, m)+1)/2;
        int l=y, r=m-y+1, u=x-1, d=n-x;
        if(min(l, r)>ans && x-1!=n-x)
            ans=min(max(u, d), min(l, r));
        else if(n%2 && n==m && x==y && x==n/2+1)
            ans--;
        cout<<ans<<endl;
    }
    return 0;
}

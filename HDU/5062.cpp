#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;

int C(int n, int m)
{
    int ans=1;
    for(int i=1; i<=n; i++)
        ans*=i;
    for(int i=1; i<=m; i++)
        ans/=i;
    for(int i=1; i<=n-m; i++)
        ans/=i;
    return ans;
}

int main()
{
    int ans[10]={1, 9};
    for(int i=2; i<=6; i++)
    {
        ans[i]=ans[i-1];
        ans[i]+=C(9, (i+1)/2);
    }
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        cout<<ans[n]<<endl;
    }
    return 0;
}

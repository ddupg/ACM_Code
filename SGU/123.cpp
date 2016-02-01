#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    unsigned long long f[50]={0, 1, 1}, sum[50]={0, 1, 2};
    for(int i=3; i<=42; i++)
        f[i]=f[i-1]+f[i-2], sum[i]=sum[i-1]+f[i];
    int x;
    cin>>x;
    cout<<sum[x]<<endl;
    return 0;
}

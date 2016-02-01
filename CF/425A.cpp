#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int a[220], n, k;

int solve(int x, int y)
{
    vector<int> v1, v2;
    int ans=0, sum=0;
    for(int i=0; i<n; i++)
    {
        if(i>=x && i<=y)
            v1.push_back(a[i]), sum+=a[i];
        else v2.push_back(a[i]);
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    ans=sum;
    for(int i=0; i<k && i<v1.size() && i<v2.size(); i++)
    {
        sum=sum-v1[i]+v2[v2.size()-1-i];
        ans=max(ans, sum);
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    for(int i=0; i<n; i++)
        cin>>a[i];
    int ans=a[0];
    for(int i=0; i<n; i++)
        for(int j=i; j<n; j++)
            ans=max(ans, solve(i, j));
    cout<<ans<<endl;
    return 0;
}

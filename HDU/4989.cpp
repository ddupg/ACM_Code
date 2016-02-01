#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
    int n, cnt;
    long long a[111];
    vector<long long> v;
    while(cin>>n)
    {
        for(int i=0; i<n; i++)
            cin>>a[i];
        v.clear();
        long long ans=0;
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                v.push_back(a[i]+a[j]);
        sort(v.begin(), v.end());
        vector<long long>::iterator it=unique(v.begin(), v.end());
        v.erase(it, v.end());
        for(int i=0; i<v.size(); i++)
            ans+=v[i];
        cout<<ans<<endl;
    }
    return 0;
}

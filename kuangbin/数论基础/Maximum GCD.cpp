#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    int T, x;
    cin>>T;
    getchar();
    while(T--)
    {
        string s;
        getline(cin, s);
        stringstream sin(s);
        vector<int> v;
        while(sin>>x)
            v.push_back(x);
        int ans=1;
        for(int i=0; i<v.size(); i++)
            for(int j=i+1; j<v.size(); j++)
                ans=max(ans, __gcd(v[i], v[j]));
        cout<<ans<<endl;
    }
    return 0;
}

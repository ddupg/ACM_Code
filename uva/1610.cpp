#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> s(1010);

int main()
{
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n && n)
    {
        for(int i=0; i<n; i++)
            cin>>s[i];
        sort(s.begin(), s.begin()+n);
        string s1(s[n/2-1]), s2(s[n/2]);
        int flag=0;
        string ans, tmp;
        for(int i=0; i<s1.length() && !flag; i++)
        {
            for(char c='A'; c<='Z'; c++)
            {
                if(ans+c>=s1 && ans+c<s2)
                {
                    cout<<ans+c<<endl;
                    flag=true;
                    break;
                }
            }
            ans+=s1[i];
        }
    }
    return 0;
}

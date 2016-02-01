#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long LL;

string s, t;

LL solve()
{
    LL ans=1;
    for(int i=0; s[i]; i++)
    {
        if(s[i]=='{')
        {
            int cnt=0;
            for(int j=i+1; s[j]; j++)
            {
                if(s[j]=='}')
                {
                    i=j;
                    break;
                }
                else if(s[j]=='|')
                    cnt++;
            }
            ans*=(cnt+1);
            if(ans>1e5)return -1;
        }
        else if(s[i]=='$')
        {
            int cnt=0;
            for(int j=i+1; s[j]; j++)
            {
                if(s[j]==' ')
                    cnt++;
                else ans*=(cnt+1), cnt=0;
                if(ans>1e5)return -1;
                if(s[j]=='$')
                {
                    i=j;
                    break;
                }
            }
        }
    }
    return ans;
}

int main()
{
    int n;
    while(cin>>n)
    {
        s="";
        getline(cin, t);
        while(n--)
        {
            getline(cin, t);
            s+=t;
        }
        LL ans=solve();
        if(ans==-1)cout<<"doge"<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;
const int maxn=1000000+100;

bool t[maxn];
vector<int> pri;

void init()
{
    for(int i=2; i*i<maxn; i++)
        for(int j=i*i; j<maxn; j+=i)
            t[j]=1;
    for(int i=2; i<maxn; i++)
        if(!t[i])
            pri.push_back(i);
}

int main()
{
    init();
    int T;
    long long n, cnt, ans, a, b;
    cin>>T;
    while(T--)
    {
        ans=1;
        cin>>a>>b;
        if(b%a)
        {
            cout<<0<<endl;
            continue ;
        }
        n=b/a;
        for(int i=0; i<pri.size(); i++)
            if(n%pri[i]==0)
            {
                cnt=0;
                while(n%pri[i]==0)
                {
                    cnt++;
                    n/=pri[i];
                }
                ans*=cnt*6;
            }
        if(n>1)
            ans*=6;
        cout<<ans<<endl;
    }
    return 0;
}

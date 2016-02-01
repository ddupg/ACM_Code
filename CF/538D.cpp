#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define all(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
const int maxn=1000000+100;

vector<int> v, ans;
int d[maxn], pre[maxn];

bool judge(int x)
{
    for(; x; x/=10)
        if(x%10!=1 && x%10!=0)
            return false;
    return true;
}

void init()
{
    for(int i=1; i<=1e6+1; i++)
        if(judge(i))
            v.push_back(i);
    clr(d, 0x3f);
    clr(pre, -1);
    d[0]=0;
    for(int i=0; i<v.size(); i++)
        for(int j=v[i]; j<maxn; j++)
            if(d[j]>d[j-v[i]]+1)
                d[j]=d[j-v[i]]+1, pre[j]=i;
}

int main()
{
    init();
    int n;
    cin>>n;
    cout<<d[n]<<endl;
    for(; n; n-=v[pre[n]])
        ans.push_back(v[pre[n]]);
    sort(all(ans));
    cout<<ans[0];
    for(int i=1; i<ans.size(); i++)
        cout<<' '<<ans[i];
    cout<<endl;
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=10000000;

int n, sum;
vector<int> pri, ans;
bool vis[maxn+10];

void init()
{
    for(int i=2; i*i<=maxn; i++)
        if(!vis[i])for(int j=i*i; j<=maxn; j+=i)
                vis[j]=true;
    for(int i=3; i<maxn; i++)
        if(!vis[i])
            pri.push_back(i);
}

int main()
{
    scanf("%d%d", &n, &sum);
    if(sum<n/2 || (n==1 && sum>0))
    {
        puts("-1");
        return 0;
    }
    int t=n>>1, a=-1, b=-1;
    if(sum>t-1 && t>0)
    {
        a=sum-t+1;
        b=a*2;
        ans.push_back(a);
        ans.push_back(b);
        t--;
    }
    int i;
    for(i=1; t>0; i+=2)
        if(i!=a && i!=b && i+1!=a && i+1!=b)
        {
            ans.push_back(i);
            ans.push_back(i+1);
            t--;
        }
    if(n&1)
    {
        while(!(i!=a && i!=b && i+1!=a && i+1!=b))
            i++;
        ans.push_back(i);
    }
    for(int i=0; i<n; i++)
        printf("%d%c", ans[i], i==n-1?'\n':' ');
    return 0;
}

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

vector<int> p;
int cnt[10000], n, tot;

int solve()
{
    p.clear();
    memset(cnt, 0, sizeof cnt);
    int t=n, tot=0;
    for(int i=2; i*i<=t; i++)
        if(t%i==0)
        {
            p.push_back(i);
            while(t%i==0)
            {
                t/=i;
                cnt[tot]++;
            }
            tot++;
        }
    if(t>1)
    {
        p.push_back(t);
        cnt[tot++]++;
    }
    int ans=0;
    for(int i=0; i<(1<<tot); i++)
    {
        int a=1, b=1;
        for(int j=0; j<tot; j++)
        {
            if(1<<j&i)
                b*=cnt[j]+1;
            else
                a*=cnt[j];
        }
        ans+=a*b;
    }
    return ans;
}

int main()
{
    while(~scanf("%d", &n) && n)
        printf("%d %d\n", n, (solve()+1)/2);
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define pb push_back
using namespace std;

const int maxn=100000+100;

int n, dep[maxn], q[maxn], head, tail;
vector<int> G[maxn];


int main()
{
    while(~scanf("%d", &n))
    {
        for(int i=1; i<=n; i++)
            G[i].clear();
        for(int i=2; i<=n; i++)
        {
            int u;
            scanf("%d", &u);
            G[u].pb(i);
        }
        head=tail=0;
        q[tail++]=1, dep[1]=0;
        while(head!=tail)
        {
            int u=q[head++];
            for(int i=0; i<G[u].size(); i++)
            {
                int v=G[u][i];
                dep[v]=dep[u]+1;
                q[tail++]=v;
            }
        }
        sort(dep+1, dep+1+n);
        double ans=0;
        if(n<=60)
        {
            for(int i=1; i<=n; i++)
                for(int j=i+1; j<=n; j++)
                    ans+=1.0*(dep[i]+1)*(dep[j]+1)/(dep[i]+dep[j]+2)*pow(2, i-1)/(pow(2, n)-1-n);
        }
        else
        {
            for(int i=n-60+1; i<=n; i++)
                for(int j=i+1; j<=n; j++)
                    ans+=1.0*(dep[i]+1)*(dep[j]+1)/(dep[i]+dep[j]+2)*pow(2, i-1-n);
        }
        printf("%.6f\n", ans);
    }
    return 0;
}

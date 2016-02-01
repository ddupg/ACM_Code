#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=10000;
vector<int> G[maxn], prime;
int vis[maxn], S, T;

int judge(int x, int y)
{
    int cnt=0;
    for(int i=1; i<=4; i++, x/=10, y/=10)
        if(x%10==y%10)
            cnt++;
    return cnt==3;
}

void init_prime()
{
    int a[maxn]= {0};
    for(int i=2; i*i<maxn; i++)
        for(int j=i*i; j<maxn; j+=i)
            a[j]=1;
    for(int i=1000; i<maxn; i++)
        if(!a[i])
            prime.push_back(i);
    for(int i=0; i<prime.size(); i++)
        for(int j=i; j<prime.size(); j++)
            if(judge(prime[i], prime[j]))
            {
                G[prime[i]].push_back(prime[j]);
                G[prime[j]].push_back(prime[i]);
            }
}

int bfs()
{
    queue<int> q;
    mem(vis, -1);
    vis[S]=0;
    q.push(S);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        if(x==T)return vis[x];
        for(int i=0; i<G[x].size(); i++)
        {
            int v=G[x][i];
            if(vis[v]==-1)
            {
                vis[v]=vis[x]+1;
                q.push(v);
            }
        }
    }
    return 0;
}

int main()
{
    init_prime();
    int kase;
    cin>>kase;
    while(kase--)
    {
        cin>>S>>T;
        cout<<bfs()<<endl;
    }
    return 0;
}

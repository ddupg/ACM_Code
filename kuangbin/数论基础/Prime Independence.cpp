#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 40005;
const int INF = 0x3f3f3f3f;

inline int readint()
{
    char c=getchar();
    while(!isdigit(c))c=getchar();
    int x=0;
    while(isdigit(c))
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}

int n;
vector<int> prime;
int num[MAXN], p[2][500000+10];

vector<int>G[MAXN], v[MAXN];
int uN;
int Mx[MAXN],My[MAXN];
int dx[MAXN],dy[MAXN];
int dis;
bool used[MAXN];

void init()
{
    for(int i=0; i<=n; i++)
        v[i].clear(), G[i].clear();
}

bool SearchP()
{
    queue<int>Q;
    dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for(int i = 0 ; i < uN; i++)
        if(Mx[i] == -1)
        {
            Q.push(i);
            dx[i] = 0;
        }
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if(dx[u] > dis) break;
        int sz = G[u].size();
        for(int i = 0; i < sz; i++)
        {
            int v = G[u][i];
            if(dy[v] == -1)
            {
                dy[v] = dx[u] + 1;
                if(My[v] == -1)dis = dy[v];
                else
                {
                    dx[My[v]] = dy[v] + 1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis != INF;
}
bool DFS(int u)
{
    int sz = G[u].size();
    for(int i = 0; i < sz; i++)
    {
        int v = G[u][i];
        if(!used[v] && dy[v] == dx[u] + 1)
        {
            used[v] = true;
            if(My[v] != -1 && dy[v] == dis) continue;
            if(My[v] == -1 || DFS(My[v]))
            {
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch()
{
    int res = 0;
    memset(Mx, -1, sizeof(Mx));
    memset(My, -1, sizeof(My));
    while(SearchP())
    {
        memset(used, false, sizeof(used));
        for(int i = 0; i < uN; i++)
            if(Mx[i] == -1 && DFS(i))
                res++;
    }
    return res;
}

int main()
{
    bool a[500000+100]= {0};
    for(int i=2; i*i<=500000; i++)
        for(int j=i*i; j<=500000; j+=i)
            a[j]=1;
    for(int i=2; i<=500000; i++)
        if(!a[i])
            prime.push_back(i);
    int T=readint(), kase=0;
    while(T--)
    {
        n=readint();
        uN=n;
        init();
        memset(p, 0, sizeof p);
        for(int i=1; i<=n; i++)
        {
            num[i]=readint();
            int t=num[i], cnt=0;
            for(int j=0; prime[j]*prime[j]<=t; j++)
            {
                if(t%prime[j]==0)
                {
                    v[i].push_back(prime[j]);
                    while(t%prime[j]==0)
                        ++cnt, t/=prime[j];
                }
            }
            if(t>1)
            {
                v[i].push_back(t);
                ++cnt;
            }
            p[cnt&1][num[i]]=i;
        }
        for(int i=1; i<=n; i++)
        {
            if(p[0][num[i]])
            {
                for(int j=0; j<v[i].size(); j++)
                {
                    int tmp=num[i]/v[i][j];
                    if(!p[1][tmp])continue ;
                    G[i-1].push_back(p[1][tmp]-1);
                }
            }
            else
            {
                for(int j=0; j<v[i].size(); j++)
                {
                    int tmp=num[i]/v[i][j];
                    if(!p[0][tmp])continue ;
                    G[p[0][tmp]-1].push_back(i-1);
                }
            }
        }
        printf("Case %d: %d\n", ++kase, n-MaxMatch());
    }
    return 0;
}

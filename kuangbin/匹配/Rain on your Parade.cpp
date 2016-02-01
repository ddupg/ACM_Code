#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 3010;
const int oo = 0x3f3f3f3f;
vector<int> G[maxn];
int n;
int Mx[maxn],My[maxn];
int dx[maxn],dy[maxn];
int dis;
bool used[maxn];
bool SearchP()
{
    queue<int>Q;
    dis = oo;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for(int i = 0 ; i < n; i++)
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
    return dis != oo;
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
        for(int i = 0; i < n; i++)
            if(Mx[i] == -1 && DFS(i))
                res++;
    }
    return res;
}

struct Node
{
    int x, y;
} p[maxn], s[maxn];
int v[maxn];

int readint()
{
    int x=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))
        x=x*10+c-'0', c=getchar();
    return x;
}

double dist(Node a, Node b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int main()
{
    int T=readint(), kase=0, tm, m;
    while(T--)
    {
        tm=readint();
        n=readint();
        for(int i=0; i<n; i++)G[i].clear();
        for(int i=0; i<n; i++)
            p[i].x=readint(), p[i].y=readint(), v[i]=readint();
        m=readint();
        for(int i=0; i<m; i++)
        {
            s[i].x=readint(), s[i].y=readint();
            for(int j=0; j<n; j++)
                if(dist(p[j], s[i])/v[i]<=tm)
                    G[j].push_back(i);
        }
        printf("Scenario #%d:\n%d\n\n", ++kase, MaxMatch());
    }
    return 0;
}

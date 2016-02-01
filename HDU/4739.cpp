#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

struct Point
{
    int x, y;
    bool operator < (const Point & a)const
    {
        return y<a.y || (y==a.y && x<a.x);
    }
} p[25];

struct Node
{
    int a, b, c, d;
    Node(int a, int b, int c, int d):a(a), b(b), c(c), d(d) {}
};

vector<Node> v;

int judge(int a, int b, int c, int d)
{
    if(p[a].y==p[b].y && p[b].x>=p[a].x)
    {
        int k=p[b].x-p[a].x;
        if(p[a].x==p[c].x && p[a].y==p[c].y-k && p[a].x==p[d].x-k && p[a].y==p[d].y-k)
            return 1;
        return 0;
    }
    return 0;
}

int ans=0, vis[25];

void dfs(int u, int deep)
{
    ans=max(deep, ans);
    for(int i=u+1; i<v.size(); i++)
    {
        if(!vis[v[i].a] && !vis[v[i].b] && !vis[v[i].c] && !vis[v[i].d])
        {
            vis[v[i].a]=vis[v[i].b]=vis[v[i].c]=vis[v[i].d]=1;
            dfs(i, deep+1);
            vis[v[i].a]=vis[v[i].b]=vis[v[i].c]=vis[v[i].d]=0;
        }
    }
}

int main()
{
    int n;
    while(scanf("%d", &n) && n!=-1)
    {
        for(int i=0; i<n; i++)
            scanf("%d%d", &p[i].x, &p[i].y);
        sort(p, p+n);

        v.clear();
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                for(int k=j+1; k<n; k++)
                    for(int l=k+1; l<n; l++)
                        if(judge(i, j, k, l))
                            v.push_back(Node(i, j, k, l));
        ans=0;
        memset(vis, 0, sizeof(vis));
        dfs(-1, 0);
        printf("%d\n", ans*4);
    }

    return 0;
}

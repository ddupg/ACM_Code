#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=100;

struct TowSAT
{
    int n;
    vector<int> G[maxn<<1];
    bool mark[maxn<<1];
    int S[maxn<<1], c;

    bool dfs(int x)
    {
        if(mark[x^1])return false;
        if(mark[x])return true;
        mark[x]=true;
        S[c++]=x;
        for(int i=0; i<G[x].size(); i++)
            if(!dfs(G[x][i]))return false;
        return true;
    }

    void init(int n)
    {
        this->n=n;
        for(int i=0; i<n*2; i++)
            G[i].clear();
        memset(mark, 0, sizeof mark);
    }

    void add_clause(int x, int xval, int y, int yval)
    {
        x=x*2+xval;
        y=y*2+yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool solve()
    {
        for(int i=0; i<n*2; i+=2)
            if(!mark[i] && !mark[i+1])
            {
                c=0;
                if(!dfs(i))
                {
                    while(c>0)mark[S[--c]]=false;
                    if(!dfs(i+1))return false;
                }
            }
        return true;
    }
} solver;

int getid()
{
    char s[10];
    scanf("%s", s);
    int i, ans=0;
    for(i=0; isdigit(s[i]); i++)
        ans=ans*10+s[i]-'0';
    return s[i]=='h'?ans*2+1:ans*2;
}

int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        solver.init(n*2);
        solver.mark[1]=true;
        for(int i=0; i<n*2; i+=2)
        {
            solver.add_clause(i, 0, i+1, 0);
            solver.add_clause(i, 1, i+1, 1);
        }
        while(m--)
        {
            int u=getid(), v=getid();
            solver.add_clause(u, 1, v, 1);
        }
        if(solver.solve())
        {
            bool first=true;
            for(int i=2; i<n*2; i+=2)
            {
                if(!first)putchar(' ');
                first=false;
                printf("%d%c", i>>1, solver.mark[2*i+1]?'w':'h');
            }
            puts("");
        }
        else puts("bad luck");
    }
    return 0;
}

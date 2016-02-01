#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
#define fst first
#define snd second
using namespace std;
typedef pair<int, int> pii;
const int maxn=100000+100;

struct TwoSAT
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

    void add(int x, int xval, int y, int yval)
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

int n, A, B;
int a[maxn];
map<int, int> mp;

int main()
{
    scanf("%d%d%d", &n, &A, &B);
    solver.init(n);
    for(int i=0, t; i<n; i++)
    {
        scanf("%d", a+i);
        mp[a[i]]=i;
    }

    for(int i=0; i<n; i++)
    {
        int ap=A-a[i], bp=B-a[i];
        if(mp.find(ap)==mp.end())
            solver.add(i, 1, i, 1);
        else
            solver.add(i, 1, mp[ap], 0);
        if(mp.find(bp)==mp.end())
            solver.add(i, 0, i, 0);
        else
            solver.add(i, 0, mp[bp], 1);
    }

    if(!solver.solve())
    {
        puts("NO");
        return 0;
    }
    puts("YES");
    for(int i=0; i<(n<<1); i+=2)
    {
        if(i)putchar(' ');
        printf("%d", solver.mark[i]^1);
    }
    puts("");
    return 0;
}

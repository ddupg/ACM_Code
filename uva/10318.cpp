#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int n, m, kase=0;
char op[5][5];
bool g[7][7], lit[30];
vector<int> ans;
int dx[]= {0, 0, 0, 1, 1, 1, -1, -1, -1};
int dy[]= {0, 1, -1, 0, 1, -1, 0, 1, -1};

void getPos(int id, int& x, int& y)
{
    x=(id+m-1)/m;
    y=id-(x-1)*m;
}

void dfs(int pos, int cnt)
{
    if(pos>m*n)
    {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if(!g[i][j])return ;

        if(cnt<ans.size())
        {
            ans.clear();
            for(int i=1; i<=m*n; i++)if(lit[i])
                ans.push_back(i);
        }
        return ;
    }

    if(pos>m*2)
    {
        for(int i=1; i<=m; i++)
            if(!g[(pos-1)/m-1][i])return ;
    }

    dfs(pos+1, cnt);

    int x, y;
    getPos(pos, x, y);
    for(int j=0; j<9; j++)
    {
        if(op[1+dx[j]][1+dy[j]]!='*')continue ;
        int nx=x+dx[j], ny=y+dy[j];
        g[nx][ny]^=1;
    }
    lit[pos]=true;
    dfs(pos+1, cnt+1);
    for(int j=0; j<9; j++)
    {
        if(op[1+dx[j]][1+dy[j]]!='*')continue ;
        int nx=x+dx[j], ny=y+dy[j];
        g[nx][ny]^=1;
    }
    lit[pos]=false;
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n)
    {
        ans.resize(100);
        memset(g, 0, sizeof g);
        memset(lit, 0, sizeof lit);
        for(int i=0; i<3; i++)
            scanf("%s", op[i]);

        printf("Case #%d\n", ++kase);
        dfs(1, 0);
        if(ans.size()==100)
            puts("Impossible.");
        else
            for(int i=0; i<ans.size(); i++)
                printf("%d%c", ans[i], i==ans.size()-1?'\n':' ');
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

bool g[20][20], t[20][20], res[20][20];
int tt[20][20];
int n, m, ans;
void change(int i, int j)
{
    tt[i][j]=!tt[i][j];
    tt[i+1][j]=!tt[i+1][j];
    tt[i-1][j]=!tt[i-1][j];
    tt[i][j+1]=!tt[i][j+1];
    tt[i][j-1]=!tt[i][j-1];
}

void judge(int x)
{
    int cnt=0;
    memset(t, 0, sizeof(t));
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            tt[i][j]=g[i][j];

    for(int i=1; i<=m; i++)
    {
        t[1][i]=x&1;
        x=x>>1;
        if(t[1][i])
        {
            change(1, i);
            cnt++;
        }
    }

    for(int i=2; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(tt[i-1][j])
            {
                t[i][j]=1;
                change(i, j);
                cnt++;
                if(cnt>ans)
                    return ;
            }
    int ok=1;
    for(int i=1; i<=m; i++)
        if(tt[n][i])
        {
            ok=0;
            break;
        }
    if(ok && cnt<ans)
    {
        ans=cnt;
        memcpy(res, t, sizeof(t));
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            cin>>g[i][j];
    ans=1<<30;
    for(int i=0; i<=(1<<m)-1; i++)
        judge(i);
    if(ans==1<<30)
        cout<<"IMPOSSIBLE"<<endl;
    else
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
            cout<<res[i][j]<<(j==m?'\n':' ');
    }
    return 0;
}

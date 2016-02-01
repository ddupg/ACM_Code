#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=300;
const int oo=0x3f3f3f3f;

int nx, ny;
int g[maxn][maxn];
int link[maxn], lx[maxn], ly[maxn];
int slack[maxn];
bool visx[maxn], visy[maxn];

bool dfs(int x)
{
    visx[x]=1;
    for(int y=0; y<ny; y++)
    {
        if(visy[y])continue ;
        int tmp=lx[x]+ly[y]-g[x][y];
        if(tmp==0)
        {
            visy[y]=1;
            if(link[y]==-1 || dfs(link[y]))
            {
                link[y]=x;
                return 1;
            }
        }
        else if(slack[y]>tmp)
            slack[y]=tmp;
    }
}
int KM()
{
    memset(link, -1, sizeof link);
    memset(ly, 0, sizeof ly);
    for(int i=0; i<nx; i++)
    {
        lx[i]=-oo;
        for(int j=0; j<ny; j++)
            if(g[i][j]>lx[i])
                lx[i]=g[i][j];
    }
    for(int x=0; x<nx; x++)
    {
        for(int i=0; i<ny; i++)
            slack[i]=oo;
        while(true)
        {
            memset(visx, 0, sizeof visx);
            memset(visy, 0, sizeof visy);
            if(dfs(x))break;
            int d=oo;
            for(int i=0; i<ny; i++)
                if(!visy[i] && d>slack[i])
                    d=slack[i];
            for(int i=0; i<nx; i++)
                if(visx[i])
                    lx[i]-=d;
            for(int i=0; i<ny; i++)
            {
                if(visy[i])ly[i]+=d;
                else slack[i]-=d;
            }
        }
    }
    int ans=0;
    for(int i=0; i<ny; i++)
        if(link[i]!=-1)
            ans+=g[link[i]][i];
    return ans;
}

int main()
{

    return 0;
}

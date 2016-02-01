#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

vector<int> g[20];

int d[1<<16], pre[1<<16], S, from[1<<16], to[1<<16], p;
int s[6]= {0, 1, 2, 4, 7, 11}, e[6]= {0, 1, 3, 6, 10, 15};
void init()
{

    for(int i=1; i<=5; i++)
        for(int j=s[i]; j<=e[i]; j++)
        {
            for(int k=j+1; k<=e[i]; k++)
                g[j].push_back(k), g[k].push_back(j);
            for(int k=1, p=j+i; k<=5-i; p+=++k+i-1)
            {
                g[j].push_back(p), g[p].push_back(j);
                g[j].push_back(p+k), g[p+k].push_back(j);
            }
        }
}

void printAns(int y)
{
    vector< pair<int, int> > ans;
    for(; y!=S; y=pre[y])
        ans.push_back(make_pair(from[y], to[y]));
    printf("%d\n", ans.size());
    for(int i=ans.size()-1; i>=0; i--)
        printf("%d %d%c", ans[i].first, ans[i].second, i?' ':'\n');
}



void getPos(int x, int& a, int& b, int& c)
{
    for(int i=1; i<=5; i++)
        if(x>=s[i] && x<=e[i])
        {
            a=i, b=x-s[i]+1, c=e[i]-x+1;
            return ;
        }

}

bool judge(int x, int y, int z)
{
    if(x>y) swap(x, y);
    int ax, bx, cx, ay, by, cy, az, bz, cz;
    getPos(x, ax, bx, cx);
    getPos(y, ay, by, cy);
    getPos(z, az, bz, cz);
    if(ax==ay && ay==az)return true;
    if(bx==by && by==bz)return true;
    if(cx==cy && cy==cz)return true;
    return false;
}

void bfs(int s)
{
    S=s;
    memset(d, -1, sizeof d);
    memset(pre, -1, sizeof pre);
    d[S]=0;
    queue<int> q;
    q.push(S);
    int c=0;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        int cnt=0;
        for(int i=1; i<=15; i++)
            if(1<<i&x)cnt++;
        if(cnt==1)
        {
            if(to[x]==p)
            {
                printAns(x);
                return ;
            }
            continue ;
        }
        for(int i=1; i<=15; i++)if(1<<i&x)
                for(int j=0; j<g[i].size(); j++)if(!(1<<g[i][j]&x))
                    {
                        int pos=g[i][j], cnt=0;
                        int y=x^(1<<i)^(1<<pos);
                        for(int k=min(i, pos)+1; k<max(i, pos); k++)
                            if(judge(i, pos, k) && (y&(1<<k)))
                                y^=(1<<k), cnt++;
                        if(cnt && d[y]==-1)
                        {
                            d[y]=d[x]+1;
                            pre[y]=x;
                            from[y]=i;
                            to[y]=pos;
                            q.push(y);
                        }
                    }
    }
}

int main()
{
    init();
    int Kase;
    scanf("%d", &Kase);
    while(Kase--)
    {
        scanf("%d", &p);
        bfs(((1<<15)-1)<<1^(1<<p));
    }
    return 0;
}


//#include <cstdio>
//int main()
//{
//    int T;
//    scanf("%d", &T);
//    while(T--)
//    {
//        int n;
//        scanf("%d", &n);
//        switch (n)
//        {
//        case 1:
//            puts("9");
//            puts("4 1 6 4 11 2 14 11 15 6 1 10 10 7 11 4 4 1");
//            break;
//        case 2:
//            puts("9");
//            puts("7 2 1 4 10 1 14 2 1 7 11 14 15 13 13 4 7 2");
//            break;
//        case 3:
//            puts("9");
//            puts("10 3 1 6 7 1 12 3 1 10 14 12 11 13 13 6 15 3");
//            break;
//        case 4:
//            puts("9");
//            puts("1 4 6 1 13 6 10 3 11 13 3 12 15 11 11 2 1 4");
//            break;
//        case 5:
//            puts("10");
//            puts("12 5 3 8 15 12 6 13 7 9 1 7 10 8 7 9 11 14 14 5");
//            break;
//        case 6:
//            puts("9");
//            puts("1 6 4 1 13 4 7 2 15 13 2 14 11 15 15 3 1 6");
//            break;
//        case 7:
//            puts("9");
//            puts("1 7 6 1 11 4 9 7 14 11 11 2 15 6 6 4 1 7");
//            break;
//        case 8:
//            puts("10");
//            puts("3 8 12 5 15 3 13 6 1 10 2 9 11 2 14 5 2 9 10 8");
//            break;
//        case 9:
//            puts("10");
//            puts("2 9 11 2 12 5 3 8 13 4 1 7 14 5 15 3 3 8 7 9");
//            break;
//        case 10:
//            puts("9");
//            puts("1 10 4 1 11 4 4 6 12 5 10 8 15 12 12 3 1 10");
//            break;
//        case 11:
//            puts("9");
//            puts("4 11 1 4 10 1 14 2 1 7 11 14 15 13 13 4 4 11");
//            break;
//        case 12:
//            puts("9");
//            puts("14 12 2 14 7 2 1 4 15 13 3 15 11 14 4 13 15 12");
//            break;
//        case 13:
//            puts("9");
//            puts("4 13 1 4 11 2 13 11 15 13 2 14 3 15 15 12 11 13");
//            break;
//        case 14:
//            puts("9");
//            puts("11 14 2 11 3 12 10 3 1 6 11 13 15 12 6 13 12 14");
//            break;
//        case 15:
//            puts("9");
//            puts("6 15 1 6 7 1 12 3 1 10 15 12 11 13 13 6 6 15");
//            break;
//        default:
//            puts("IMPOSSIBLE");
//        }
//    }
//    return 0;
//}

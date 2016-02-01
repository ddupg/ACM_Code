#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=110;
int vis[maxn][maxn][maxn], T, A, B, C;

struct Node
{
    int a, b, c;
    Node(int a=0, int b=0, int c=0):a(a), b(b), c(c){}
}q[1001000];

int bfs()
{
    mem(vis, -1);
    int T=A>>1;
    vis[A][0][0]=0;
    int head=0, tail=1;
    q[0]=Node(A, 0, 0);
    while(head<tail)
    {
        Node x=q[head++];
        if((x.a==T && x.b==T) || (x.a==T && x.c==T))
            return vis[x.a][x.b][x.c];
        int t=min(x.a, B-x.b);
        if(t && vis[x.a-t][x.b+t][x.c]==-1)
        {
            vis[x.a-t][x.b+t][x.c]=vis[x.a][x.b][x.c]+1;
            q[tail++]=Node(x.a-t, x.b+t, x.c);
        }
        t=min(x.a, C-x.c);
        if(t && vis[x.a-t][x.b][x.c+t]==-1)
        {
            vis[x.a-t][x.b][x.c+t]=vis[x.a][x.b][x.c]+1;
            q[tail++]=Node(x.a-t, x.b, x.c+t);
        }
        t=min(x.b, A-x.a);
        if(t && vis[x.a+t][x.b-t][x.c]==-1)
        {
            vis[x.a+t][x.b-t][x.c]=vis[x.a][x.b][x.c]+1;
            q[tail++]=Node(x.a+t, x.b-t, x.c);
        }
        t=min(x.b, C-x.c);
        if(t && vis[x.a][x.b-t][x.c+t]==-1)
        {
            vis[x.a][x.b-t][x.c+t]=vis[x.a][x.b][x.c]+1;
            q[tail++]=Node(x.a, x.b-t, x.c+t);
        }
        t=min(x.c, A-x.a);
        if(t && vis[x.a+t][x.b][x.c-t]==-1)
        {
            vis[x.a+t][x.b][x.c-t]=vis[x.a][x.b][x.c]+1;
            q[tail++]=Node(x.a+t, x.b, x.c-t);
        }
        t=min(x.c, B-x.b);
        if(t && vis[x.a][x.b+t][x.c-t]==-1)
        {
            vis[x.a][x.b+t][x.c-t]=vis[x.a][x.b][x.c]+1;
            q[tail++]=Node(x.a, x.b+t, x.c-t);
        }
    }
    return -1;
}

int main()
{
    while(~scanf("%d%d%d", &A, &B, &C) && A+B+C)
    {
        if(A&1)
        {
            puts("NO");
            continue ;
        }
        int ans=bfs();
        if(~ans)
            printf("%d\n", ans);
        else puts("NO");
    }
    return 0;
}

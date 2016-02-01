#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=110;
int vis[maxn][maxn], A, B, C, E;
struct Node
{
    int a, b, fa;
    char op[15];
    Node(int a=0, int b=0):a(a), b(b){}
}q[10010];

int bfs()
{
    mem(vis, -1);
    vis[0][0]=0;
    int head=0, tail=0;
    q[tail++]=Node(0, 0);
    q[0].fa=-1;
    while(head<tail)
    {
        Node x=q[head];
        if(x.a==C || x.b==C)
        {
            E=head;
            return vis[x.a][x.b];
        }
        char s[15];
        if(x.a>0 && vis[0][x.b]==-1)
        {
            vis[0][x.b]=vis[x.a][x.b]+1;
            q[tail]=Node(0, x.b);
            q[tail].fa=head;
            strcpy(q[tail].op, "DROP(1)");
            tail++;
        }
        if(x.b>0 && vis[x.a][0]==-1)
        {
            vis[x.a][0]=vis[x.a][x.b]+1;
            q[tail]=Node(x.a, 0);
            q[tail].fa=head;
            strcpy(q[tail].op, "DROP(2)");
            tail++;
        }
        if(x.a<A && vis[A][x.b]==-1)
        {
            vis[A][x.b]=vis[x.a][x.b]+1;
            q[tail]=Node(A, x.b);
            q[tail].fa=head;
            strcpy(q[tail].op, "FILL(1)");
            tail++;
        }
        if(x.b<B && vis[x.a][B]==-1)
        {
            vis[x.a][B]=vis[x.a][x.b]+1;
            q[tail]=Node(x.a, B);
            q[tail].fa=head;
            strcpy(q[tail].op, "FILL(2)");
            tail++;
        }
        int t=min(x.a, B-x.b);
        if(t && vis[x.a-t][x.b+t]==-1)
        {
            vis[x.a-t][x.b+t]=vis[x.a][x.b]+1;
            q[tail]=Node(x.a-t, x.b+t);
            q[tail].fa=head;
            strcpy(q[tail].op, "POUR(1,2)");
            tail++;
        }
        t=min(A-x.a, x.b);
        if(t && vis[x.a+t][x.b-t]==-1)
        {
            vis[x.a+t][x.b-t]=vis[x.a][x.b]+1;
            q[tail]=Node(x.a+t, x.b-t);
            q[tail].fa=head;
            strcpy(q[tail].op, "POUR(2,1)");
            tail++;
        }
        head++;
    }
    return -1;
}

void print_road(int x)
{
    if(!x)return ;
    print_road(q[x].fa);
    puts(q[x].op);
}

int main()
{
    while(~scanf("%d%d%d", &A, &B, &C))
    {
        int ans=bfs();
        if(~ans)
        {
            printf("%d\n", ans);
            print_road(E);
        }
        else puts("impossible");
    }
    return 0;
}

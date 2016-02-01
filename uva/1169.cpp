#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int maxn=100000+100;

int n, c, d[maxn], dist[maxn], tw[maxn], x[maxn], y[maxn], w[maxn];
int q[maxn];

int func(int i)
{
    return d[i]+abs(x[i+1])+abs(y[i+1])-dist[i+1];
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &c, &n);
        dist[0]=tw[0]=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d%d", x+i, y+i, w+i);
            tw[i]=tw[i-1]+w[i];
            dist[i]=dist[i-1]+abs(x[i]-x[i-1])+abs(y[i]-y[i-1]);
        }
        int front=1, rear=1;
        for(int i=1; i<=n; i++)
        {
            while(front<=rear && tw[i]-tw[q[front]]>c)
                front++;
            d[i]=func(q[front])+dist[i]+abs(x[i])+abs(y[i]);
            while(front<=rear && func(i) <= func(q[rear]))
                rear--;
            q[++rear]=i;
        }
        printf("%d\n", d[n]);
        if(T)puts("");
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int maxn=1010;

int pre[maxn][maxn], order[maxn][maxn], next[maxn];
int hus[maxn], wife[maxn];
queue<int> q;

void engage(int man, int woman)
{
    int m=hus[woman];
    if(m)
    {
        wife[m]=0;
        q.push(m);
    }
    wife[man]=woman;
    hus[woman]=man;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
                scanf("%d", pre[i]+j);
            next[i]=1;
            wife[i]=0;
            q.push(i);
        }
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                int x;
                scanf("%d", &x);
                order[i][x]=j;
            }
            hus[i]=0;
        }

        while(!q.empty())
        {
            int man=q.front();
            q.pop();
            int woman=pre[man][next[man]++];
            if(!hus[woman]) engage(man, woman);
            else if(order[woman][man]<order[woman][hus[woman]])
                engage(man, woman);
            else q.push(man);
        }
        while(!q.empty())q.pop();
        for(int i=1; i<=n; i++)
            printf("%d\n", wife[i]);
        if(T)
            puts("");
    }
    return 0;
}

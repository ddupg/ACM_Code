#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=30;
int n, h, f[maxn], d[maxn], t[maxn], ans, cnt[maxn];

struct Node
{
    int fish, id;
    Node(int f, int i):fish(f), id(i){}
    bool operator < (const Node a)const
    {
        return fish<a.fish || (fish==a.fish && id>a.id);
    }
};

void solve(int pos)
{
    int tmp[maxn]={0}, T=h, res=0;
    priority_queue<Node> q;
    while(!q.empty())q.pop();
    for(int i=1; i<=pos; i++)
    {
        T-=t[i-1];
        q.push(Node(f[i], i));
    }
    if(T<=0)return ;
    while(T--)
    {
        Node x=q.top();
        q.pop();
        res+=x.fish;
        ++tmp[x.id];
        q.push(Node(max(x.fish-d[x.id], 0), x.id));
    }
    if(res>ans)
    {
        ans=res;
        for(int i=1; i<=n; i++)
            cnt[i]=tmp[i];
    }
}

int main()
{
    int kase=0;
    while(~scanf("%d", &n) && n)
    {
        scanf("%d", &h);
        h*=12;
        for(int i=1; i<=n; i++)
            scanf("%d", f+i);
        for(int i=1; i<=n; i++)
            scanf("%d", d+i);
        for(int i=1; i<n; i++)
            scanf("%d", t+i);
        ans=0;
        memset(cnt, 0, sizeof(cnt));
        cnt[1]=h;
        for(int i=1; i<=n; i++)
            solve(i);
        if(kase++)puts("");
        printf("%d", cnt[1]*5);
        for(int i=2; i<=n; i++)
            printf(", %d", cnt[i]*5);
        printf("\nNumber of fish expected: %d\n", ans);
    }
    return 0;
}

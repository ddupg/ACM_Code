#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define mem(a, val) memset((a), (val), sizeof a)
#define pb push_back
using namespace std;
const int maxn=550;
const int maxm=1000000+100;

struct Node
{
    int h;
    char music[110], sport[110];
} node[maxn];

struct Edge
{
    int to, next;
} edge[maxm];
int n, link[maxn], tot, head[maxn];
vector<int> boy, girl;
bool used[maxn];

void init()
{
    tot=0;
    mem(head, -1);
    boy.clear();
    girl.clear();
}

void AddEdge(int u, int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

bool match(int u)
{
    for(int i=head[u]; ~i; i=edge[i].next)
    {
        int v=edge[i].to;
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1 || match(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    mem(link, -1);
    int ans=0;
    for(int i=0; i<boy.size(); i++)
    {
        mem(used, 0);
        ans+=match(i);
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        char sex[3];
        for(int i=0; i<n; i++)
        {
            scanf("%d %s %s %s", &node[i].h, sex, node[i].music, node[i].sport);
            if(sex[0]=='M')
                boy.pb(i);
            else girl.pb(i);
        }
        for(int i=0; i<boy.size(); i++)
            for(int j=0; j<girl.size(); j++)
            {
                int u=boy[i], v=girl[j];
                if(abs(node[u].h-node[v].h)<=40 && !strcmp(node[u].music, node[v].music) && strcmp(node[u].sport, node[v].sport))
                    AddEdge(i, j);
            }
        printf("%d\n", n-hungary());
    }
    return 0;
}

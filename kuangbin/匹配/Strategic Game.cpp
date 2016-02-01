#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1550;
int N;
int Match[MAXN];
bool InQueue[MAXN],InPath[MAXN],InBlossom[MAXN];
int Head,Tail;
int Queue[MAXN];
int Start,Finish;
int NewBase;
int Father[MAXN],Base[MAXN];
int Count;

struct Edge
{
    int v, nxt;
} edge[2*MAXN*MAXN];

int head[MAXN], tot;

void init()
{
    memset(head, -1, sizeof head);
    tot=0;
}
void AddEdge(int u, int v)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}

void CreateGraph()
{
    init();
    for(int i=0; i<N; i++)
    {
        int u, v, m;
        scanf("%d:(%d)", &u, &m);
        while(m--)
        {
            scanf("%d", &v);
            AddEdge(u+1, v+1);
            AddEdge(v+1, u+1);
        }
    }
}
void Push(int u)
{
    Queue[Tail] = u;
    Tail++;
    InQueue[u] = true;
}
int Pop()
{
    int res = Queue[Head];
    Head++;
    return res;
}
int FindCommonAncestor(int u,int v)
{
    memset(InPath,false,sizeof(InPath));
    while(true)
    {
        u = Base[u];
        InPath[u] = true;
        if(u == Start) break;
        u = Father[Match[u]];
    }
    while(true)
    {
        v = Base[v];
        if(InPath[v])break;
        v = Father[Match[v]];
    }
    return v;
}
void ResetTrace(int u)
{
    int v;
    while(Base[u] != NewBase)
    {
        v = Match[u];
        InBlossom[Base[u]] = InBlossom[Base[v]] = true;
        u = Father[v];
        if(Base[u] != NewBase) Father[u] = v;
    }
}
void BloosomContract(int u,int v)
{
    NewBase = FindCommonAncestor(u,v);
    memset(InBlossom,false,sizeof(InBlossom));
    ResetTrace(u);
    ResetTrace(v);
    if(Base[u] != NewBase) Father[u] = v;
    if(Base[v] != NewBase) Father[v] = u;
    for(int tu = 1; tu <= N; tu++)
        if(InBlossom[Base[tu]])
        {
            Base[tu] = NewBase;
            if(!InQueue[tu]) Push(tu);
        }
}
void FindAugmentingPath()
{
    memset(InQueue,false,sizeof(InQueue));
    memset(Father,0,sizeof(Father));
    for(int i = 1; i <= N; i++)
        Base[i] = i;
    Head = Tail = 1;
    Push(Start);
    Finish = 0;
    while(Head < Tail)
    {
        int u = Pop();
        for(int i=head[u]; ~i; i=edge[i].nxt)
        {
            int v=edge[i].v;
            if((Base[u] != Base[v]) && (Match[u] != v))
            {
                if((v == Start) || ((Match[v] > 0) && Father[Match[v]] > 0))
                    BloosomContract(u,v);
                else if(Father[v] == 0)
                {
                    Father[v] = u;
                    if(Match[v] > 0)
                        Push(Match[v]);
                    else
                    {
                        Finish = v;
                        return;
                    }
                }
            }
        }
    }
}
void AugmentPath()
{
    int u,v,w;
    u = Finish;
    while(u > 0)
    {
        v = Father[u];
        w = Match[v];
        Match[v] = u;
        Match[u] = v;
        u = w;
    }
}
void Edmonds()
{
    memset(Match,0,sizeof(Match));
    for(int u = 1; u <= N; u++)
        if(Match[u] == 0)
        {
            Start = u;
            FindAugmentingPath();
            if(Finish > 0)AugmentPath();
        }
}
void PrintMatch()
{
    Count = 0;
    for(int u = 1; u <= N; u++)
        if(Match[u] > 0)
            Count++;
    printf("%d\n",Count>>1);
}
int main()
{
    while(~scanf("%d",&N))
    {
        CreateGraph();
        Edmonds();
        PrintMatch();
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

struct Node
{
    int a, b;
    bool operator < (const Node x)const
    {
        return b<x.b || (b==x.b && a<x.a);
    }
} nd[800100];

int n;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%d%d", &nd[i].a, &nd[i].b);
        sort(nd, nd+n);
        int st=0;
        priority_queue<int> q;
        for(int i=0; i<n; i++)
        {
            if(st+nd[i].a<=nd[i].b)
            {
                q.push(nd[i].a);
                st+=nd[i].a;
            }
            else if(!q.empty() && q.top()>nd[i].a && st-q.top()+nd[i].a<=nd[i].b)
            {
                st=st-q.top()+nd[i].a;
                q.pop();
                q.push(nd[i].a);
            }
        }
        printf("%d\n", q.size());
        if(T)puts("");
    }
    return 0;
}

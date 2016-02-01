#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=110;

struct Build
{
    int x, y, wei, len, hei, id;
    bool operator < (const Build a)const
    {
        return x<a.x || (x==a.x && y<a.y);
    }
} b[maxn];
int n;

bool judge(int x)
{
    vector<pair<int, int> > v;
    for(int i=0; i<n; i++)
        if(i!=x && b[i].y<b[x].y && b[i].hei>=b[x].hei)
            v.push_back(make_pair(b[i].x, b[i].x+b[i].wei));
    if(!v.size())return true;
    int L=b[x].x, t;
    for(int i=0, j=0; i<v.size(); i++)
    {
        t=L;
        for(; j<v.size(); j++)
        {
            if(v[j].first<=L)
                t=max(t, v[j].second);
            else break;
        }
        L=t;
        if(L>=b[x].x+b[x].wei)return false;
    }
    return L<b[x].x+b[x].wei;
}

int main()
{
    int kase=0;
    while(~scanf("%d", &n) && n)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%d%d%d", &b[i].x, &b[i].y, &b[i].wei, &b[i].len, &b[i].hei);
            b[i].id=i+1;
        }
        sort(b, b+n);
        if(kase)puts("");
        printf("For map #%d, the visible buildings are numbered as follows:\n", ++kase);
        int first=0;
        for(int i=0; i<n; i++)if(judge(i))
        {
            if(first)putchar(' ');
            first++;
            printf("%d", b[i].id);
        }
        puts("");
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn=10000+10;

struct Ant
{
    int id, p, d;
    bool operator < (const Ant a)const
    {
        return p<a.p;
    }
} before[maxn], after[maxn];

const char dirName[][10]={"L", "Turning", "R"};

int order[maxn];

int main()
{
    int Kase, kase=0;
    scanf("%d", &Kase);
    while(Kase--)
    {
        int L, T, n;
        scanf("%d%d%d", &L, &T, &n);
        for(int i=0; i<n; i++)
        {
            int p, d;
            char c;
            scanf("%d %c", &p, &c);
            d = ( c == 'L' ? -1 : 1 );
            before[i] = Ant{i, p, d};
            after[i] = Ant{0, p+T*d, d};
        }

        sort(before, before+n);

        for(int i=0; i<n; i++)
            order[before[i].id]=i;

        sort(after, after+n);
        for(int i=0; i<n-1; i++)
            if(after[i].p==after[i+1].p)after[i].d=after[i+1].d=0;

        printf("Case #%d:\n", ++kase);
        for(int i=0; i<n; i++)
        {
            int a=order[i];
            if(after[a].p<0 || after[a].p>L)puts("Fell off");
            else printf("%d %s\n", after[a].p, dirName[after[a].d+1]);
        }
        puts("");
    }
    return 0;
}

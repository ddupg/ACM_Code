#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <cstdlib>
#include <queue>
#include <stack>
#include<cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define rep1(i,x,y) for(int i=x;i<=(int)y;i++)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;


set<int> s;
int n, k, a, m;

int size(int x)
{
    return (x+1)/(a+1);
}

int main()
{
    scanf("%d%d%d%d", &n, &k, &a, &m);
    s.insert(0);
    s.insert(n+1);
    int sz=size(n);
    for(int i=0; i<m; i++)
    {
        int x;
        scanf("%d", &x);
        set<int>::iterator it=s.lower_bound(x);
        int R= *it, L= *(--it);
        sz-=size(R-L-1);
        sz+=size(R-x-1)+size(x-L-1);
        if(sz<k)
        {
            printf("%d\n", i+1);
            return 0;
        }
        s.insert(x);
    }
    puts("-1");
    return 0;
}

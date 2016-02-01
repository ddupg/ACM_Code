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
typedef pair<LL, int> pli;

const int maxn=200020;

LL a[maxn];

int main()
{
    int n, k;
    LL ans=0, sum=0, Min=0;
    scanf("%d%d", &n, &k);
    for(int i=0; i<n; i++)
    {
        scanf("%I64d", a+i);
        Min=min(a[i], Min);
    }
    for(int i=0; i<k-1; i++)
        sum+=a[i];
    for(int l=0, r=k-1; r<n; r++, l++)
    {
        sum+=a[r];
        if(sum>=0)
        {
            LL diff=sum+1;
            ans+=diff;
            for(int i=r; i>=l && diff>0; i--)
            {
                LL t=a[i];
                a[i]-=min(diff, t-Min);
                diff-=t-a[i];
            }
            sum=-1;
        }
        sum-=a[l];
    }
    printf("%I64d\n", ans);
    for(int i=0; i<n; i++)
        printf("%I64d%c", a[i], " \n"[i==n-1]);
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ALL(a) a.begin(), a.end()
using namespace std;
const int maxn=100000+100;

int n;
vector<int> v[maxn];
int ans[500];

bool judge(int lim)
{
    for(int i=0; i<n; i++)
    {
        if(v[i].size()<lim)return 0;
        if(v[i][lim]!=v[0][lim])return 0;
    }
    return 1;
}

int main()
{
    scanf("%d", &n);
    for(int i=0 ; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        while(x)
        {
            v[i].push_back(x&1);
            x>>=1;
        }
        reverse(ALL(v[i]));
    }
    int len=1;
    for(; judge(len) && len<v[0].size(); len++);
    for(int i=0; i<n; i++)
    {
        int p=len;
        while(p<v[i].size() && !v[i][p]) p++;
        for(int j=len; j<100; j++)
        {
            if(j<=p)ans[j]+=v[i].size()-j;
            else ans[j]+=v[i].size()-p+j-p;
        }
    }
    int res=ans[len];
    for(int i=len; i<100; i++)
        res=min(ans[i], res);
    printf("%d\n", res);
    return 0;
}

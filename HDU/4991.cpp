#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
typedef long long LL;
typedef unsigned long long LLU;
using namespace std;
const int MOD=123456789;
int d[11111][111], a[11111], b[11111], n, k, cnt;

int lowbit(int x)
{
    return x&(-x);
}

int Sum(int x, int l)
{
    int res=0;
    while(x>0)
    {
        res=(res+d[x][l])%MOD;
        x-=lowbit(x);
    }
    return res;
}

void Update(int x, int l, int val)
{
    while(x<=cnt)
    {
        d[x][l]=(d[x][l]+val)%MOD;
        x+=lowbit(x);
    }
}

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        memset(d, 0, sizeof(d));
        vector<int> v;
        v.clear();
        for(int i=0; i<n; i++)
        {
            scanf("%d", &a[i]);
            v.push_back(a[i]);
        }
        sort(v.begin(), v.end());
        vector<int>::iterator it=unique(v.begin(), v.end());
        v.erase(it, v.end());

        cnt=v.size();

        map<int, int> m;
        m.clear();
        for(int i=0; i<v.size(); i++)
            m[v[i]]=i+1;
        for(int i=0; i<n; i++)
            b[i]=m[a[i]];

        Update(b[0], 1, 1);
        for(int i=1; i<n; i++)
        {
            for(int j=2; j<=k; j++)
            {
                int sum=Sum(b[i]-1, j-1);
                Update(b[i], j, sum);
            }
            Update(b[i], 1, 1);
        }
        printf("%d\n", Sum(cnt, k));
    }
    return 0;
}

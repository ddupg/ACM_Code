#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=110;
double b[maxn][maxn], p[maxn][maxn];
vector<double> v;
int n, m[maxn];

double func(double B)
{
    double ans=0;
    for(int i=0; i<n; i++)
    {
        double tmp=1e9;
        for(int j=0; j<m[i]; j++)
            if(b[i][j]>=B)
                tmp=min(tmp, p[i][j]);
        ans+=tmp;
    }
    return B/ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        v.clear();
        scanf("%d", &n);
        for(int i=0; i<n; i++)
        {
            scanf("%d", &m[i]);
            for(int j=0; j<m[i]; j++)
            {
                scanf("%lf%lf", &b[i][j], &p[i][j]);
                v.push_back(b[i][j]);
            }
        }
        sort(v.begin(), v.end());
        double ans=func(v[0]);
        for(int i=1; i<v.size(); i++)
            if(v[i]!=v[i-1])
                ans=max(ans, func(v[i]));
        printf("%.3lf\n", ans);
    }
    return 0;
}

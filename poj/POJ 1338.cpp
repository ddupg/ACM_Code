#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
    int n, m, kase=0;
    while(scanf("%d%d", &m, &n) && n+m)
    {
        priority_queue<int> q1, q2;
        bool a[1100]={0};
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            a[x]=1;
        }
        for(int i=m*n; i>0; i--)
        {
            if(a[i])q1.push(i);
            else q2.push(i);
        }
        int ans=0;
        for(int i=0; i<n; i++)
        {
            if(q1.top()>q2.top())
                ans++;
            else q2.pop();
            q1.pop();
        }
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}

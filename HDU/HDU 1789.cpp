#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <algorithm>
using namespace std;

struct Node
{
    int val, day;
    bool operator < (const Node a)const
    {
        return val>a.val || (val==a.val && day<a.day);
    }
}node[1110];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%d", &node[i].day);
        for(int i=0; i<n; i++)
            scanf("%d", &node[i].val);
        sort(node, node+n);
        set<int> s;
        int ans=0;
        for(int i=0; i<n; i++)
        {
            int flag=0;
            for(int j=node[i].day; j>=1; j--)
                if(!s.count(j))
                {
                    flag=1;
                    s.insert(j);
                    break;
                }
            if(!flag)ans+=node[i].val;
        }
        printf("%d\n", ans);
    }
    return 0;
}

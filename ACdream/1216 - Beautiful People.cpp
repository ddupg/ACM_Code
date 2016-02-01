#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define mem(a, val) memset((a), (val), sizeof(a))
#define all(a) (a).begin(), (a).end()
using namespace std;
const int maxn=100010;
int n, top, ans, d[maxn];
struct Node
{
    int x, y, id;
    bool operator < (const Node& a)
    {
        return x<a.x && y<a.y;
    }
}node[maxn], s[maxn];
int cmp(const Node& a, const Node& b)
{
    return a.x<b.x || (a.x==b.x && a.y>b.y);
}

int main()
{
    while(~scanf("%d", &n))
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d%d", &node[i].x, &node[i].y);
            node[i].id=i;
        }
        sort(node, node+n, cmp);
        top=0, ans=0;
        Node tmp;
        for(int i=0; i<n; i++)
        {
            if(!i || s[top]<node[i])
                s[++top]=node[i], d[i]=top;
            else
            {
                int cnt=lower_bound(s+1, s+1+top, node[i])-s;
                s[cnt]=node[i];
                d[i]=cnt;
            }
            if(d[i]>ans)
            {
                ans=d[i];
                tmp=node[i];
            }
        }
        printf("%d\n", ans);
        vector<int> v;
        v.push_back(tmp.id+1);
        for(int i=n-1; i>=0; i--)
            if(d[i]==ans-1 && node[i]<tmp)
            {
                v.push_back(node[i].id+1);
                --ans;
            }
        sort(all(v));
        for(int i=0; i<v.size(); i++)
            printf("%d%c", v[i], i==v.size()-1?'\n':' ');
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, b[3], d[1110];
struct Node
{
    int a, b, c;
    Node(int a, int b, int c):a(a), b(b), c(c) {};
    bool operator < (const Node aa)const
    {
        return (a>aa.a || (a==aa.a && b>aa.b));
    }
};
vector<Node> nd;

void init()
{
    nd.clear();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<3; j++)
            scanf("%d", b+j);
        sort(b, b+3);
        nd.push_back(Node(b[0], b[1], b[2]));
        nd.push_back(Node(b[0], b[2], b[1]));
        nd.push_back(Node(b[1], b[2], b[0]));
    }
}

int dp()
{
    int ans=0;
    sort(nd.begin(), nd.end());
    for(int i=0; i<nd.size(); i++)
    {
        d[i]=nd[i].c;
        for(int j=0; j<i; j++)
            if(nd[j].a>nd[i].a && nd[j].b>nd[i].b)
                d[i]=max(d[i], d[j]+nd[i].c);
        ans=max(ans, d[i]);
    }
    return ans;
}

int main()
{
    int kase=0;
    while(~scanf("%d", &n) && n)
    {
        init();
        printf("Case %d: maximum height = %d\n", ++kase, dp());
    }
    return 0;
}

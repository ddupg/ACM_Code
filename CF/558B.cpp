#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

const int maxn=1000000+100;

struct Node
{
    int cnt, l, r;
    bool operator < (const Node a) const
    {
        return cnt>a.cnt || (cnt==a.cnt && r-l<a.r-a.l);
    }
} nd[maxn];

set<int> s;

int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        int x;
        cin>>x;
        if(!s.count(x))
        {
            s.insert(x);
            nd[x].l=i;
        }
        nd[x].r=i;
        nd[x].cnt++;
    }
    sort(nd, nd+maxn);
    cout<<nd[0].l<<' '<<nd[0].r<<endl;
    return 0;
}

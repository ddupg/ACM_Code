#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
using namespace std;
const int maxn=1010;

struct Com
{
    int pri, qua;
};

int n, b, maxq, cnt;
map<string, int> id;
vector<Com> comp[maxn];

void init()
{
    for(int i=0; i<n; i++)
        comp[i].clear();
    id.clear();
    cnt=0;
}

int getid(string s)
{
    if(!id.count(s))
        return id[s]=cnt++;
    return id[s];
}

bool ok(int q)
{
    int sum=0;
    for(int i=0; i<cnt; i++)
    {
        int tmp=b+1;
        for(int j=0; j<comp[i].size(); j++)
            if(comp[i][j].qua>=q && comp[i][j].pri<tmp)
                tmp=comp[i][j].pri;
        if(tmp>b)return false;
        sum+=tmp;
        if(sum>b)return false;
    }
    return sum<=b;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &b);
        init();
        maxq=0;
        for(int i=0; i<n; i++)
        {
            char s1[100], s2[100];
            int pri, qua;
            scanf("%s %s %d %d", s1, s2, &pri, &qua);
            maxq=max(maxq, qua);
            comp[getid(s1)].push_back(Com{pri, qua});
        }

        int L=0, R=maxq;
        while(L<R)
        {
            int mid=L+(R-L+1)/2;
            if(ok(mid))
                L=mid;
            else R=mid-1;
        }
        printf("%d\n", L);
    }
    return 0;
}

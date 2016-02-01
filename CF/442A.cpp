#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n, g[15], cnt;
char s[5];
vector<pair<int, int> > v;

int getid(char c)
{
    if(isdigit(c))
        return c-'1';
    if(c=='R')
        return 5;
    if(c=='G')
        return 6;
    if(c=='B')
        return 7;
    if(c=='Y')
        return 8;
    if(c=='W')
        return 9;
}

bool check(int s)
{
    int t[15], c=0;
    bool vis[15]= {0};
    memcpy(t, g, sizeof t);

    for(int i=0; i<cnt; i++)
        if((1<<v[i].first&s)&&(1<<v[i].second&s))
        {
            vis[i]=true;
            c++;
            t[v[i].first]--;
            t[v[i].second]--;
        }
    for(int j=0; j<2; j++)
        for(int i=0; i<cnt; i++)
        {
            if(vis[i])continue ;
            if(((1<<v[i].second&s) && t[v[i].second]==1)||((1<<v[i].first&s) && t[v[i].first]==1))
            {
                c++;
                vis[i]=true;
                t[v[i].first]--;
                t[v[i].second]--;
            }
        }
    return c>=cnt-1;
}

int main()
{
    scanf("%d", &n);
    while(n--)
    {
        scanf("%s", s);
        v.push_back(make_pair(getid(s[0]), getid(s[1])));
    }
    sort(v.begin(), v.end());
    cnt=unique(v.begin(), v.end())-v.begin();
    for(int i=0; i<cnt; i++)
        g[v[i].first]++, g[v[i].second]++;
    int ans=10;
    for(int i=0; i<(1<<10); i++)
        if(check(i))
            ans=min(ans, __builtin_popcount(i));
    printf("%d\n", ans);
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;
const int maxn=1100;

string op;
map<string, int> id;
vector<int> G[maxn];
int tot, in[maxn], cnt;
bool flag[maxn], vis[maxn];
queue<int> que;

void init()
{
    for(int i=0; i<maxn; i++)
        G[i].clear();
    id.clear();
    tot=cnt=0;
    memset(flag, 0, sizeof flag);
    memset(vis, 0, sizeof vis);
    memset(in, 0, sizeof in);
    while(!que.empty())que.pop();
}

int getpos()
{
    for(int i=0; i<op.length(); i++)
        if(op[i]==':')
            return i;
}

int getid(string s)
{
    if(id.count(s))return id[s];
    id[s]=++tot;
    return tot;
}

void solve(int u)
{
    if(flag[u])
    {
        if(in[u]==0)
            que.push(u);
    }
    else
    {
        cnt++;
        vis[u]=true;
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            in[v]--;
            if(vis[v] || in[v])continue ;
            solve(v);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int T, kase=0;
    cin>>T;
    getline(cin, op);
    getline(cin, op);
    while(T--)
    {
        init();
        while(getline(cin, op))
        {
            if(!op[0])break;
            stringstream ss(op);
            ss>>op;
            int id1, id2;
            if(op[op.length()-2]=='*')
            {
                id1=getid(op.substr(0, op.length()-2));
                flag[id1]=true;
            }
            else id1=getid(op.substr(0, op.length()-1));
            while(ss>>op)
            {
                id2=getid(op);
                G[id2].push_back(id1);
                in[id1]++;
            }
        }
        int ans=0;
        while(cnt<tot)
        {
            for(int i=1; i<=tot; i++)
                if(!vis[i] && in[i]==0)
                    solve(i);
            if(!que.empty())
            {
                ans++;
                for(; !que.empty(); que.pop())
                    if(in[que.front()]==0)
                        flag[que.front()]=0;
            }
        }
        cout<<"Case "<<++kase<<": "<<ans<<endl;
    }
    return 0;
}

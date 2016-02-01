#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#define pb push_back
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
using namespace std;

char str[50];
bool ok;

long long build(int x, int y, string s)
{
    int c1=-1,c2=-1;
    bool flag = true;
    for(int i=x; i<y; i++) if(!isdigit(s[i]))
        {
            flag =false;
            break;
        }
    if(flag)
    {
        int num=0;
        for(int i=x; i<y; i++) num = num*10 + s[i] - '0';
        return num;
    }
    int p=0;
    for(int i=x; i<y; i++)
    {
        switch(s[i])
        {
        case '+':
        case '-': if(p==0) c1=i; break;
        case '*':
        case '/': if(p==0) c2=i; break;
        case '(': p++; break;
        case ')': p--; break;
        }
    }
    if(c1==-1) c1=c2;
    if(c1 < 0) return build(x+1,y-1,s);
    int num1 = build(x,c1,s);
    int num2 = build(c1+1,y,s);
    int res  = 0;
    switch(s[c1])
    {
    case '+' : res = num1+num2; break;
    case '-' : res = num1-num2; break;
    case '*' : res = num1*num2; break;
    case '/' : res = num1/num2; break;
    }
    return res;
}

bool judge(string& s)
{
    for(int i=1; i<s.length(); i++)if(isdigit(s[i]))
    {
        if(i==1 && s[i-1]=='0')
            return false;
        if(i!=1 && s[i-1]=='0' && !isdigit(s[i-2]))
            return false;
    }
    return true;
}

void dfs(int x, string s)
{
    if(!judge(s))return ;
    if(str[x]=='=')
    {
        if(s!="2000" && build(0, s.length(), s)==2000)
        {
            cout<<"  "<<s<<"="<<endl;
            ok=true;
        }
        return ;
    }
    dfs(x+1, s+'*'+str[x]);
    dfs(x+1, s+'+'+str[x]);
    dfs(x+1, s+'-'+str[x]);
    dfs(x+1, s+str[x]);
}

int main()
{
    int kase=0;
    while(cin>>str)
    {
        if(str[0]=='=')break;
        ok=false;
        cout<<"Problem "<<++kase<<endl;
        string s;
        dfs(1, s=str[0]);
        if(!ok)
            cout<<"  IMPOSSIBLE"<<endl;
    }
    return 0;
}

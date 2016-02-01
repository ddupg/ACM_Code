#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <set>
#include <string>
using namespace std;
const int maxn=210;
set<string> S;
char s[maxn];
int n;

int dfs(char* s1, char* s2, int deep)
{
    char tmp[maxn];
    for(int i=0; i<2*n; i++)
        tmp[i]=(i&1)?s1[i>>1]:s2[i>>1];
    tmp[2*n]='\0';
    if(!strcmp(tmp, s))
        return deep+1;
    if(S.count(tmp))
        return -1;
    S.insert(tmp);
    memcpy(s1, tmp, sizeof(char)*n);
    memcpy(s2, tmp+n, sizeof(char)*n);
    s1[n]=s2[n]='\0';
    return dfs(s1, s2, deep+1);
}

int main()
{
    int T, kase=0;
    char s1[maxn], s2[maxn];
    scanf("%d", &T);
    while(T--)
    {
        S.clear();
        scanf("%d", &n);
        scanf("%s%s%s", s1, s2, s);
        printf("%d %d\n", ++kase, dfs(s1, s2, 0));
    }
    return 0;
}

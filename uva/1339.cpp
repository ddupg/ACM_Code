#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int cnt1[30], cnt2[30];
char s1[110], s2[110];

int main()
{
    while(~scanf("%s", s1))
    {
        scanf("%s", s2);
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        for(int i=0; s1[i]; i++)
        {
            cnt1[s1[i]-'A']++;
            cnt2[s2[i]-'A']++;
        }
        sort(cnt1, cnt1+26);
        sort(cnt2, cnt2+26);
        if(!memcmp(cnt1, cnt2, 26*sizeof(int)))
            puts("YES");
        else puts("NO");
    }
    return 0;
}

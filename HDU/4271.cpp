#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxlen=100000+100;
int d[maxlen][15], n;
char s1[maxlen], s2[15][15];

int dp(char *s1, char *s2, int len1, int len2)
{
    for(int i=0; i<=len1; i++)
        for(int j=0; j<=len2; j++)
            d[i][j]=0;
    for(int i=0; i<=len2; i++)
        d[0][i]=i;
    int ans=1e9;
    for(int i=1; i<=len1; i++)
    {
        for(int j=1; j<=len2; j++)
        {
            if(s1[i-1]==s2[j-1])
                d[i][j]=d[i-1][j-1];
            else d[i][j]=1 + min( min(d[i][j-1], d[i-1][j]), d[i-1][j-1] );
            if(j==len2)ans=min(ans, d[i][j]);
        }
    }
    return ans;
}

int main()
{
    while(~scanf("%s", s1))
    {
        int len1=strlen(s1);
        if(len1<=20)
        {
            for(int i=0; i<len1; i++)
                s1[len1+i]=s1[i];
        }
        else
        {
            for(int i=0; i<20; i++)
                s1[len1++]=s1[i];
        }
        scanf("%d", &n);

        int min_len=1e9, index;
        for(int i=0; i<n; i++)
        {
            scanf("%s", s2[i]);
            int tmp=1e9;
            if(len1<=20)
            {
                for(int j=0; j<len1; j++)
                    tmp=min(tmp, dp(s1+j, s2[i], len1, strlen(s2[i])));
            }
            else
            {
                tmp=min(tmp, dp(s1, s2[i], len1, strlen(s2[i])));
            }
            if(tmp<min_len || (tmp==min_len && strcmp(s2[i], s2[index])<0))
            {
                min_len=tmp;
                index=i;
            }
        }
        printf("%s %d\n", s2[index], min_len);
    }
    return 0;
}

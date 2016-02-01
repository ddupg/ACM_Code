#include <bits/stdc++.h>
using namespace std;

char str[1100];
char s[110][50];
int val[110];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%s", str);
        int len=strlen(str);
        val[i]=len;
        sort(str, str+len);
        len=unique(str, str+len)-str;
        str[len]='\0';
        strcpy(s[i], str);
    }
    int ans=0;
    for(int i=0; i<26; i++)
        for(int j=i+1; j<26; j++)
        {
            char ss[50];
            ss[0]='a'+i;
            ss[1]='a'+j;
            ss[2]='\0';
            int cnt=0;
            for(int k=0; k<n; k++)
            {
                if(strstr(ss, s[k]))
                    cnt+=val[k];
                ans=max(ans, cnt);
            }
        }
    printf("%d\n", ans);
    return 0;
}

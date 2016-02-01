#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

char s[10][6]={"0", "1", "6248", "1397", "64", "5", "6", "1793", "6842", "19"};

int div(char* str, int x)
{
    int c=0;
    for(int i=0; str[i]; i++)
        c=(c*10+str[i]-'0')%x;
    return c;
}

int main()
{
    char a[120], b[120];
    while(~scanf("%s%s", a, b))
    {
        if(a[0]=='0' && b[0]=='0')return 0;
        int n=a[strlen(a)-1]-'0';
        if(b[0]=='0')
            puts("1");
        else
            printf("%c\n", s[n][div(b, strlen(s[n]))]);
    }
}

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

char s[100000+100];

int main()
{
    gets(s);
    int a=0, b=0, c=0, pos;
    for(int i=0; s[i]; i++)
    {
        if(s[i]=='(')
            a++;
        else if(s[i]=='#')
            b++, a--, pos=i;
        else
            c++, a--;
        if(a<0)
        {
            puts("-1");
            return 0;
        }
    }
    int d=0, e=0;
    for(int i=0; s[i]; i++)
    {
        if(i==pos)
            e+=a+1;
        else if(s[i]=='(')
           d++;
        else e++;

        if(d<e)
        {
            puts("-1");
            return 0;
        }
    }
    for(int i=1; i<b; i++)
        puts("1");
    printf("%d\n", a+1);
    return 0;
}

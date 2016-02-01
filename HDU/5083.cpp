#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

char op[10][10]= {"", "ADD", "SUB", "DIV", "MUL", "MOVE", "SET"};

void Error()
{
    puts("Error!");
}

void op0()
{
    char str[1111];
    gets(str);
    int len=strlen(str);
    if(len!=16)
    {
        Error();
        return ;
    }
    for(int i=0; i<len; i++)
        if(str[i]!='0' && str[i]!='1')
        {
            Error();
            return ;
        }
    int opp=0, a=0, b=0;
    for(int i=0; i<6; i++)
        opp=opp*2+str[i]-'0';
    for(int i=6; i<11; i++)
        a=a*2+str[i]-'0';
    for(int i=11; i<16; i++)
        b=b*2+str[i]-'0';

    if(opp>=1 && opp<=5 && a!=0 && b!=0)
        printf("%s R%d,R%d\n", op[opp], a, b);
    else if(opp==6 && a!=0 && b==0)
        printf("%s R%d\n", op[6], a);
    else
    {
        Error();
        return ;
    }
}

int solve_op(char *str)
{
    char s[10];
    for(int i=0; i<3; i++)
        s[i]=str[i];
    s[3]='\0';
    for(int i=1; i<=6; i++)
        if(strcmp(op[i], s)==0)
            return i;
    return 5;
}

void print_bri(int x)
{
    int cnt=0, num[10]={0};
    while(x)
    {
        num[cnt++]=x%2;
        x/=2;
    }
    for(int i=4; i>=0; i--)
        printf("%d", num[i]);
}

void op1()
{
    int a=0, b=0, c=0;
    char str[50], s[10];
    gets(str);
    int i;
    a=solve_op(str);
    i=5;
    if(a==5)
        i++;
    for(; str[i]>='0' && str[i]<='9'; i++)
        b=b*10+str[i]-'0';
    if(a!=6)
        for(i+=2; str[i]>='0' && str[i]<='9'; i++)
            c=c*10+str[i]-'0';
    printf("0");
    print_bri(a);
    print_bri(b);
    print_bri(c);
    puts("");
}

int main()
{
    int opp;
    while(~scanf("%d", &opp))
    {
        getchar();
        if(!opp)
            op0();
        else op1();
    }
    return 0;
}

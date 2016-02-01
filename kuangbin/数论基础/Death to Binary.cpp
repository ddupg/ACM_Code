#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

char s[2][60];
int num[3][100], top[3];

int solve(int* a)
{
    bool flag=true;
    while(flag)
    {
        flag=false;
        for(int i=50; i; i--)
        {
            if(a[i]+a[i-1]>2)return 0;
            if(a[i] && a[i-1])
            {
                flag=true;
                a[i+1]++;
                a[i]--;
                a[i-1]--;
            }
        }
    }

    int top=0;
    for(int i=0; i<50; i++)
        if(a[i])top=i;
    return top;
}

void print(int* a, int top)
{
    for(int i=top; i>=0; i--)
        printf("%d", a[i]);
    puts("");
}

int main()
{
    while(~scanf("%s%s", s[0], s[1]))
    {
        memset(num, 0, sizeof num);
        for(int i=0; i<2; i++)
        {
            reverse(s[i], s[i]+strlen(s[i]));
            for(int j=0; s[i][j]; j++)
                num[i][j]=s[i][j]-'0';
            top[i]=solve(num[i]);
        }
        for(int i=0; i<50; i++)
            num[2][i]=num[0][i]+num[1][i];
        bool flag=true;
        while(flag)
        {
            flag=false;
            for(int i=50; i>=0; i--)
                if(num[2][i]>1)
                {
                    flag=true;
                    if(!i)
                        num[2][i]-=2, num[2][i+1]++;
                    else if(i==1)
                        num[2][i-1]++, num[2][i+1]++, num[2][i]-=2;
                    else
                        num[2][i-1]++, num[2][i-2]++, num[2][i]--;
                    break;
                }
            solve(num[2]);
        }
        top[2]=solve(num[2]);

        for(int i=0; i<top[2]-top[0]+2; i++)
            putchar(' ');
        print(num[0], top[0]);
        putchar('+');
        for(int i=1; i<top[2]-top[1]+2; i++)
            putchar(' ');
        print(num[1], top[1]);
        putchar(' ');
        putchar(' ');
        for(int i=0; i<=top[2]; i++)
            putchar('-');
        puts("");
        putchar(' ');
        putchar(' ');
        print(num[2], top[2]);
        puts("");
    }
    return 0;
}

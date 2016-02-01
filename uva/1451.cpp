#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=100000+100;

char str[maxn];
int d[maxn], q[maxn], sum[maxn];

int up(int i, int j)
{
    return sum[i]-sum[j];
}
int down(int i, int j)
{
    return i-j;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, len;
        scanf("%d%d", &n, &len);
        getchar();
        gets(str);
        for(int i=0; str[i]; i++)
            sum[i+1]=sum[i]+str[i]-'0';
        int head=0, tail=0;
        int ans=len;
        for(int i=len; i<=n; i++)
        {
            while(head<tail-1 && up(i-len, q[tail-1])*down(q[tail-1], q[tail-2])<up(q[tail-1], q[tail-2])*down(i-len, q[tail-1]))
                tail--;
            q[tail++]=i-len;
            while(head<tail-1 && up(i, q[head+1])*down(q[head+1], q[head])>=up(q[head+1], q[head])*(down(i, q[head+1])))
                head++;
            d[i]=q[head];
            int a=up(i, d[i])*down(ans, d[ans]), b=up(ans, d[ans])*down(i, d[i]);
            if(a>b || (a==b && i-d[i]<ans-d[ans]))
                ans=i;
        }
        printf("%d %d\n", d[ans]+1, ans);
    }
    return 0;
}

#include <stdio.h>
#include <cstring>
const int maxn=1e5+5;
unsigned short bit[10][10][maxn];
bool f[10][10][maxn];
int n, m, num[maxn];

int lowbit(int x)
{
    return x&(-x);
}

void add(int i, int j, int x, int val=1)
{
    while(x<=n)
    {
        bit[i][j][x]+=val;
        if(bit[i][j][x]>50000)
        {
            bit[i][j][x]-=50000;
            f[i][j][x]=1;
        }
        x+=lowbit(x);
    }
}

int sum(int i, int j, int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=bit[i][j][x];
        if(f[i][j][x])
            ans+=50000;
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
//        memset(bit, 0, sizeof(bit));
//        memset(f, 0, sizeof(f));
        scanf("%d%d", &n, &m);
        for(int i=0; i<10; i++)
            for(int j=0; j<10; j++)
                for(int k=0; k<=n; k++)
                    f[i][j][k]=bit[i][j][k]=0;


        for(int i=1; i<=n; i++)
            scanf("%d", &num[i]);

        for(int i=1; i<=n; i++)
        {
            int t=num[i];
            int j=0;
            while(j<10)
            {
                add(j, t%10, i);
                t/=10;
                j++;
            }
        }

        while(m--)
        {
            char c[10];
            scanf("%s", c);
            if(c[0]=='Q')
            {
                int l, r, i, j;
                scanf("%d%d%d%d", &l, &r, &i, &j);
                printf("%d\n", sum(i-1, j, r)-sum(i-1, j, l-1));
            }
            else
            {
                int pos, new_num;
                scanf("%d%d", &pos, &new_num);
                int t=num[pos];
                int j=0;
                while(j<10)
                {
                    add(j, t%10, pos, -1);
                    j++;
                    t/=10;
                }
                t=num[pos]=new_num;
                j=0;
                while(j<10)
                {
                    add(j, t%10, pos, 1);
                    j++;
                    t/=10;
                }
            }
        }
    }
    return 0;
}

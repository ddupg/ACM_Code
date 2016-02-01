#include <cstdio>
#include <map>
using namespace std;

const int maxn=30;
map<int, int> table;

int bitcount(int x)
{
    int ans=0;
    while(x)
    {
        ans+=(x&1);
        x>>=1;
    }
    return ans;
}

int main()
{
    int n, A[maxn];
    char s[1000];
    while(~scanf("%d", &n) && n)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%s", s);
            A[i]=0;
            for(int j=0; s[j]; j++)
                A[i]^=(1<<(s[j]-'A'));
        }

        table.clear();
        int n1=n>>1, n2=n-n1;
        for(int i=0; i<(1<<n1); i++)
        {
            int x=0;
            for(int j=0; j<n1; j++)
                if(i&(1<<j))
                    x^=A[j];
            if(!table.count(x) || bitcount(table[x])<bitcount(i))
                table[x]=i;
        }
        int ans=0;
        for(int i=0; i<(1<<n2); i++)
        {
            int x=0;
            for(int j=0; j<n2; j++)
                if(i&(1<<j))
                    x^=A[n1+j];
            if(table.count(x) && bitcount(ans)<bitcount(table[x])+bitcount(i))
                ans=(i<<n1)^table[x];
        }

        printf("%d\n", bitcount(ans));
        bool first=true;
        for(int i=0; i<n; i++)
            if(1<<i&ans)
            {
                if(!first)putchar(' ');
                first=false;
                printf("%d", i+1);
            }
        puts("");
    }
    return 0;
}

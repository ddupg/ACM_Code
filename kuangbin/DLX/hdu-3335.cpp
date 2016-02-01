#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int maxn=1010;
const int maxnd=maxn*maxn;
const int oo=0x3f3f3f3f;

struct DLX
{
    int n, m, sz;
    int U[maxnd], D[maxnd], L[maxnd], R[maxnd], row[maxnd], col[maxnd];
    int H[maxn], S[maxn];
    int ansd, ans[maxn];
    void init(int _n, int _m)
    {
        n=_n, m=_m, ansd=0;
        for(int i=0; i<=m; i++)
        {
            S[i]=0;
            U[i]=D[i]=i;
            L[i]=i-1;
            R[i]=i+1;
        }
        R[m]=0, L[0]=m;
        sz=m;
        for(int i=1; i<=n; i++)
            H[i]=-1;
    }
    void Link(int r, int c)
    {
        ++S[col[++sz]=c];
        row[sz]=r;
        D[sz]=D[c];
        U[D[c]]=sz;
        U[sz]=c;
        D[c]=sz;
        if(H[r]<0)H[r]=L[sz]=R[sz]=sz;
        else
        {
            R[sz]=R[H[r]];
            L[R[H[r]]]=sz;
            L[sz]=H[r];
            R[H[r]]=sz;
        }
    }
    void remove(int c)
    {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j])
            {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
    void resume(int c)
    {
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                ++S[Col[U[D[j]]=D[U[j]]=j]];
        L[R[c]] = R[L[c]] = c;
    }
    void Dance(int d)
    {
        if(d>ansd)
        {
            ansd=d;
            cout<<d<<": ";
            for(int i=0; i<d; i++)
                cout<<ans[i]<<' ';
            cout<<endl;
        }
        if(R[0]==0) return ;
        int c=R[0];
        for(int i=R[0]; i; i=R[i])
            if(S[i]<S[c])
                c=i;

        L[R[c]]=L[c], R[L[c]]=R[c];
        ans[d]=c;
        for(int i=D[c]; i!=c; i=D[i])
            for(int j=R[i]; j!=i; j=R[j])
            {
                U[D[j]]=U[j];
                D[U[j]]=D[j];
                --S[col[j]];
            }
        Dance(d+1);
        for(int i=D[c]; i!=c; i=D[i])
            for(int j=L[i]; j!=i; j=L[j])
                ++S[col[U[D[j]]=D[U[j]]=j]];
        L[R[c]]=R[L[c]]=c;
    }
} dlx;

int main()
{
    int T, n;
    LL a[maxn];
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        dlx.init(n, n);
        for(int i=1; i<=n; i++)
        {
            scanf("%I64d", a+i);
            dlx.Link(i, i);
            for(int j=1; j<i; j++)
                if(a[i]%a[j]==0 || a[j]%a[i]==0)
                {
                    dlx.Link(i, j);
                    dlx.Link(j, i);
                }
        }
        dlx.Dance(0);
        printf("%d\n", dlx.ansd);
    }
    return 0;
}

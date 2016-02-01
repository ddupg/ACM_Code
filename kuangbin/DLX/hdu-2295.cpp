#include <iostream>
#include <cstdio>
#include <cmath>
#define sqr(x) ((x)*(x))
#define fst first
#define snd second
using namespace std;
typedef pair<double, double> pdd;
const int maxn=55;
const double eps=1e-9;
const int maxnd=maxn*maxn;
const int oo=0x3f3f3f3f;

struct DLX
{
    int n, m, sz, lim;
    int U[maxnd], D[maxnd], L[maxnd], R[maxnd], row[maxnd], col[maxnd];
    int H[maxn], S[maxn];
    int ansd;
    void init(int _n, int _m, int _lim)
    {
        n=_n, m=_m, lim=_lim;
        for(int i=0; i<=m; i++)
        {
            S[i]=0;
            U[i]=D[i]=i;
            L[i]=i-1;
            R[i]=i+1;
        }
        R[m]=0, L[0]=m;
        sz=m;
        for(int i=1; i<=n; i++)H[i]=-1;
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
        for(int i=D[c]; i!=c; i=D[i])
            L[R[i]]=L[i], R[L[i]]=R[i];
    }
    void resume(int c)
    {
        for(int i=U[c]; i!=c; i=U[i])
            L[R[i]]=R[L[i]]=i;
    }
    bool v[maxn];
    int f()
    {
        int ans=0;
        for(int c=R[0]; c; c=R[c])v[c]=true;
        for(int c=R[0]; c; c=R[c])if(v[c])
            {
                ans++;
                v[c]=false;
                for(int i=D[c]; i!=c; i=D[i])
                    for(int j=R[i]; j!=i; j=R[j])
                        v[col[j]]=false;
            }
        return ans;
    }
    bool Dance(int d)
    {
        if(d+f()>lim)return false;
        if(R[0]==0)return d<=lim;
        int c=R[0];
        for(int i=R[0]; i; i=R[i])
            if(S[i]<S[c])
                c=i;
        for(int i=D[c]; i!=c; i=D[i])
        {
            remove(i);
            for(int j=R[i]; j!=i; j=R[j])remove(j);
            if(Dance(d+1))return true;
            for(int j=L[i]; j!=i; j=L[j])resume(j);
            resume(i);
        }
        return false;
    }
} dlx;

pdd a[maxn], b[maxn];
int n, m, k;

double Dist(pdd a, pdd b)
{
    return sqr(a.fst-b.fst)+sqr(a.snd-b.snd);
}

bool check(double r)
{
    dlx.init(m, n, k);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(Dist(a[i], b[j])<=r*r)
                dlx.Link(j, i);
    return dlx.Dance(0);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &k);
        for(int i=1; i<=n; i++)
            scanf("%lf%lf", &a[i].fst, &a[i].snd);
        for(int i=1; i<=m; i++)
            scanf("%lf%lf", &b[i].fst, &b[i].snd);
        double L=0, R=1e9;
        while(R-L>eps)
        {
            double mid=(R+L)/2;
            if(check(mid))
                R=mid;
            else L=mid;
        }
        printf("%.6lf\n", R);
    }
    return 0;
}

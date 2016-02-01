#include <iostream>
#include <algorithm>
#include <cstdio>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

#define Key ch[ch[rt][1]][0]

const int maxn=500000+100;
const int oo=0x3f3f3f3f;
int pre[maxn], ch[maxn][2], val[maxn], sz[maxn];
int rt, tot1, tot2, s[maxn];
int gcd[maxn][2], on[maxn];
int n, m, a[maxn][2];

void NewNode(int& r, int fa, int v, int statu)
{
    if(tot2)r=s[tot2--];
    else r=++tot1;
    pre[r]=fa;
    ch[r][0]=ch[r][1]=0;
    val[r]=v;
    gcd[r][0]=gcd[r][1]=0;
    on[r]=statu;
    gcd[r][statu]=v;
    sz[r]=1;
}

void pushup(int r)
{
    int ls=ch[r][0], rs=ch[r][1];
    sz[r]=sz[ls]+sz[rs]+1;
    gcd[r][0]=__gcd(gcd[ls][0], gcd[rs][0]);
    gcd[r][1]=__gcd(gcd[ls][1], gcd[rs][1]);
    gcd[r][on[r]]=__gcd(gcd[r][on[r]], val[r]);
}

void build(int& x, int l, int r, int fa)
{
    if(l>r)return ;
    int mid=(l+r)>>1;
    NewNode(x, fa, a[mid][0], a[mid][1]);
    build(ch[x][0], l, mid-1, x);
    build(ch[x][1], mid+1, r, x);
    pushup(x);
}

void init()
{
    rt=tot1=tot2=0;
    ch[rt][0]=sz[rt]=pre[rt]=ch[rt][1]=0;
    val[rt]=0;
    NewNode(rt, 0, 0, 0);
    NewNode(ch[rt][1], rt, 0, 0);

    for(int i=0; i<n; i++)
        scanf("%d%d", &a[i][0], &a[i][1]);
    build(Key, 0, n-1, ch[rt][1]);

    pushup(ch[rt][1]);
    pushup(rt);
}

void Rotate(int x, int kind)
{
    int y=pre[x];
    ch[y][!kind]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
    pushup(y);
}

void Splay(int r, int goal)
{
    while(pre[r]!=goal)
    {
        if(pre[pre[r]]==goal)
            Rotate(r, ch[pre[r]][0]==r);
        else
        {
            int y=pre[r];
            int kind=ch[pre[y]][0]==y;
            if(ch[y][kind]==r)
            {
                Rotate(r, !kind);
                Rotate(r, kind);
            }
            else
            {
                Rotate(y, kind);
                Rotate(r, kind);
            }
        }
    }
    pushup(r);
    if(goal==0)rt=r;
}

int get_Kth(int r, int k)
{
    int t=sz[ch[r][0]]+1;
    if(t==k)return r;
    if(t>k)return get_Kth(ch[r][0], k);
    return get_Kth(ch[r][1], k-t);
}

int query(int L, int R, int statu)
{
    Splay(get_Kth(rt, L), 0);
    Splay(get_Kth(rt, R+2), rt);
    if(!gcd[Key][statu])return -1;
    return gcd[Key][statu];
}

void add(int pos, int v, int statu)
{
    Splay(get_Kth(rt, pos+1), 0);
    Splay(get_Kth(rt, pos+2), rt);
    NewNode(Key, ch[rt][1], v, statu);
    pushup(ch[rt][1]);
    pushup(rt);
}

void erase(int pos)
{
    Splay(get_Kth(rt, pos), 0);
    Splay(get_Kth(rt, pos+2), rt);
    s[++tot2]=Key;
    pre[Key]=0;
    Key=0;
    pushup(ch[rt][1]);
    pushup(rt);
}

void reverse(int pos)
{
    Splay(get_Kth(rt, pos), 0);
    Splay(get_Kth(rt, pos+2), rt);
    on[Key]^=1;
    swap(gcd[Key][0], gcd[Key][1]);
    pushup(ch[rt][1]);
    pushup(rt);
}

void modify(int pos, int v)
{
    Splay(get_Kth(rt, pos), 0);
    Splay(get_Kth(rt, pos+2), rt);
    val[Key]=v;
    gcd[Key][on[Key]]=v;
    pushup(ch[rt][1]);
    pushup(rt);
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        init();
        while(m--)
        {
            char op[5];
            int x, y, z;
            scanf("%s", op);
            if(op[0]=='Q')
            {
                scanf("%d%d%d", &x, &y, &z);
                printf("%d\n", query(x, y, z));
            }
            else if(op[0]=='I')
            {
                scanf("%d%d%d", &x, &y, &z);
                add(x, y, z);
            }
            else if(op[0]=='D')
            {
                scanf("%d", &x);
                erase(x);
            }
            else if(op[0]=='R')
            {
                scanf("%d", &x);
                reverse(x);
            }
            else if(op[0]=='M')
            {
                scanf("%d%d", &x, &y);
                modify(x, y);
            }
        }
    }
    return 0;
}

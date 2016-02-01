#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=110;

string d[maxn][maxn];
char s[maxn], str[maxn];
int n, f[maxn];

void getFail(char* P, int m, int* f)
{
    f[0]=f[1]=0;
    for(int i=1; i<m; i++)
    {
        int j=f[i];
        while(j && P[i]!=P[j])j=f[j];
        f[i+1]=P[i]==P[j]?j+1:0;
    }
}

string num2str(int x)
{
    string ans("");
    while(x)
    {
        ans=(char)(x%10+'0')+ans;
        x/=10;
    }
    return ans;
}

int main()
{
    while(cin>>s)
    {
        n=strlen(s);
        for(int i=0; i<n; i++)
            d[i][i]=string("")+s[i];
        for(int i=n-1; i>=0; i--)
            for(int j=i+1; j<n; j++)
            {
                d[i][j]="";
                int len=0;
                for(int k=i; k<=j; k++)
                {
                    d[i][j]+=s[k];
                    str[len++]=s[k];
                }
                getFail(str, len, f);
                if(f[len]>0 && len%(len-f[len])==0)
                {
                    string tmp=num2str(len/(len-f[len]));
                    tmp+='(';
                    tmp+=d[i][i+len-f[len]-1];
                    tmp+=')';
                    if(tmp.length()<d[i][j].length())
                        d[i][j]=tmp;
                }
                for(int k=i; k<j; k++)
                {
                    string tmp=d[i][k]+d[k+1][j];
                    if(tmp.length()<d[i][j].length())
                        d[i][j]=tmp;
                }
            }
        cout<<d[0][n-1]<<endl;
    }
    return 0;
}

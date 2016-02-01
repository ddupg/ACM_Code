#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
int k;
int t[10010000];
void print(int x)
{
    if(!x)return ;
    print(x>>1);
    cout<<(x&1);
}
int main()
{
    while(cin>>k && k)
    {
        int i=1;
        t[i]=1%k;
        while(t[i])
        {
            ++i;
            t[i]=(t[i>>1]*10+(i&1))%k;
        }
        print(i);
        cout<<endl;
    }
    return 0;
}

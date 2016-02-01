#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

bool judge(int x)
{
    int cnt=0;
    for(int i=2; i*i<=x; i++)
        while(x%i==0)
        {
            cnt++;
            x/=i;
        }
    if(x>1)cnt++;
    return cnt==2;
}

int main()
{
    int T, x;
    cin>>T;
    while(T--)
    {
        cin>>x;
        if(judge(x))
            puts("Yes");
        else puts("No");
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <cmath>
using namespace std;
typedef unsigned long long LLU;
set<LLU> s;
vector<int> power;

bool isprime(int x)
{
    for(int i=2; i*i<=x; i++)
        if(x%i==0)
            return false;
    return true;
}

LLU Pow(LLU x, int b)
{
    LLU ans=1;
    while(b)
    {
        if(b&1)
            ans*=x;
        x*=x;
        b>>=1;
    }
    return ans;
}

int main()
{
    for(int i=4; i<64; i++)
        if(!isprime(i))
            power.push_back(i);

    for(LLU i=2; i<65536; i++)
    {
        int t=(int)sqrt(i);
        if(t*t==i)continue ;
        for(int j=0; j<power.size() && pow(i, power[j]/4.0)<=65536; j++)
            s.insert(Pow(i, power[j]));
    }
    puts("1");
    for(set<LLU>::iterator i = s.begin(); i!=s.end(); i++)
        cout<<*i<<endl;
    return 0;
}

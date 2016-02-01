#include <iostream>
#include <set>
#include <cstdio>
#include <sstream>
using namespace std;

int next(int n, int k)
{
    stringstream ss;
    ss<<(long long)k*k;
    string s=ss.str();
    if(s.length()>n)s=s.substr(0, n);
    int ans;
    stringstream ss2(s);
    ss2>>ans;
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        set<int> s;
        s.clear();
        s.insert(k);
        int ans=k;
        while(1)
        {
            k=next(n, k);
            ans=max(k, ans);
            if(s.count(k))break;
            s.insert(k);
        }
        printf("%d\n", ans);
    }
    return 0;
}

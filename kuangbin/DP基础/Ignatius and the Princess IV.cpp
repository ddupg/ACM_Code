#include <cstdio>
#include <map>
using namespace std;

map<int, int> mp;

int main()
{
    int n, x;
    while(~scanf("%d", &n))
    {
        mp.clear();
        for(int i=0; i<n; i++)
        {
            scanf("%d", &x);
            mp[x]++;
        }
        for(map<int, int>::iterator i=mp.begin(); i!=mp.end(); i++)
            if(i->second>(n>>1))
            {
                printf("%d\n", i->first);
                break;
            }
    }
    return 0;
}

#include <cstdio>
#include <set>
using namespace std;

set<int> s;

int main()
{
    int n, x;
    set<int>::iterator it;
    while(~scanf("%d", &n))
    {
        s.clear();
        while(n--)
        {
            scanf("%d", &x);
            it=s.lower_bound(x);
            if(it!=s.end())
                s.erase(it);
            s.insert(x);
        }
        printf("%d\n", s.size());
    }
    return 0;
}

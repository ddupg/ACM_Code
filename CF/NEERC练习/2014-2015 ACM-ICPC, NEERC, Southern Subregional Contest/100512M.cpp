#include <cstdio>
#include <stack>
#define fst first
#define snd second
#define mp make_pair
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

stack<pii> stk[30];
stack<char> ori;

int main()
{
    int n;
    char str[55];
    scanf("%d%*c", &n);
    for(int i=1; i<=n; i++)
    {
        gets(str+1);
        for(int j=1; str[j]; j++)
        {
            char c=str[j];
            if(c=='{' || (c>='a' && c<='z'))
            {
                ori.push(c);
                if(c>='a' && c<='z')
                {
                    if(!stk[c-'a'].empty())
                    {
                        pii t=stk[c-'a'].top();
                        printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n", i, j, c, t.fst, t.snd);
                    }
                    stk[c-'a'].push(mp(i, j));
                }
            }
            else if(c=='}')
            {
                while(!ori.empty())
                {
                    char t=ori.top();
                    ori.pop();
                    if(t!='{')stk[t-'a'].pop();
                    else break;
                }
            }
        }
    }
    return 0;
}

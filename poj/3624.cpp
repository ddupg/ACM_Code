#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <sstream>
#include <map>
#include <set>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;

const int maxm=13000;
const int maxn=3500;

int n, m, d[maxm], w[maxn], D[maxn];

void dp()
{
    memset(d, 0, sizeof(d));
    for(int i=0; i<n; i++)
        for(int j=m; j>=w[i]; j--)
            d[j]=max(d[j], d[j-w[i]]+D[i]);
    printf("%d\n", d[m]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<n; i++)
        scanf("%d%d", &w[i], &D[i]);
    dp();
    return 0;
}

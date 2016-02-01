#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

typedef int Matrix[1011][100];
Matrix A;
int m;

//m�����̣�n������
int rank(int m, int n)
{
    int i=0, j=0, k, r, u;
    while(i<m && j<n)   //��ǰ���ڴ����i�����̣���j������
    {
        r=i;
        for(k=i; k<m; k++)
            if(A[k][j])
            {
                r=k;
                break;
            }
        if(A[r][j])
        {
            if(r!=i)
                for(k=0; k<=n; k++)
                    swap(A[r][k], A[i][k]);
            //��Ԫ���i�еĵ�һ����0���ǵ�j�У��ҵ�u>i�еĵ�j�о�Ϊ0
            for(u=i+1; u<m; u++)
                if(A[u][j])
                    for(k=i; k<=n; k++)
                        A[u][k]^=A[i][k];
            i++;
        }
        j++;
    }
    return i;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        memset(A, 0, sizeof(A));
        scanf("%d", &m);
        int n=0;
        for(int i=0; i<m; i++)
        {
            LL tmp;
            scanf("%I64d", &tmp);
            int j=0;
            while(tmp)
            {
                A[i][j++]=tmp%2;
                tmp/=2;
            }
            n=max(n, j);
        }
        if(m>rank(m, n))
            puts("Yes");
        else puts("No");
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int cmp ( const void *a , const void *b )
{
    return *(int *)a - *(int *)b;
}

int main()
{
    int t, i;
    scanf("%d", &t);
    while(t--)
    {
        int a[10];
        for(i=0; i<6; i++)
            scanf("%d", &a[i]);
        qsort(a, 6, sizeof(int), cmp);

        if(a[5]+a[4]>a[3]+a[2]+a[1])
            puts("Grandpa Shawn is the Winner!");
        else puts("What a sad story!");
    }
    return 0;
}

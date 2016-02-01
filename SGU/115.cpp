#include <iostream>
using namespace std;

int a[15]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
    int m, d, y=2001;
    cin>>d>>m;
    if(m>=1 && m<=12 && d>0 && d<=a[m])
    {
        if(m<=2)
            m+=12, y--;
        cout<<(d + 2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7+1<<endl;
    }
    else cout<<"Impossible"<<endl;
    return 0;
}

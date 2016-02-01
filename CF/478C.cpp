#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    long long t[5];
    cin>>t[0]>>t[1]>>t[2];
    sort(t, t+3);
    cout<<min((t[0]+t[1]+t[2])/3, t[0]+t[1])<<endl;
    return 0;
}

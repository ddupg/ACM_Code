#include <iostream>
#include <vector>
using namespace std;
vector<pair<int, int> > v[2];

void judge(int x, int flag)
{
    for(int i=1; i<x; i++)
        for(int j=i; j<x && i*i+j*j<=x*x; j++)
        {
            if(i*i+j*j==x*x)
                v[flag].push_back(make_pair(i, j));
        }
}
bool judge(int x1, int y1, int x2, int y2)
{
    if(x1==x2)return false;
    if(y1==y2)return false;
    if(x1==-x2 && y1==-y2)return false;
    if((x1*x2<0 || y1*y2>0) && x1>x2 && x1%x2==0 && y1%y2==0 && x1/x2==y1/y2)return false;
    if((x1*x2<0 || y1*y2>0) && x2>x1 && x2%x1==0 && y2%y1==0 && x2/x1==y2/y1)return false;
    if(x1*x2+y1*y2)return false;
    cout<<"YES"<<endl;
    cout<<"0 0"<<endl;
    cout<<x1<<" "<<y1<<endl;
    cout<<x2<<" "<<y2<<endl;
    return true;
}

int main()
{
    int a, b;
    cin>>a>>b;
    judge(a, 0);
    judge(b, 1);
    if(v[0].size() && v[1].size())
    {
        for(int i=0; i<v[0].size(); i++)
            for(int j=0; j<v[1].size(); j++)
            {
                if(judge(v[0][i].first, v[0][i].second, v[1][j].first, -v[1][j].second))
                    return 0;
                else if(judge(v[0][i].first, v[0][i].second, v[1][j].second, -v[1][j].first))
                    return 0;
                else if(judge(v[0][i].first, v[0][i].second, -v[1][j].first, v[1][j].second))
                    return 0;
                else if(judge(v[0][i].first, v[0][i].second, -v[1][j].second, v[1][j].first))
                    return 0;
            }
        cout<<"NO"<<endl;
    }
    else cout<<"NO"<<endl;
    return 0;
}

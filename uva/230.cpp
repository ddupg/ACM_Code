#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

map<string, string> author;
struct cmp
{
    bool operator () (const string& a, const string& b)
    {
        return author[a]<author[b];
    }
};
set<string, cmp> book, s;

int main()
{
    ios::sync_with_stdio(false);
    string str;
    while(getline(cin, str) && str[0]!='E')
    {
        int p=str.find("\"", 1);
        author[str.substr(1, p-1)]=str.substr(p+5);
        book.insert(str.substr(1, p-1));
    }

    while(cin>>str)
    {
        if(str[0]=='E')
            return 0;
        else if(str[0]=='B')
        {
            getline(cin, str);
            book.erase(str.substr(2, str.length()-3));
        }
        else if(str[0]=='R')
        {
            getline(cin, str);
            s.insert(str.substr(2, str.length()-3));
        }
        else if(str[0]=='S')
        {
            while(!s.empty())
            {
                set<string, cmp>::iterator i=(book.insert(*s.begin())).first;
                string ss = *i;
                s.erase(ss);
                if(ss==*book.begin())
                    cout<<"Put \""<<*i<<"\" first"<<endl;
                else
                {
                    set<string, cmp>::iterator j=i;
                    j--;
                    cout<<"Put \""<< *i<<"\" after \""<< *j <<"\""<<endl;
                }
            }
            cout<<"END"<<endl;
        }
    }
    return 0;
}

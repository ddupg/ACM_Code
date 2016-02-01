#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
#define fst first
#define snd second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<char, char> pcc;

map<string, pair<char, char> > mp;

void init()
{
    mp["0E"]=pcc('`', '~');
    mp["16"]=pcc('1', '!');
    mp["1E"]=pcc('2', '@');
    mp["26"]=pcc('3', '#');
    mp["23"]=pcc('4', '$');
    mp["2E"]=pcc('5', '%');
    mp["36"]=pcc('6', '^');
    mp["3D"]=pcc('7', '&');
    mp["3E"]=pcc('8', '*');
    mp["46"]=pcc('8', '(');
    mp["22"]=pcc('9', ')');
    mp["4E"]=pcc('0', '_');
    mp["55"]=pcc('=', '+');
/**    mp["66"]=pcc('`', '~'); Backspac**/
    mp["0D"]=pcc('\t', '\t');
    mp["15"]=pcc('q', 'Q');
    mp["1D"]=pcc('w', 'W');
    mp["24"]=pcc('e', 'E');
    mp["2C"]=pcc('r', 'R');
    mp["2D"]=pcc('t', 'T');
    mp["35"]=pcc('y', 'Y');
    mp["3C"]=pcc('u', 'U');
    mp["43"]=pcc('i', 'I');
    mp["44"]=pcc('o', 'O');
    mp["4D"]=pcc('p', 'P');
    mp["54"]=pcc('[', '{');
    mp["5B"]=pcc(']', '}');
    mp["5D"]=pcc('|', '~');
/**    mp["58"]=pcc('`', '~'); Caps**/
    mp["1C"]=pcc('a', 'A');
    mp["1B"]=pcc('s', 'S');
    mp["25"]=pcc('d', 'D');
    mp["2B"]=pcc('f', 'F');
    mp["33"]=pcc('g', 'G');
    mp["34"]=pcc('h', 'H');
    mp["3B"]=pcc('j', 'J');
    mp["42"]=pcc('k', 'K');
    mp["4B"]=pcc('l', 'L');
    mp["4C"]=pcc(';', ':');
    mp["52"]=pcc('\'', '"');
    mp["5A"]=pcc('\n', '\n');
/**    mp["12"]=pcc('`', '~'); SHIFT**/
    mp["1A"]=pcc('z', 'Z');
    mp["45"]=pcc('x', 'X');
    mp["29"]=pcc('c', 'C');
    mp["2A"]=pcc('v', 'V');
    mp["32"]=pcc('b', 'B');
    mp["31"]=pcc('n', 'N');
    mp["3A"]=pcc('m', 'M');
    mp["41"]=pcc(',', '<');
    mp["49"]=pcc('.', '>');
    mp["4A"]=pcc('/', '?');
/**    mp["59"]=pcc('`', '~'); SHIFT**/
    mp["21"]=pcc(' ', ' ');
}

const int maxn=1000000+100;
char s[maxn];
char ans[maxn];

int main()
{
    init();
    while(~scanf("%s", s))
    {
        int cnt=0;
        int SHIFT=0, CAPS=0;
        for(int i=0; s[i]; i+=2)
        {
            string str;
            str+=s[i];
            str+=s[i+1];
            if(str=="F0")
            {
                str="";
                str+=s[i+2];
                str+=s[i+3];
                i+=2;
                if(str=="12" || str=="59")
                    SHIFT--;
                if(str=="58")
                    CAPS=0;
            }
            else if(str=="66")cnt--;
            else if(str=="12" || str=="59")
                SHIFT++;
            else if(str=="58")
                CAPS=1;
            else
            {
                char c=mp[str].fst;
                if(c>='a' && c<='z')
                {
                    if((SHIFT>0)^CAPS)
                        ans[cnt++]=c+'a';
                    else ans[cnt++]=c;
                }
                else if(SHIFT)
                    ans[cnt++]=mp[str].snd;
                else ans[cnt++]=c;
            }
        }
        for(int i=0; i<cnt; i++)
            putchar(ans[i]);
        putchar('\n');
    }
    return 0;
}

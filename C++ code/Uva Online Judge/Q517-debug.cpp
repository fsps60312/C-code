#include <set>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#pragma comment(linker, "/STACK:1024000000,1024000000")

#define     IT              iterator
#define     PB(x)           push_back(x)
#define     CLR(a,b)        memset(a,b,sizeof(a))

using namespace std;

typedef     long long               ll;
typedef     unsigned long long      ull;
typedef     vector<int>             vint;
typedef     vector<ll>              vll;
typedef     vector<ull>             vull;
typedef     set<int>                sint;
typedef     set<ull>                sull;

using namespace std;

string a;
string b[8];
int s,n;
map<string,int> rec;

char idx(string a,int pos) {
    if (pos < 0) pos += n;
    pos %= n;
    return a[pos];
}

string change(string a) {
    vint p[8];
    for (int i = 0; i < 8; i++) p[i].clear();
    //cout<<a<<" ";
    for (int k = 0; k < 8; k++) {
        for (int i = 0; i < n; i++) {
            if (idx(a,i-2) == b[k][0] && idx(a,i) == b[k][1] && idx(a,i+1) == b[k][2]) {
                p[k].PB(i);
            }
        }
    }
    for (int k = 0; k < 8; k++) {
        for (int i = 0; i < p[k].size(); i++) a[p[k][i]] = b[k][3];
    }
    //cout<<a<<endl;
    return a;
}

int main() {
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    while (cin>>n) {
        rec.clear();
        cin>>a;
        string tmp = a;
        for (int i = 0; i < 8; i++) cin>>b[i];
        cin>>s;
        rec[a] = 0;
        int cnt = 0;
        int cnt_cnt;
        while (1) {
            cnt++;
            a = change(a);
            //cout<<tmp<<endl;
            //cout<<cnt<<" "<<a<<" "<<(int)a.length()<<endl;
            if (rec.find(a) != rec.end()) {
                cnt_cnt = rec[a];
                break;
            }
            else rec[a] = cnt;
        }
        bool flag = false;
        if (s >= cnt) {
            flag = true;
            s -= cnt;
            s %= (cnt - cnt_cnt);
        }
        if (!flag) a = tmp;
        for (int i = 0; i < s; i++) {
            a = change(a);
        }
        string ans = a;
        a += a;
        for (int i = 0; i < n; i++) {
            string tmp = a.substr(i,n);
            ans = min(ans,tmp);
        }
        cout<<ans<<endl;
    }
}


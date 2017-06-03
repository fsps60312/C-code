/*
ID: wuqi9395@126.com
PROG:
LANG: C++
*/
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<fstream>
#include<cstring>
#include<ctype.h>
#include<iostream>
#include<algorithm>
#define INF (1<<30)
#define PI acos(-1.0)
#define mem(a, b) memset(a, b, sizeof(a))
#define rep(i, n) for (int i = 0; i < n; i++)
#define debug puts("===============")
typedef long long ll;
using namespace std;
const int maxnode = 4001000;
struct Trie {
    int head[maxnode], next[maxnode], tot[maxnode], ed[maxnode];
    char ch[maxnode];
    int sz;
    ll sum;
    void init() {
        sz = 1;
        sum = 0;
        head[0] = next[0] = tot[0] = 0;
    }
    void insert(char *s) {
        int u = 0, v, n = strlen(s);
        for (int i = 0; i < n; i++) {
            bool ok = 0;
            for (v = head[u]; v; v = next[v]) {
                if (ch[v] == s[i]) {
                    ok = 1;
                    break;
                }
            }
            if (!ok) {
                v = sz++;
                tot[v] = ed[v] = 0;
                ch[v] = s[i];
                next[v] = head[u];
                head[u] = v;
                head[v] = 0;
            }
            u = v;
            sum += tot[v] * 2;
            tot[v]++;
        }
        sum += ed[u];
        ed[u]++;
    }
}T;
int main () {
	freopen("in.txt","r",stdin);
	//freopen("New.txt","w",stdout);
    int cnt = 1, n;
    char str[1100];
    while(~scanf("%d", &n), n) {
        T.init();
        rep(i, n) {
            scanf("%s", str);
            T.insert(str);
        }
        printf("Case %d: %lld\n", cnt++, T.sum + (ll)n * (n - 1) / 2);
    }
    return 0;
}


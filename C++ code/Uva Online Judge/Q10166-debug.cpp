#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <iostream>
using namespace std;
int dp[2405][105];
struct E {
    int st, ed, to;
    E(int a, int b, int c):
        st(a), ed(b), to(c) {}
};
vector<E> g[105];
int main() {
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout);
    int n, m, q;
    char s[105];
    int i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        map<string, int> R;
        for(i = 0; i < n; i++) {
            scanf("%s", s);
            R[s] = i;
            g[i].clear();
        }
        memset(dp, -1, sizeof(dp));
        scanf("%d", &m);
        while(m--) {
            scanf("%d", &q);
            int pret, pren, time, tn;
            scanf("%d %s", &time, s), q--;
            pret = (time/100)*60 + time%100;
            pren = R[s];
            while(q--) {
                scanf("%d %s", &time, s);
                time = (time/100)*60 + time%100;
                tn = R[s];
                g[pren].push_back(E(pret, time, tn));
                pren = tn, pret = time;
            }
        }
        int st, ed, stime;
        scanf("%d %s", &stime, s);
        st = R[s];
        scanf("%s", s);
        ed = R[s];
        stime = stime/100*60 + stime%100;
        int ll = -1, rr;
        for(i = stime; i <= 2400; i++) {
            for(j = 0; j < n; j++) {
                for(k = 0; k < g[j].size(); k++) {
                    if(g[j][k].st < i)  continue;
                    if(j == st)
                        dp[i][j] = g[j][k].st;
                    dp[g[j][k].ed][g[j][k].to] = max(dp[g[j][k].ed][g[j][k].to], dp[i][j]);
                }
            }
            if(dp[i][ed] != -1) {
                ll = dp[i][ed];
                rr = i;
                break;
            }
        }
        if(ll == -1)
            puts("No connection");
        else
            printf("%02d%02d %02d%02d\n", ll/60, ll%60, rr/60, rr%60);

    }
    return 0;
}

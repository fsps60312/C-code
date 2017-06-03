#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int max(int a, int b) { return a>b?a:b; }
int min(int a, int b) { return a>b?b:a; }

int n, m, slack[555], lx[55], ly[555], match[555], w[55][555], mem[22], a[22], t[22];
bool S[55], T[555];

bool dfs(int i) {
    S[i] = 1;
    for(int j = 1;j <= n*m; j++) if(!T[j])
        slack[j] = min(slack[j], w[i][j] - lx[i] - ly[j]);
    for(int j = 1;j <= n*m; j++) if(w[i][j] == lx[i] + ly[j] && !T[j]) {
        T[j] = 1;
        if(!match[j] || dfs(match[j])) {
            match[j] = i;
            return true;
        }
    }
    return false;
}

void update() {
    int delta = 1<<30;
    for(int i = 1;i <= n*m; i++) if(!T[i])
        delta = min(delta, slack[i]);
    for(int i = 1;i <= n; i++) if(S[i])    
        lx[i] += delta;
    for(int i = 1;i <= n*m; i++) if(T[i])
        ly[i] -= delta;
}

void KM() {
    int i, j;
    for(i = 1;i <= n; i++) {
        lx[i] = 1<<30;
        for(j = 1;j <= n*m; j++) {
            lx[i] = min(lx[i], w[i][j]);
            ly[j] = match[j] = 0;
        }
    }

    for(i = 1;i <= n; i++) {
        while(true) {
            for(j = 1;j <= n*m; j++)    S[j] = T[j] = 0, slack[j] = 1<<30;
            if(dfs(i))  break;
            else    update();
        }
    }
}

void solve() {
    for(int i = 1;i <= m; i++)  scanf("%d", &mem[i]);
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= n*m; j++)
            w[i][j] = 1<<30;
    for(int i = 1;i <= n; i++) {
        int k;
        scanf("%d", &k);
        for(int j = 1;j <= k; j++)  scanf("%d%d", &a[j], &t[j]);
        a[k+1] = 1<<30;
        for(int j = 1;j <= m; j++) {
            for(int l = 1;l <= k; l++) if(mem[j] >= a[l] && mem[j] < a[l+1]) {
                for(int ii = 1;ii <= n; ii++) {
                    w[i][(j-1)*n + ii] = ii*t[l];
                }
            }
        }
    }   

    KM();
}

int main() {
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout);
    int cas = 1;
    while(scanf("%d%d", &m, &n) != -1) {
        solve();
        printf("Case %d\n", cas++);
        int ans = 0;
        for(int i = 1;i <= n; i++)  ans += lx[i];
        for(int i = 1;i <= n*m; i++)    ans += ly[i];
        printf("Average turnaround time = %.2lf\n", (double)ans/n);
       
        int from[55], to[55], in[55], sum; // from表示程序?什么???始，to表示?束??，in表示在哪??存?域里?行
        for(int i = n*m;i >= 1; i--) {
            if(i%n == 0)    sum = 0;
            if(match[i]) {
                int tmp = w[match[i]][i];
                from[match[i]] = sum;
                int num = i%n;
                if(i%n == 0)    num = n;
                to[match[i]] = sum = tmp/num + sum;
                in[match[i]] = i/n + 1;
                if(i%n == 0)    in[match[i]]--;
            }
        }
        for(int i = 1;i <= n; i++)
            printf("Program %d runs in region %d from %d to %d\n", i, in[i], from[i], to[i]);
    }
    return 0;
}


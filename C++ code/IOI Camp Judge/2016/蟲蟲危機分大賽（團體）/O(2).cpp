#include <cstdio>

const int N = 514;
const int M = 1000;
const int MOD = 1e9 + 7;

int t, n, m, a[N], dp[M + 1];
int main() {
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i <= m; i++) dp[i] = 0;
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= a[i]; j--) {
                dp[j] += dp[j - a[i]];
                if (dp[j] >= MOD) dp[j] -= MOD;
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}

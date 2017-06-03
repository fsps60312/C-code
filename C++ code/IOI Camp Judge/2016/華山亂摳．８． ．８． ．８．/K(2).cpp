#include <cstdio>

const int N = 42;
const int M = 777;
const int MOD = 1e9 + 7;

int t, n, m, a[N], dp[M + 1];
int main() {
	puts("1 42 497 2 4 6 7 9 10 12 13 14 15 16 17 19 21 22 23 24 25 26 28 29 31 32 33 34 35 37 39 41 43 44 46 47 49 51 52 53 67 323 391 448 452");
	return 0;
	freopen("in.txt","r",stdin);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i <= m; i++) dp[i] = 0;
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= a[i]; j--) {
                dp[j] += dp[j - a[i]];
                if (dp[j] > MOD) dp[j] -= MOD;
            }
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}

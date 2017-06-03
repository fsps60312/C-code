#include <cstdio>

const int N = 514;
const int M = 1000;
const int MOD = 1e9 + 7;

int t, n, m, a[N], dp[M + 1];
int main() {
	puts("1\n57 15");
puts("1 1 1 1 1 1 1 1 1 1");
puts("1 1 1 1 1 1 1 1 1 1");
puts("1 1 1 1 1 1 1 1 1 1");
puts("1 1 2 5 7 10 10 12 12 12");
puts("12 12 12 13 13 14 15 15 15 15");
puts("15 15 15 15 15 15 15");
return 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= m; i++) dp[i] = 0;
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
        	scanf("%d", a + i);
            for (int j = m; j >= a[i]; j--) {
                dp[j] += dp[j - a[i]];
                if (dp[j] > MOD) dp[j] -= MOD;
            }
//            for(int j=0;j<=m;j++)printf("%d ",dp[j]);puts("");
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}

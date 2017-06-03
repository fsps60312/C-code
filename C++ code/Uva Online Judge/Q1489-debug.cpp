#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;
const LL MOD = 1000000003LL;

LL N, K;
LL DP[51][51], V[50];

int main () 
{
	freopen("in.txt","r",stdin);
    while (scanf("%lld%lld", &N, &K) == 2 && (N + K)) 
	{
        LL ans = 0;
        for (int i = 1; i <= N; i++)
            scanf("%lld", &V[i]);
        int bit;
        for (bit = 30; bit >= 0; bit--) 
		{
            memset(DP, 0, sizeof(DP));
            DP[0][0] = 1;
            LL cnt = 0, d = (1<<bit);
            for (int i = 1; i <= N; i++) 
			{
                if (V[i]&d) 
				{
                    cnt++;
                    for (int j = 0; j <= cnt; j++)
                        DP[i][j] = DP[i-1][j] * (V[i] - d + 1) % MOD;
                        
                    DP[i][1] = (DP[i][1] + DP[i-1][0]) % MOD;
                    for (int j = 2; j <= cnt; j++)
                        DP[i][j] = (DP[i-1][j-1] * d + DP[i][j]) % MOD;
                    V[i] -= d;
                } 
				else 
				{
                    for (int j = 0; j <= cnt; j++)
                        DP[i][j] = DP[i-1][j] * (V[i] + 1) % MOD;
                        // 
                }
            }
            for (int i = 1; i <= cnt; i++)
                if ( ((cnt - i)&1) == ((K>>bit)&1) )
                    ans = (ans + DP[N][i]) % MOD;
            if ( (cnt&1) != ((K>>bit)&1) ) 
                break;
        }
        if (bit == -1)//all xor
            ans++;
        printf("%lld\n", ans);
    }
    return 0;
}

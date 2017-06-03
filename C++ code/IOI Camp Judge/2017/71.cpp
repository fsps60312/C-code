#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
typedef double LD;
#define mpr make_pair
#define pb push_back
#define X first
#define Y second
#define FOR(i,n) for(int i=0;i<n;i++)
#define FOR1(i,n) for(int i=1;i<=n;i++)
#define RI(x) scanf("%d",&x)
#define RID(x) int x;RI(x)
const int N=510,INF=1e9+20;
const LD EPS=1e-6;
long long dp[N][N];
const long long mod=1e9+7;
long long fac[N];
int n,k,p;
int main() {
    fac[0]=1;
    fac[1]=1;
    for(int i=2;i<N;i++) fac[i]=(fac[i-1]*i)%mod;
    for(int i=0;i<N;i++) dp[i][0]=1;
    for(int i=1;i<N;i++)
        for(int j=1;j<=i;j++) dp[i][j] = (dp[i-1][j]+dp[i-1][j-1])%mod;
    RID(T);
    FOR1(w,T) {
        scanf("%d%d%d",&n,&k,&p);
        if(n==n)
        {
            long long ans=0;
            ans = (dp[p-1][n-k]*fac[k-1])%mod;
            //printf("Case #%d: ",w);            cout << ans << "\n";        }        else{            long long ans=0;
            for(int i=1;i<=n-k;i++){
                ans=(ans+(dp[n-1][i]-dp[p-1][i]+mod)*fac[n-i-1])%mod;
            }
            printf("Case #%d: ",w);
            cout << ans << "\n";
        }
    }
    return 0;
}

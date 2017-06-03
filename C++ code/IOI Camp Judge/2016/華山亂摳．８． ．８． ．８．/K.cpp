#include <cstdio>
#include<cstdlib>
#include<ctime>
#define int long long
typedef long long LL;
const int N = 42;
const int M = 777;
const int MOD = (1e9 + 7)*1;
const int m=497;
int t,a[N], dp[M + 1];
LL Solve(const int n)
{
        for (int i = 0; i <= m; i++) dp[i] = 0;
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = m; j >= a[i]; j--) {
                dp[j] += dp[j - a[i]];
                if (dp[j] > MOD)return MOD+1;
            }
        }
        return dp[m];
}
int nnn;
void Dfs(const int dep)
{
	if(dep==nnn)
	{
		if(Solve(nnn)==MOD)
		{
			printf("n=%lld,m=%lld\n",nnn,m);
			for(int i=0;i<nnn;i++)printf("%lld ",a[i]);puts("");
			for(;;);
			exit(0);
		}
		return;
	}
	a[dep]=(dep==0?0:a[dep-1])+(rand()&1?1:2);
//	while(Solve()>MOD)a[dep]++;
	for(;a[dep]<=m;a[dep]++)if(Solve(dep+1)<=MOD)
	{
	static int cnt=0,goal=0;
	if(cnt++>goal&&dep>nnn-4)goal+=1000,printf("dep=%lld,Solve()=%lld\n",dep,Solve(dep+1));
//		for(int i=dep+1;i<nnn;i++)a[i]=a[i-1]+1;
//		n=nnn;
//		if(Solve()<MOD)break;
		Dfs(dep+1);
	}
}
main() {
	srand(time(NULL));
//	freopen("in.txt","r",stdin);
    for(nnn=42;nnn>=1;nnn--)Dfs(0);
    puts("find nothing!");
    for(;;);
    return 0;
}

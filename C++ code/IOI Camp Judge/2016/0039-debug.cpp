#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL mod7=1000000007;
const int MAXN=1005;
int getint(){int v;scanf("%d",&v);return v;}
LL add(LL _x,LL _y)
{
	LL _=_x+_y;
	if(_>=mod7)_%=mod7;
	return _;
}
LL mul(LL _x,LL _y)
{
	LL _=_x*_y;
	if(_>=mod7)_%=mod7;
	return _;
}
int n,m,k,good,bad;
int a[MAXN],b[MAXN];
LL C[MAXN][MAXN],fac[MAXN];
void build()
{
	for(int i=0;i<MAXN;i++)C[i][i]=C[i][0]=1;
	for(int i=2;i<MAXN;i++)for(int j=1;j<=i;j++)C[i][j]=add(C[i-1][j-1],C[i-1][j]);
	fac[0]=1;
	for(int i=1;i<MAXN;i++)fac[i]=mul(fac[i-1],i);
}
void init()
{
	n=getint();
	m=getint();
	k=getint();
	good=bad=0;
	assert(1<=n&&n<=1000);
	assert(0<=m&&m<=n);
	assert(0<=k&&k<=n);
	for(int i=0;i<=n;i++)a[i]=b[i]=0;
	for(int i=1;i<=k;i++)
	{
		int ai=getint();
		int bi=getint();
		assert(1<=ai&&ai<=n);
		assert(1<=bi&&bi<=n);
		//ai sit at bi
		a[ai]=bi;
		b[bi]=ai;
		if(bi==ai||bi==ai+1||(ai==n&&bi==1))good++;
		else bad++;
	}
	m=max(m,good);
}
bool can(const int i,const int j)
{
//	if(a[i]==j)return true;
	if(a[i]&&(a[i]!=j))return false;
	if(b[j]&&(b[j]!=i))return false;
	return true;
}
LL dp[2][1005][1005][2],ans[1005][1005];
void DP()
{
	for(int i=0;i<2;i++)for(int j=0;j<=n;j++)for(int k=0;k<=n;k++)for(int l=0;l<2;l++)dp[i][j][k][l]=0;
	for(int i=0;i<3;i++)
	{
		if(i==0&&(a[1]==1||a[1]==2))continue;
		if(i==1&&!can(1,1))continue;
		if(i==2&&!can(1,2))continue;
		dp[(i==1)][1][(i>0)][(i==2)]++;
	}
	for(int bt=0;bt<2;bt++)for(int i=0;i<n;i++)for(int j=0;j<=n;j++)for(int msk=0;msk<2;msk++)
	{
		if(dp[bt][i][j][msk]==0)continue;
		for(int nxt=0;nxt<3;nxt++)
		{
			if(i==n-1)
			{
				if(nxt==0&&(a[n]==n||a[n]==1))continue;
				if(nxt==1&&(!can(i+1,i+1)||msk==1))continue;
				if(nxt==2&&(!can(i+1,1)||bt==1))continue;
			}
			else
			{
				if(nxt==0&&(a[i+1]==i+1||a[i+1]==i+2))continue;
				if(nxt==1&&(!can(i+1,i+1)||msk==1))continue;
				if(nxt==2&&(!can(i+1,i+2)))continue;
			}
			int nxtj=j+(nxt>0);
			int nxtmsk=(nxt==2);
			dp[bt][i+1][nxtj][nxtmsk]=add(dp[bt][i+1][nxtj][nxtmsk],dp[bt][i][j][msk]);
			if(i+1==n)ans[n][nxtj]=add(ans[n][nxt],dp[bt][i][j][msk]);
		}
	}
	for(int i=m;i<=n;i++)if(n-i-bad>=0)ans[n][i]=mul(ans[n][i],fac[n-i-bad]);
}
LL cnt[MAXN];
void solve()
{
	if(n==1){puts("1");return;}
	for(int i=0;i<=n;i++)cnt[i]=0;
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)
	{
		ans[i][j]=0;
		for(int kk=0;kk<2;kk++)for(int kkk=0;kkk<2;kkk++)dp[kk][i][j][kkk]=0;
	}
	DP();
	LL fans=ans[n][m];cnt[m]=1;
	for(int i=m+1;i<=n;i++)
	{
		LL tcnt=0;
		for(int j=m;j<i;j++)tcnt=add(tcnt,mul(C[i-good][j-good],cnt[j]));
		cnt[i]=(1-tcnt+mod7)%mod7;
		fans=add(fans,mul(ans[n][i],cnt[i]));
	}
	printf("%lld\n",fans);
}
int main()
{
//	freopen("in.txt","r",stdin);
	build();
	int __=getint();
	assert(1<=__&&__<=100);
	while(__--)
	{
		init();
		solve();
	}
}

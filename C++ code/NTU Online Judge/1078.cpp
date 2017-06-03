#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,M,W[1000];
LL DP[1000][101];
vector<int>ET[1000];
void Merge(LL *a,LL *b)
{
	static LL ans[101];
	for(int i=0;i<=M;i++)ans[i]=0;
	for(int i=1;i<=M;i++)
	{
		for(int j=1;j<=i;j++)getmax(ans[i],a[j]+b[i-j]);
	}
	for(int i=0;i<=M;i++)a[i]=ans[i];
}
void Dfs(const int u,const int parent)
{
//	printf("u=%d,w=%d\n",u+1,W[u]);
	LL *dp=DP[u];
	for(int i=0;i<=M;i++)dp[i]=W[u];
	dp[0]=0;
	for(const int nxt:ET[u])if(nxt!=parent)
	{
		Dfs(nxt,u);
		Merge(dp,DP[nxt]);
	}
//	printf("ans[%d]=%lld\n",u+1,dp[M]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)scanf("%d",&W[i]);
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),--a,--b,ET[a].push_back(b),ET[b].push_back(a);
		Dfs(0,-1);
		LL ans=0;
		for(int i=0;i<N;i++)getmax(ans,DP[i][M]);
		printf("%lld\n",ans);
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
bool getmin(LL &a,const LL &b){if(b<a){a=b;return true;}return false;}
LL S[100000],SUM[100000];
LL Sq(const LL &v){return v*v;}
void Solve(LL *dp,const LL *pre_dp,int *pre,const int l,const int r,const int bl,const int br)
{
	if(l>r)return;
	const int mid=(l+r)/2;
	int &bmid=pre[mid]=-1;
	dp[mid]=INF;
	for(int i=bl;i<=br&&i<mid;i++)
	{
		if(getmin(dp[mid],pre_dp[i]+Sq(SUM[mid]-SUM[i])))bmid=i;
	}
	assert(bmid!=-1);
	Solve(dp,pre_dp,pre,l,mid-1,bl,bmid);
	Solve(dp,pre_dp,pre,mid+1,r,bmid,br);
}
int N,K;
LL Solve(vector<int>&ans)
{
	static LL dp[202][100000];
	static int pre[202][100000];
	for(int i=0;i<N;i++)dp[1][i]=Sq(SUM[i]);
	int d=0;
	for(int k=2;k<=K+1;k++,d^=1)
	{
		Solve(dp[k],dp[k-1],pre[k],k-1,N-1,k-2,N-1);
	}
	ans.clear();
	for(int k=K,cur=pre[K+1][N-1];k>=1;cur=pre[k--][cur])ans.push_back(cur+1);
	return dp[K+1][N-1];
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&K)==2)
	{
		LL sum=0LL;
		for(int i=0;i<N;i++)scanf("%lld",&S[i]),SUM[i]=(sum+=S[i]);
		vector<int>ans;
		printf("%lld\n",(Sq(SUM[N-1])-Solve(ans))/2LL);
		assert((int)ans.size()==K);
		for(int i=K-1;i>=0;i--)
		{
			if(i<K-1)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}


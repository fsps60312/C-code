#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL b){if(b<a)a=b;}
int N,A[1000000],B[1000000],LOC[1000000];
LL M[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lld",&M[i]);
		for(int i=0;i<N;i++)scanf("%d",&A[i]),--A[i];
		for(int i=0;i<N;i++)scanf("%d",&B[i]),--B[i];
		for(int i=0;i<N;i++)LOC[B[i]]=i;
		LL total_min=INF;
		for(int i=0;i<N;i++)getmin(total_min,M[i]);
		static bool vis[1000000];
		for(int i=0;i<N;i++)vis[i]=false;
		LL ans=0LL;
		for(int i=0;i<N;i++)if(!vis[i])
		{
			vector<int>s;
			for(int cur=i;!vis[cur];vis[cur]=true,cur=LOC[A[cur]])s.push_back(A[cur]);
			const LL n=(LL)s.size();
			if(n==1LL)continue;
			LL sum=0LL,mn=INF;
			for(int j=0;j<n;j++)sum+=M[s[j]],getmin(mn,M[s[j]]);
			sum-=mn;
			ans+=min(sum+(n-1LL)*mn,sum+(n-1LL)*total_min+2LL*(mn+total_min));
		}
		printf("%lld\n",ans);
	}
	return 0;
}

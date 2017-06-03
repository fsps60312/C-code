#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
int M,N,S[1000];
LL DP[2][40000],DIST[200][200];
vector<int>V[2];
int Idx(const int &a,const int &b){return min(a,b)*M+max(a,b);}
LL Solve()
{
	for(int i=0;i<2;i++)for(int j=0;j<M*M;j++)DP[i][j]=INF;
	V[0].clear(),V[1].clear();
	DP[0][Idx(1,2)]=DIST[0][S[0]];
	DP[0][Idx(0,2)]=DIST[1][S[0]];
	DP[0][Idx(0,1)]=DIST[2][S[0]];
	V[0].push_back(Idx(1,2)),V[0].push_back(Idx(0,2)),V[0].push_back(Idx(0,1));
	for(int i=0,d=0;i+1<N;i++,d^=1)
	{
		for(int &j:V[d])
		{
			int a=j/M,b=j%M,u;
			LL &dp=DP[d][j];
//			printf("DP[%d][%d][%d]=%d\n",i,a,b,dp);
			if(DP[d^1][u=Idx(a,b)]==INF)V[d^1].push_back(u);
			getmin(DP[d^1][u],dp+DIST[S[i]][S[i+1]]);
			if(DP[d^1][u=Idx(S[i],b)]==INF)V[d^1].push_back(u);
			getmin(DP[d^1][u],dp+DIST[a][S[i+1]]);
			if(DP[d^1][u=Idx(S[i],a)]==INF)V[d^1].push_back(u);
			getmin(DP[d^1][u],dp+DIST[b][S[i+1]]);
			dp=INF;
		}
		V[d].clear();
	}
	LL ans=INF,d=(N-1)&1;
	for(int &j:V[d])getmin(ans,DP[d][j]);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&M);
	for(int i=0;i<M;i++)for(int j=0;j<M;j++)scanf("%lld",&DIST[i][j]);
	for(int i=0;i<M;i++)assert(DIST[i][i]==0LL);
	for(N=0;scanf("%d",&S[N])==1;S[N++]--);
	printf("%lld\n",Solve());
	return 0;
}

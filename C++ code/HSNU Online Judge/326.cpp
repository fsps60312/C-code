#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,K,FA[101],W[101],LEN[101],DEP[101];
vector<int>ET[101];
int DP[101][51][101];//for town i, place j sawmill on upriver and process all wood on depth k, min cost DP[i][j][k]
void BuildDEP(const int u,const int dep){DEP[u]=dep;for(const int nxt:ET[u])BuildDEP(nxt,dep+1);}
int GetDP(const int u)
{
	if(ET[u].empty())
	{
		static int dist[101];
		for(int cur=u,c=0,dep=DEP[u];dep>=0;c+=LEN[cur],cur=FA[cur],dep--)dist[dep]=c;
		for(int dep=0;dep<DEP[u];dep++)
		{
			DP[u][0][dep]=W[u]*dist[dep];
			for(int k=1;k<=K;k++)DP[u][k][dep]=0;
		}
		return 0;
	}
	for(const int nxt:ET[u])GetDP(nxt);
	static int dist[101];
	for(int cur=u,c=0,dep=DEP[u];dep>=0;c+=LEN[cur],cur=FA[cur],dep--)dist[dep]=c;
	static int dp_yes[100][51];
	for(int k=0;k<=K;k++)dp_yes[0][k]=DP[ET[u][0]][k][DEP[u]];
	for(int ch=1;ch<(int)ET[u].size();ch++)
	{
		for(int k=0;k<=K;k++)dp_yes[ch][k]=INF;
		for(int k=0;k<=K;k++)for(int i=0;i+k<=K;i++)getmin(dp_yes[ch][i+k],dp_yes[ch-1][i]+DP[ET[u][ch]][k][DEP[u]]);
	}
	const int lastch=(int)ET[u].size()-1;
	for(int dep=0;dep<DEP[u];dep++)
	{
		static int dp_no[100][51];//i_th child, place j sawmill, min cost is dp[i][j]
		for(int k=0;k<=K;k++)dp_no[0][k]=DP[ET[u][0]][k][dep];
		for(int ch=1;ch<(int)ET[u].size();ch++)
		{
			for(int k=0;k<=K;k++)dp_no[ch][k]=INF;
			for(int k=0;k<=K;k++)for(int i=0;i+k<=K;i++)getmin(dp_no[ch][i+k],dp_no[ch-1][i]+DP[ET[u][ch]][k][dep]);
		}
		DP[u][0][dep]=dp_no[lastch][0]+W[u]*dist[dep];
		for(int k=1;k<=K;k++)DP[u][k][dep]=min(dp_no[lastch][k]+W[u]*dist[dep],dp_yes[lastch][k-1]);
	}
//	printf("u=%d\n",u);
//	for(int k=0;k<=K;k++)printf(" %d",dp_yes[lastch][k]);puts("");
	return dp_yes[lastch][K];
}
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d%d",&N,&K)==2),N++;
	W[0]=FA[0]=LEN[0]=-1;
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=1;i<N;i++)
	{
		assert(scanf("%d%d%d",&W[i],&FA[i],&LEN[i])==3);
		ET[FA[i]].push_back(i);
	}
	BuildDEP(0,0);
	const int ans=GetDP(0);
	printf("%d\n",ans);
	return 0;
}

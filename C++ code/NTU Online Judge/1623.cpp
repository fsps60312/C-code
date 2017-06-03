#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,P,G[100][100],S[100];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&P);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)scanf("%d",&G[i][j]);
		for(int i=0;i<N;i++)scanf("%d",&S[i]),--S[i];
		vector<int>a,b;
		bool vis[100];
		for(int i=0;i<N;i++)vis[i]=false;
		int ans=0;
		for(int i=0;i<N/2;i++)
		{
			static int ga[100],gb[100];
			for(int j=0;j<N;j++)if(!vis[j])
			{
				ga[j]=gb[j]=G[j][j];
				for(const int v:a)ga[j]+=G[j][v]+G[v][j];
				for(const int v:b)gb[j]+=G[j][v]+G[v][j];
			}
			int ta=-INF,sa=-1,sb=-1;
			for(int j=0;j<N;j++)if(!vis[j])
			{
				int ua=ga[j],ub=-INF,ssb=-1;
				for(int k=0;k<N;k++)if(!vis[k]&&k!=j)if(gb[k]>ub)ub=gb[k],ssb=k;
				assert(ub!=INF&&ssb!=-1);
				if(ua-ub>ta)ta=ua-ub,sa=j,sb=ssb;
			}
			assert(ta!=-INF&&sa!=-1&&sb!=-1);
			ans+=ta;
			vis[sa]=vis[sb]=true;
			a.push_back(sa),b.push_back(sb);
		}
		if(N&1)
		{
			for(int j=0;j<N;j++)if(!vis[j])
			{
				ans+=G[j][j];
				for(const int v:a)ans+=G[v][j]+G[j][v];
				vis[j]=true;
				break;
			}
		}
		printf("%d\n",P==1?ans:-ans);
		for(int j=0;j<N;j++)assert(vis[j]);
	}
	return 0;
}

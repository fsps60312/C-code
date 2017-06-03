#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N,M,A[100],B[100],DP[2][1000001];
vector<int>REC[2];
void Update(const int d,const int u,const int v)
{
	if(u>M||DP[d][u]>=v)return;
	if(DP[d][u]==-1)REC[d].push_back(u);
	DP[d][u]=v;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=1000000;i++)DP[0][i]=DP[1][i]=-1;
	static int casenumber;scanf("%d",&casenumber);
	while(casenumber--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d%d",&A[i],&B[i]);
		DP[0][0]=0;
		assert(REC[0].empty()&&REC[1].empty());
		REC[0].push_back(0);
		int d=0;
		for(int i=0;i<N;i++,d^=1)
		{
			for(const auto u:REC[d])
			{
				assert(DP[d][u]!=-1);
				Update(d^1,u,DP[d][u]);
				Update(d^1,u+A[i],DP[d][u]+B[i]);
				DP[d][u]=-1;
			}
			REC[d].clear();
		}
		int ans=0;
		for(const auto u:REC[d])
		{
			if(DP[d][u]>ans)ans=DP[d][u];
			DP[d][u]=-1;
		}
		REC[d].clear();
		printf("%d\n",ans);
	}
	return 0;
}

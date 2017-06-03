#include<cstdio>
#include<vector>
using namespace std;
#define LL long long
int TRA[24][6]=
{
	{0,1,2,3,4,5},{0,4,1,2,3,5},{0,3,4,1,2,5},{0,2,3,4,1,5},
	{1,5,2,0,4,3},{1,4,5,2,0,3},{1,0,4,5,2,3},{1,2,0,4,5,3},
	{5,3,2,1,4,0},{5,4,3,2,1,0},{5,1,4,3,2,0},{5,2,1,4,3,0},
	{3,0,2,5,4,1},{3,4,0,2,5,1},{3,5,4,0,2,1},{3,2,5,4,0,1},
	{4,1,0,3,5,2},{4,5,1,0,3,2},{4,3,5,1,0,2},{4,0,3,5,1,2},
	{2,1,5,3,0,4},{2,0,1,5,3,4},{2,3,0,1,5,4},{2,5,3,0,1,4}
};
int VIS[6];
LL GetCYC(int i,int j)
{
	int u=TRA[i][j];
	for(LL ans=1LL;;ans++,u=TRA[i][u])
	{
		VIS[u]=1;
		if(u==j)return ans;
	}
}
vector<LL> CYC[24];
LL N,POW[7];
int main()
{
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<6;j++)VIS[j]=0;
		for(int j=0;j<6;j++)
		{
			if(VIS[j])continue;
			CYC[i].push_back(GetCYC(i,j));
		}
//		for(int j=0;j<CYC[i].size();j++)printf(" %d",CYC[i][j]);puts("");
	}
	while(scanf("%lld",&N)==1&&N)
	{
		POW[0]=1LL;
		for(int i=1;i<=6;i++)POW[i]=POW[i-1]*N;
		LL ans=0LL;
		for(int i=0;i<24;i++)
		{
			ans+=POW[CYC[i].size()];
		}
		if(ans%24LL)puts("error\n");
		printf("%lld\n",ans/24LL);
	}
	return 0;
}

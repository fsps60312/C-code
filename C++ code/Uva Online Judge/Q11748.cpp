#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
int N,M,C;
int RANK[100][100];
bool Win(const int a,const int b)
{
	int avote=0,bvote=0;
	for(int i=0;i<M;i++)
	{
		if(RANK[i][a]<RANK[i][b])avote++;
		else bvote++;
	}
	return avote>bvote;
}
bool WIN[100][100];
bool VIS[100];
int main()
{
	for(;;)
	{
		assert(scanf("%d%d%d",&N,&M,&C)==3);
		if(N==0&&M==0&&C==0)break;
		C--;
		for(int i=0;i<M;i++)
		{
			static int tmp[100];
			for(int j=0;j<N;j++)assert(scanf("%d",&tmp[j])==1),tmp[j]--;
			for(int j=0;j<N;j++)RANK[i][tmp[j]]=j;
		}
		for(int i=0;i<N;i++)
		{
			for(int j=i+1;j<N;j++)
			{
				bool iwin=Win(i,j);
				WIN[i][j]=iwin;
				WIN[j][i]=(!iwin);
			}
		}
		for(int i=0;i<N;i++)VIS[i]=false;
		queue<int>q;
		q.push(C);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			if(VIS[u])continue;
			VIS[u]=true;
			for(int i=0;i<N;i++)if(i!=u&&WIN[u][i])q.push(i);
		}
		bool ans=true;
		for(int i=0;i<N;i++)if(!VIS[i]){ans=false;break;}
		puts(ans?"yes":"no");
	}
	return 0;
}

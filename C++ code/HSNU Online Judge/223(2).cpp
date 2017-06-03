#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int T,N,M,V,E,I[300000],CNT;
vector<int>CYC[300000];
vector<bool>VIS;
void Dfs(const int &u,const int &cnt)
{
	if(CNT++)printf(" ");
	printf("%d",u%N);
	for(int i=0;i<N;i++)if(CYC[u][i]!=-1&&!VIS[CYC[u][i]])
	{
		int c=CYC[u][i];
		CYC[u][i]=-1;
		VIS[c]=true;
		Dfs(u*N%V+i,c);
		VIS[c]=false;
	}
	for(int i=0;i<N;i++)if(CYC[u][i]!=-1)
	{
		CYC[u][i]=-1;
		Dfs(u*N%V+i,cnt);
		return;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		V=1;
		for(int i=1;i<M;i++)V*=N;
		E=V*N;
		for(int i=0;i<V;i++)
		{
			CYC[i].reserve(N);
			for(int j=0;j<N;j++)
			{
				CYC[i].push_back(-1);
			}
			I[i]=N-1;
		}
		for(int i=0,cnt=0;i<V;i++)
		{
			if(I[i]==-1)continue;
			int u=i;
			for(;;)
			{
				if(I[u]==-1)break;
				CYC[u][I[u]]=cnt;
				u=u*N%V+I[u];
				I[u]--;
			}
			cnt++;
			VIS.push_back(false);
//			i--;
		}
		for(int i=0;i<V;i++)
		{
			for(int j=0;j<N;j++)printf(" %d",CYC[i][j]);puts("");
		}
		CNT=0;
		VIS[0]=false;
		Dfs(0,0);
		assert(CNT==E);
		puts("");
	}
	return 0;
}

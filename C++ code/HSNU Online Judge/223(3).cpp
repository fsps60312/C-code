#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int T,N,M,V,E,CNT,TAG[300000];
struct Edge
{
	int b,g;
	Edge(){}
	Edge(const int &_b,const int &_g):b(_b),g(_g){}
};
vector<Edge>ET[300000];
vector<bool>VIS;
void Dfs(const int &u,const int &g)
{
	if(CNT++)
	{
		if(CNT>=3)printf(" ");
		if(CNT>=2)printf("%d",u%N+1);
	}
	for(Edge &e:ET[u])
	{
		if(e.g==-1||VIS[e.g])continue;
		int c=e.g;
		e.g=-1;
		VIS[c]=true;
		Dfs(e.b,c);
		VIS[c]=false;
	}
	for(Edge &e:ET[u])
	{
		if(e.g!=g)continue;
		e.g=-1;
		Dfs(e.b,g);
		return;
	}
}
void Tag(const int &u,const int &g)
{
	for(Edge &e:ET[u])
	{
		if(e.g!=-1)continue;
		e.g=g;
		Tag(e.b,g);
		break;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		if(M==1)
		{
			printf("1");
			for(int i=2;i<=N;i++)printf(" %d",i);
			puts("");
			continue;
		}
		V=1;
		for(int i=1;i<M;i++)V*=N;
		E=V*N;
		for(int i=0;i<V;i++)
		{
			ET[i].clear();
			for(int j=0;j<N;j++)ET[i].push_back(Edge(i*N%V+j,-1));
			TAG[i]=N;
		}
		for(int i=0,g=0;i<V;i++)
		{
			if(TAG[i]==0)continue;
			int u=i;
			Tag(u,g);
			g++;
			VIS.push_back(false);
		}
//		for(int i=0;i<V;i++)
//		{
//			for(int j=0;j<N;j++)printf(" %d",ET[i][j].g);puts("");
//		}
		CNT=0;
		VIS[0]=true;
		Dfs(0,0);
		assert(CNT==E+1);
		puts("");
	}
	return 0;
}

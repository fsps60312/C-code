#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,K;
vector<int>ET[100000];
int H1[100000],H2[100000],I1[100000],I2[100000];
void Update(const int &u,const int &h,const int &i)
{
	if(h>=H1[u])H2[u]=H1[u],I2[u]=I1[u],H1[u]=h,I1[u]=i;
	else if(h>=H2[u])H2[u]=h,I2[u]=i;
}
void Dfs1(const int &u,const int &fa)
{
	for(const int &et:ET[u])
	{
		if(et==fa)continue;
		Dfs1(et,u);
		Update(u,H1[et]+1,et);
	}
}
void Dfs2(const int &u,const int &fa)
{
	if(fa!=-1)
	{
		if(I1[fa]!=u)Update(u,H1[fa]+1,fa);
		else if(I2[fa]!=-1)Update(u,H2[fa]+1,fa);
	}
	for(const int &et:ET[u])
	{
		if(et==fa)continue;
		Dfs2(et,u);
	}
}
int main()
{
	while(scanf("%d%d",&N,&K)==2)
	{
		assert(K==1);
		for(int i=1;i<N;i++)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)H1[i]=H2[i]=0,I1[i]=I2[i]=-1;
		Dfs1(0,-1);
		Dfs2(0,-1);
		int ans=0;
		for(int i=0;i<N;i++)if(I2[i]!=-1&&H1[i]+H2[i]>ans)ans=H1[i]+H2[i];
		printf("%d\n",(N-1)*2-ans+1);
	}
	return 0;
}

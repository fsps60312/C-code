#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,DEP[5000];
vector<int>ET[5000];
vector<int>FA[5000];
void Dfs(const int u,const int fa,const int dep)
{
	DEP[u]=dep;
	FA[u].clear();
	if(fa!=-1)for(int i=0,cur=fa;;cur=FA[cur][i++])
	{
		FA[u].push_back(cur);
		if(i>=(int)FA[cur].size())break;
	}
	for(const auto nxt:ET[u])if(nxt!=fa)Dfs(nxt,u,dep+1);
}
int GetLCA(int a,int b)
{
	if(DEP[a]<DEP[b])swap(a,b);
	for(int i=30,dis=DEP[a]-DEP[b];i>=0;i--)if(dis&(1<<i))a=FA[a][i];
	assert(DEP[a]==DEP[b]);
	if(a==b)return a;
	for(int i=30;i>=0;i--)if(i<(int)FA[a].size()&&FA[a][i]!=FA[b][i])a=FA[a][i],b=FA[b][i];
	assert(FA[a][0]==FA[b][0]);
	return FA[a][0];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),a--,b--,ET[a].push_back(b),ET[b].push_back(a);
		Dfs(0,-1,0);
		static int querycount;scanf("%d",&querycount);
		while(querycount--)
		{
			static int a,b,c;scanf("%d%d",&a,&b);
			c=GetLCA(--a,--b);
			const int dis=(DEP[a]-DEP[c])+(DEP[b]-DEP[c]);
			int u=(DEP[a]>DEP[b]?a:b);
			for(int i=30,tmp=dis/2;i>=0;i--)if(tmp&(1<<i))u=FA[u][i];
			if(dis&1)
			{
				const int v=FA[u][0];
				printf("The fleas jump forever between %d and %d.\n",min(u,v)+1,max(u,v)+1);
			}
			else printf("The fleas meet at %d.\n",u+1);
		}
	}
	return 0;
}

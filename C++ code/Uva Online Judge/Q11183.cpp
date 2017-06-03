#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#include<cassert>
using namespace std;
const int INF=2147483647;
int T,N,M;
map<int,int>AD[1000];
map<int,int>RA[1000];
int FA[1000],DJ[1000];
bool VIS[1000];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
void Dfs(int u,int &ans)
{
	if(VIS[u])
	{
		vector<
	}
	VIS[u]=true;
	Dfs(FA[u],ans);
}
int Solve()
{
	for(int i=0;i<N;i++)DJ[i]=i,VIS[i]=false;
	int ans=0;
	for(int i=0;i<N;i++)
	{
		FA[i]=RA[i].begin()->first;
		ans+=RA[i].begin()->second;
		DJ[FindDJ(i)]=FindDJ(FA[i]);
	}
	for(int i=0;i<N;i++)
	{
		if(VIS[i])continue;
		Dfs(i,ans);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			for(int i=0;i<N;i++)
			{
				AD[i].clear();
				RA[i].clear();
			}
			for(int i=0;i<M;i++)
			{
				int a,b,c;
				scanf("%d%d%d",&a,&b,&c);
				assert(AD[a].find(b)==AD[a].end()&&RA[b].find(a)==RA[b].end());
				AD[a][b]=c;
				RA[b][a]=c;
			}
			static int kase=1;
			printf("Case #%d: ",kase++);
			int ans=Solve();
			if(ans==-1)puts("Possums!");
			else printf("%d\n",ans);
		}
	}
}

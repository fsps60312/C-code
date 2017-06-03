#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,P,VIS[60];
vector<int>TO[60];
void AddEdge(int a,int b){TO[a].push_back(b);TO[b].push_back(a);}
int dfs(int u,int c)
{
	if(VIS[u])
	{
		if(VIS[u]!=c)return 0;
		return VIS[u];
	}
	VIS[u]=c;
	printf("u=%d%c(%d)\n",u>>1,(u&1)?'w':'h',c);
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(!dfs(j,3-c))return 0;
	}
	return VIS[u];
}
int solve()
{
	for(int i=0;i<N*2;i++)
	{
		if(VIS[i])continue;
		if(!dfs(i,1))return 0;
	}
	return VIS[0];
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&P)==2&&(N||P))
	{
		for(int i=0;i<N*2;i++)
		{
			TO[i].clear();
			VIS[i]=0;
		}
		for(int i=0;i<N;i++)AddEdge(i*2,i*2+1);
		for(int i=0,a,b;i<P;i++)
		{
			static char c1,c2;
			scanf("%d%c%d%c",&a,&c1,&b,&c2);
			a<<=1,b<<=1;
			if(c1=='w')a++;
			if(c2=='w')b++;
			AddEdge(a,b);
		}
		int result=solve();
//		for(int i=0;i<N;i++)printf("%d %d\n",VIS[i*2],VIS[i*2+1]);
		if(!result)printf("bad luck\n");
		else
		{
			vector<int>ans;
			for(int i=0;i<N*2;i++)if(VIS[i]==result)ans.push_back(i);
			sort(ans.begin(),ans.end());
			for(int i=0;i<N;i++)printf("%d%c%c",ans[i]>>1,(ans[i]&1)?'w':'h',i==N-1?'\n':' ');
		}
	}
	return 0;
}

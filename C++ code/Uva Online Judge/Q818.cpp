#include<cstdio>
#include<vector>
using namespace std;
int max(int a,int b){return a>b?a:b;}
int N,DEG[15];
bool VIS[15],EDGE[15][15];
vector<int>ADJ[15];
int dfs(int u)
{
	if(VIS[u])return 0;
	VIS[u]=true;
	int ans=0;
	if(DEG[u]&1)ans++;
	for(int i=0;i<ADJ[u].size();i++)
	{
		int &j=ADJ[u][i];
		ans+=dfs(j);
	}
	return ans;
}
int solve()
{
	bool noedge=true;
	int ans=0;
	for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==-1&&b==-1);)
	{
		a--,b--;
		if(EDGE[a][b]){ans++;continue;}
		EDGE[a][b]=EDGE[b][a]=true;
		noedge=false;
		ADJ[a].push_back(b);
		ADJ[b].push_back(a);
		DEG[a]++,DEG[b]++;
	}
	if(noedge)return N-1;
	bool allloop=true;
	int cnt=0;
	for(int i=0,v,d;i<N;i++)
	{
		if(VIS[i])continue;
		cnt++;
		d=dfs(i);
		if(d)allloop=false;
		v=DEG[i]?max(d/2,1):1;
		printf("v=%d\n",v);
		ans+=v;
	}
	printf("cnt=%d\n",cnt);
	if(allloop&&cnt>1)ans++;
	ans--;
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			VIS[i]=false;
			DEG[i]=0;
			ADJ[i].clear();
			for(int j=0;j<N;j++)EDGE[i][j]=false;
		}
		static int kase=1;
		printf("Set %d: Minimum links to open is %d\n",kase++,solve());
	}
	return 0;
}

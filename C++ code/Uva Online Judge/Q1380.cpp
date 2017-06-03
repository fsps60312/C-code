#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30; 
struct Edge
{
	int to,type;
};
vector<Edge> EDGE;
vector<int> GETO[201];
int N,K;
void init(int n);
void add_EDGE(int from,int to,char type);
struct UpDown
{
	int up;
	int down;
};
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
int dfs_K(int u,int fa);
void get_K(){K=0;for(int i=1;i<=N;i++)getmax(K,dfs_K(i,-1)+1);}
bool cmp_UpDown(UpDown a,UpDown b){return a.down<b.down;}
int max(int a,int b){return a>b?a:b;}
UpDown F[201];
UpDown dfs(int u,int fa)
{
	printf("\tAt %d\n",u);
	UpDown &ans=F[u]=(UpDown){0,0};
	vector<UpDown>v;
	for(int i=0;i<GETO[u].size();i++)
	{
		Edge &e=EDGE[GETO[u][i]];
		if(e.to==fa)continue;
		UpDown ud=dfs(e.to,u);
		if(ud.up==INF)
		{
			ans.up=INF;
			return ans;
		}
		if(e.type==1)getmax(ans.down,ud.down+1);
		else if(e.type==2)getmax(ans.up,ud.up+1);
		else v.push_back(ud);
	}
	printf("%da: %d %d\n",u,ans.up,ans.down);
	if(!v.size())return ans;
	sort(v.begin(),v.end(),cmp_UpDown);
	int sz=v.size();
	int up[sz+1];
	up[sz]=0;
	up[sz-1]=v[sz-1].up+1;
	for(int i=sz-2;i>=0;i--)
	{
		if(up[i+1]==INF||v[i].up==INF)up[i]=INF;
		else up[i]=max(up[i+1],v[i].up+1);
	}
	bool found=false;
	UpDown now=(UpDown){INF,INF};
	for(int i=0;i<sz;i++)
	{
		if(v[i].down==INF)break;
		int d=v[i].down+1,&u=up[i+1];
		if(u==INF||d+u+1>K)continue;
		found=true;
		getmin(now.down,d);
		getmin(now.up,u);
	}
	if(!found)ans.up=INF;
	else
	{
		getmax(ans.up,now.up);
		getmax(ans.down,now.down);
	}
	printf("und: %d %d\n",now.up,now.down);
	printf("%db: %d %d\n",u,ans.up,ans.down);
	return ans;
}
int main()
{
	freopen("inn.txt","r",stdin);
	while(1)
	{
		int n;
		N=0;
		EDGE.clear();
		while(scanf("%d",&n)==1&&n)
		{
//			printf("N=%d\n",n);
			init(n);
			int a;char c;
			while(scanf("%d%c",&a,&c)==2&&a){init(a);add_EDGE(n,a,c);}
		}
		if(!N)break;
		get_K();
		printf("K=%d\n",K);
		bool found=false;
		for(int i=1;i<=N;i++)
		{
			printf("\n\troot %d\n",i);
			UpDown ud=dfs(i,-1);
//			for(int j=1;j<=N;j++)
//			{
//				printf("%d: %d %d\n",j,F[j].down,F[j].up);
//			}
			if(ud.up!=INF)
			{
				found=true;
				break;
			}
		}
		printf("%d\n",found?K:K+1);
	}
	return 0;
}
int dfs_K(int u,int fa)
{
	int ans=0;
	for(int i=0;i<GETO[u].size();i++)
	{
		Edge &e=EDGE[GETO[u][i]];
		if(e.to==fa||e.type!=1)continue;
		getmax(ans,dfs_K(e.to,u)+1);
	}
	return ans;
}
void init(int n)
{
	while(N<n)
	{
		N++;
		GETO[N].clear();
	}
}
void add_EDGE(int from,int to,char type)
{
	int t1,t2;
	if(type=='d')t1=1,t2=2;
	else if(type=='u')t1=2,t2=1;
	else t1=t2=0;
	GETO[from].push_back(EDGE.size());
	EDGE.push_back((Edge){to,t1});
	GETO[to].push_back(EDGE.size());
	EDGE.push_back((Edge){from,t2});
}

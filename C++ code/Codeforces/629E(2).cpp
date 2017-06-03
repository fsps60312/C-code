#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,M;
vector<int>ET[100000],PARENT[100000];
int DEPTH[100000],SZ[100000];
LL SUM[100000];
void Dfs(const int u,const int parent,const int depth)
{
	PARENT[u].clear();
	DEPTH[u]=depth;
	if(parent!=-1)
	{
		for(int cur=parent,i=0;;cur=PARENT[cur][i++])
		{
			PARENT[u].push_back(cur);
			if((1<<i)>DEPTH[cur])break;
		}
	}
	int &sz=SZ[u]=1;
	LL &sum=SUM[u]=0LL;
	for(const int nxt:ET[u])if(nxt!=parent)Dfs(nxt,u,depth+1),sz+=SZ[nxt],sum+=SUM[nxt]+SZ[nxt];
}
LL REVSUM[100000];
void CalRevSum(const int u,const int parent,const LL &now)
{
	REVSUM[u]=now;
	for(const int nxt:ET[u])if(nxt!=parent)CalRevSum(nxt,u,now+SUM[u]-(SUM[nxt]+SZ[nxt])+(N-SZ[nxt]));
}
int GetLCA(int a,int b)
{
	assert(DEPTH[a]>=DEPTH[b]);
	for(int i=30,dis=DEPTH[a]-DEPTH[b];i>=0;i--)if(dis&(1<<i))a=PARENT[a][i];
	assert(DEPTH[a]==DEPTH[b]);
	if(a==b)return a;
	for(int i=30;i>=0;i--)if((1<<i)<=DEPTH[a]&&PARENT[a][i]!=PARENT[b][i])a=PARENT[a][i],b=PARENT[b][i];
	assert(PARENT[a][0]==PARENT[b][0]);
	return PARENT[a][0];
}
double Solve(const int a,const int b)
{
	const int lca=GetLCA(a,b);
	assert(lca!=a);
	LL suma,sumb,sza,szb;
	if(lca==b)
	{
		int cur=a;
		for(int i=30,dis=DEPTH[a]-DEPTH[b]-1;i>=0;i--)if(dis&(1<<i))cur=PARENT[cur][i];
//		printf("(a,b)=(%d,%d),cur=%d,revsum=%lld,sz=%d\n",a+1,b+1,cur,REVSUM[cur]-(N-SZ[cur]),N-SZ[cur]);
		suma=SUM[a],sumb=REVSUM[cur]-(N-SZ[cur]);
		sza=SZ[a],szb=N-SZ[cur];
	}
	else suma=SUM[a],sumb=SUM[b],sza=SZ[a],szb=SZ[b];
	return 1.0+DEPTH[a]+DEPTH[b]-2LL*DEPTH[lca]+(double)(suma*szb+sumb*sza)/sza/szb;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		Dfs(0,-1,0);
		CalRevSum(0,-1,0LL);
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			if(DEPTH[a]<DEPTH[b])swap(a,b);
			printf("%.9f\n",Solve(a,b));
		}
	}
	return 0;
}

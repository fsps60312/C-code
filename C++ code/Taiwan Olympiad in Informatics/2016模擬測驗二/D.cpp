#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,P;
vector<int>ET[500];
void Bfs(const int root,int *dist)
{
	queue<int>q;
	for(int i=0;i<N;i++)dist[i]=INF;
	q.push(root),dist[root]=0;
	int cnt=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		++cnt;
		for(const int nxt:ET[u])if(dist[nxt]==INF)
		{
			dist[nxt]=dist[u]+1;
			q.push(nxt);
		}
	}
	assert(cnt==N);
}
int W[500],DIST[500][500];
int Solve1()
{
	int ans=INF;
	for(int i=0;i<N;i++)
	{
		int ta=0;
		for(int j=0;j<N;j++)if(j!=i)ta+=W[j]*DIST[j][i];
		getmin(ans,ta);
	}
	return ans;
}
int DP[500][500],SZ[500][500];
int GetSZ(const int u,const int parent)
{
	int &sz=SZ[u][parent];
	if(sz!=-1)return sz;
	sz=W[u];
	for(const int nxt:ET[u])if(nxt!=parent)sz+=GetSZ(nxt,u);
	return sz;
}
void GetChilds(const int u,const int parent,vector<int>&ans)
{
	ans.push_back(u);
	for(const int nxt:ET[u])if(nxt!=parent)GetChilds(nxt,u,ans);
}
int GetDP(const int u,const int parent)
{
	int &dp=DP[u][parent];
	if(dp!=-1)return dp;
	vector<int>childs;
	GetChilds(u,parent,childs);
	dp=0;
	for(const int v:childs)dp+=W[v]*DIST[v][u];
	return dp;
}
bool SELECTED[500];
void Fill(const int u,const int parent,int &cnt)
{
	if(cnt==P)return;
	SELECTED[u]=true,++cnt;
	for(const int nxt:ET[u])if(nxt!=parent)Fill(nxt,u,cnt);
}
int Cost(const int u)
{
	assert(SELECTED[u]);
	int ans=0;
	for(const int nxt:ET[u])if(!SELECTED[nxt])ans+=GetDP(nxt,u)+GetSZ(nxt,u);
	return ans;
}
#include<utility>
int Solve2()
{
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)DP[i][j]=SZ[i][j]=-1;
	for(int i=0;i<N;i++)SELECTED[i]=false;
	{int cnt=0;Fill(0,-1,cnt);}
	int now=0;
	for(int i=0;i<N;i++)if(SELECTED[i])now+=Cost(i);
	for(;;)
	{
		vector<int>s;
		for(int i=0;i<N;i++)if(SELECTED[i])s.push_back(i);
		static vector<pair<int,int> >out[500];
		vector<int>in[500];
		for(const int u:s)out[u].clear(),in[u].clear();
		for(const int u:s)
		{
			for(const int nxt:ET[u])
			{
				if(!SELECTED[nxt])out[u].push_back(make_pair(GetSZ(nxt,u),nxt));
				else in[u].push_back(GetSZ(u,nxt));
			}
		}
		for(const int a:s)if((int)in[a].size()==1)
		{
			const int increased=in[a][0];
			for(const int b:s)if(a!=b)
			{
				for(const auto &p:out[b])
				{
					const int decreased=p.first;
					if(decreased>increased)
					{
						now+=increased-decreased;
						SELECTED[a]=false;
						SELECTED[p.second]=true;
						goto check_again;
					}
				}
			}
		}
		break;
		check_again:;
	}
//	puts("pass");
	return now;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&P);
//	assert(P<=N);
	if(P>N)P=N;
	for(int i=0;i<N;i++)scanf("%d",&W[i]);
	for(int i=0;i<N;i++)
	{
		ET[i].clear();
		int cnt;scanf("%d",&cnt);
		for(int v;cnt--;)scanf("%d",&v),ET[i].push_back(--v);
	}
	for(int i=0;i<N;i++)Bfs(i,DIST[i]);
	if(P==1)printf("%d\n",Solve1());
	else printf("%d\n",Solve2());
	return 0;
}

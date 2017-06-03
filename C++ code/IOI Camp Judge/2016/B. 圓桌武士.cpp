#include<cstdio>
#include<cassert>
#include<vector>
#include<stack>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M;
vector<int>ET[1000];
int PRE[1000],LOW[1000],PRE_CNT;
bool CUT[1000],ANS[1000],VIS[1000];
vector<vector<int> >BCC;
stack<int>STK;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	CUT[u]=false;
	STK.push(u);
	int chcnt=0;
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		if(!PRE[nxt])
		{
			chcnt++;
			Dfs(nxt,u);
			getmin(LOW[u],LOW[nxt]);
			if(LOW[nxt]>=PRE[u])CUT[u]=true;
		}
		else if(!VIS[nxt])getmin(LOW[u],PRE[nxt]);
	}
	if(fa==-1)CUT[u]=(chcnt>=2);
}
int COLOR[1000];
bool IsBipartite(const int u,const int color)
{
	if(COLOR[u]==-2)return false;
	if(COLOR[u]!=-1)return COLOR[u]!=color;
	COLOR[u]=color;
	for(const int nxt:ET[u])if(IsBipartite(nxt,color^1))return true;
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		if(true)
		{
			static bool edge[1000][1000];
			for(int i=0;i<N;i++)for(int j=0;j<N;j++)edge[i][j]=false;
			for(int i=0,a,b;i<M;i++)
			{
				scanf("%d%d",&a,&b),a--,b--;
				edge[a][b]=edge[b][a]=true;
			}
			for(int i=0;i<N;i++)
			{
				ET[i].clear();
				for(int j=0;j<N;j++)if(!edge[i][j])ET[i].push_back(j);
			}
		}
		BCC.clear();
		for(int i=0;i<N;i++)PRE[i]=0,VIS[i]=false;
		PRE_CNT=0;
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1),assert(STK.empty());
		for(int i=0;i<N;i++)ANS[i]=false,COLOR[i]=-2;
		for(const auto &bcc:BCC)if((int)bcc.size()>1)
		{
			for(const int v:bcc)printf("%d ",v+1);puts("");
			for(const int v:bcc)VIS[v]=false,COLOR[v]=-1;
			if(IsBipartite(bcc[0],0))for(const int v:bcc)ANS[v]=true;
			for(const int v:bcc)COLOR[v]=-2;
		}
		int ans=0;
		for(int i=0;i<N;i++)if(!ANS[i])ans++;
		printf("%d\n",ans);
	}
	return 0;
}

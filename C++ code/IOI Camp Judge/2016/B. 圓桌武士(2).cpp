#include<cstdio>
#include<cassert>
#include<vector>
#include<stack>
//#include<algorithm>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M;
vector<int>ET[1000];
int PRE[1000],LOW[1000],PRE_CNT;
bool ANS[1000],VIS[1000];
vector<vector<int> >BCC;
stack<int>STK;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	int chcnt=0;
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		if(!PRE[nxt])
		{
			chcnt++;
			STK.push(u),STK.push(nxt);
			Dfs(nxt,u);
			getmin(LOW[u],LOW[nxt]);
			if(LOW[nxt]>=PRE[u])
			{
				vector<int>bcc;
				for(;;)
				{
					int a,b;
					a=STK.top(),STK.pop(),b=STK.top(),STK.pop();
					bcc.push_back(a),bcc.push_back(b);
					if(a==nxt&&b==u)break;
				}
				BCC.push_back(bcc);
			}
		}
		else if(!VIS[nxt])getmin(LOW[u],PRE[nxt]);
	}
}
int COLOR[1000];
bool IsBipartite(const int u,const int color)
{
	if(COLOR[u]==-2)return true;
	if(COLOR[u]!=-1)return COLOR[u]==color;
	COLOR[u]=color;
	for(const int nxt:ET[u])if(!IsBipartite(nxt,color^1))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
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
				for(int j=0;j<N;j++)if(j!=i&&!edge[i][j])ET[i].push_back(j);
			}
		}
		for(int i=0;i<N;i++)PRE[i]=0,VIS[i]=false;
		BCC.clear();
		PRE_CNT=0;
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1),assert(STK.empty());
		for(int i=0;i<N;i++)ANS[i]=false,COLOR[i]=-2;
		for(const auto &bcc:BCC)
		{
//			for(const int v:bcc)printf("%d ",v+1);puts("");
			for(const int v:bcc)VIS[v]=false,COLOR[v]=-1;
			if(!IsBipartite(bcc[0],0))for(const int v:bcc)ANS[v]=true;
			for(const int v:bcc)COLOR[v]=-2;
		}
		int ans=0;
		for(int i=0;i<N;i++)if(!ANS[i])ans++;
		printf("%d\n",ans);
	}
	return 0;
}

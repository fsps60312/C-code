#include<cstdio>
#include<vector>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int end[2],type;
	Edge(){}
	Edge(const int _a,const int _b,const int _t):end{_a,_b},type(_t){}
};
vector<Edge>EDGE;
vector<int>ET[2000];
int PRE[2000],LOW[2000],PRE_CNT;
vector<Edge>ANS;
void Dfs(const int u,const int fa)
{
//	printf("u=%d\n",u);
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const int ei:ET[u])
	{
//		printf("e=%d\n",ei);
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.end[0]?e.end[1]:e.end[0]);
		if(!PRE[nxt])
		{
			Dfs(nxt,u);
			getmin(LOW[u],LOW[nxt]);
			if(e.type==2)ANS.push_back(Edge(u,nxt,LOW[nxt]>LOW[u]?2:1));
		}
		else if(PRE[nxt]<PRE[u]&&nxt!=fa)
		{
			getmin(LOW[u],PRE[nxt]);
			if(e.type==2)ANS.push_back(Edge(u,nxt,1));
		}
	}
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),PRE[i]=0;
		PRE_CNT=0;
		EDGE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--,EDGE.push_back(Edge(a,b,c)),ET[a].push_back(i);
			if(c==2)ET[b].push_back(i);
		}
		ANS.clear();
		for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1);
		for(const auto &ans:ANS)printf("%d %d %d\n",ans.end[0]+1,ans.end[1]+1,ans.type);
	}
	return 0;
}

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
void Dfs(const int u)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const int ei:ET[u])
	{
		Edge &e=EDGE[ei];
		if(e.type!=-1&&e.end[e.type]==u)continue;
		const int pred=e.type;
		e.type=(u==e.end[0]?1:0);
		const int nxt=e.end[e.type];
		if(!PRE[nxt])
		{
			Dfs(nxt);
			getmin(LOW[u],LOW[nxt]);
			if(pred==-1)ANS.push_back(Edge(u,nxt,LOW[nxt]>LOW[u]?2:1));
		}
		else
		{
			getmin(LOW[u],PRE[nxt]);
			if(pred==-1)ANS.push_back(Edge(u,nxt,1));
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
		EDGE.clear(),ANS.clear();
		for(int i=0,a,b,c;i<M;i++)scanf("%d%d%d",&a,&b,&c),a--,b--,EDGE.push_back(Edge(a,b,c==2?-1:c)),ET[a].push_back(i),ET[b].push_back(i);
		Dfs(0);
		for(const auto &ans:ANS)printf("%d %d %d\n",ans.end[0]+1,ans.end[1]+1,ans.type);
	}
	return 0;
}

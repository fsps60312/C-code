#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<int>ET[50000];
vector<Edge>EDGE;
int N,M,PRE[50000],LOW[50000],PRE_CNT,ANS;
void Dfs(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	int chsz=0;
	for(const int ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(e.a==u?e.b:e.a);
		if(!PRE[nxt])
		{
			Dfs(nxt,ei);
			getmin(LOW[u],LOW[nxt]);
			chsz++;
		}
		else getmin(LOW[u],PRE[nxt]);
	}
	if((fa!=-1&&LOW[u]==PRE[u]&&chsz)||(fa==-1&&chsz>1))ANS++;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		EDGE.push_back(Edge(a,b));
		ET[a].push_back(i),ET[b].push_back(i);
	}
	for(int i=0;i<N;i++)PRE[i]=0;
	PRE_CNT=ANS=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i,-1);
	printf("%d\n",ANS);
	return 0;
}

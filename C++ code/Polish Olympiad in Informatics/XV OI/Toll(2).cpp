#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
int N,M;
vector<int>ET[100000];
int MATCH[200000];
bool VIS[200000];
vector<int>CHANGED;
bool Match(const int u)
{
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(!VIS[nxt])
		{
			VIS[nxt]=true;
			CHANGED.push_back(nxt);
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
			}
		}
	}
	return false;
}
bool Solve()
{
	for(int i=0;i<M;i++)MATCH[i]=-1;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<(int)CHANGED.size();j++)VIS[CHANGED[j]]=false;
		CHANGED.clear();
		if(!Match(i))return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		if(!Solve())puts("NIE");
		else
		{
			puts("TAK");
			static int ans[100000];
			for(int i=0;i<M;i++)if(MATCH[i]!=-1)ans[MATCH[i]]=i;
			for(int i=0;i<N;i++)
			{
				const Edge e=EDGE[ans[i]];
				const int nxt=(e.b==i?e.a:e.b);
				printf("%d\n",nxt+1);
			}
		}
	}
	return 0;
}

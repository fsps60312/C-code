#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
struct Edge
{
	int a,b;
	bool vis;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b),vis(false){}
};
vector<Edge>EDGE;
vector<int>ET[50000],ANS;
int N,M;
void Dfs(const int u)
{
	for(const int ei:ET[u])
	{
		Edge &e=EDGE[ei];
		if(e.vis)continue;
		const int nxt=(e.a==u?e.b:e.a);
		e.vis=true;
		Dfs(nxt);
	}
	ANS.push_back(u);
}
int main()
{
	scanf("%d%d",&N,&M);
	static int deg[50000];
	for(int i=0;i<N;i++)ET[i].clear(),deg[i]=0;
	for(int i=0;i<M;i++)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		EDGE.push_back(Edge(a,b));
		ET[a].push_back(i),ET[b].push_back(i);
		deg[a]++,deg[b]++;
	}
	ANS.clear();
	bool found=false;
	for(int i=0;i<N;i++)if(deg[i]&1){Dfs(i);found=true;break;}
	if(!found)Dfs(0);
//	printf("sz=%d\n",ANS.size());
	assert((int)ANS.size()==M+1);
	for(int i=M;i>0;i--)printf("%d %d\n",ANS[i]+1,ANS[i-1]+1);
	return 0;
}

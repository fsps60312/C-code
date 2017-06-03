#include<cstdio>
#include<vector>
#include<stack>
#include<cassert>
using namespace std;
int N,M;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
int IN[100000];
bool VIS[1000000],P[100000];
vector<vector<int> >ANS;
stack<int>STK;
bool Dfs(const int u,const int fa,const int s)
{
	if(P[u])
	{
		vector<int>ans;
		ans.push_back(u);
		while(STK.top()!=u)ans.push_back(STK.top()),P[STK.top()]=false,STK.pop();
		ans.push_back(u);
		ANS.push_back(ans);
	}
	else STK.push(u),P[u]=true;
	if(fa!=-1&&u==s)return true;
	while(IN[u]>=0&&VIS[ET[u][IN[u]]])IN[u]--;
	if(IN[u]==-1)
	{
		assert(fa==-1);
		STK.pop();P[u]=false;
		assert(STK.empty());
		return false;
	}
	Edge &e=EDGE[ET[u][IN[u]]];
	VIS[ET[u][IN[u]]]=true;
	assert(Dfs(u==e.b?e.a:e.b,u,s));
	return true;
}
bool Solve()
{
	for(int i=0;i<N;i++)if(IN[i]%2==1)return false;
	for(int i=0;i<N;i++)IN[i]--,P[i]=false;
	for(int i=0;i<N;i++)while(Dfs(i,-1,i))STK.pop(),P[i]=false,assert(STK.empty());
	printf("%d\n",ANS.size());
	for(int i=0;i<ANS.size();i++)
	{
		vector<int>&ans=ANS[i];
		printf("%d",ans.size()-1);
		for(int j=0;j<ans.size();j++)printf(" %d",ans[j]+1);
		puts("");
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
		ANS.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,c,s,t,sz;
			scanf("%d%d%d%d",&a,&b,&s,&t);
			if(s==t)continue;
			a--,b--;
			sz=EDGE.size();
			VIS[sz]=false;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(sz),ET[b].push_back(sz);
			IN[a]++,IN[b]++;
		}
		if(!Solve())puts("NIE");
//		break;
	}
	return 0;
}

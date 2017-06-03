#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
template<class T>bool getmax(T &a,const T &b){if(a<b){a=b;return true;}return false;}
struct Edge
{
	int A,B;
	Edge(){}
	Edge(const int _A,const int _B):A(_A),B(_B){}
};
vector<Edge>EDGE;
int N;
vector<int>ET[1000000];
LL SZ[1999998],DP[1999998];
LL GetSZ(const int ei)
{
	LL &ans=SZ[ei];
	if(ans!=-1)return ans;
	ans=1;
	const int u=EDGE[ei].B,parent=EDGE[ei].A;
	for(int i=0;i<(int)ET[u].size();i++)if(EDGE[ET[u][i]].B!=parent)ans+=GetSZ(ET[u][i]);
	return ans;
}
LL GetDP(const int ei)
{
	LL &ans=DP[ei];
	if(ans!=-1)return ans;
	ans=GetSZ(ei);
	const int u=EDGE[ei].B,parent=EDGE[ei].A;
	for(int i=0;i<(int)ET[u].size();i++)if(EDGE[ET[u][i]].B!=parent)ans+=GetDP(ET[u][i]);
	return ans;
}
LL Solve(const int root)
{
	LL ans=0;
	for(int i=0;i<(int)ET[root].size();i++)
	{
		const int ei=ET[root][i];
		ans+=GetDP(ei);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back((int)EDGE.size());
			EDGE.push_back(Edge(a,b));
			ET[b].push_back((int)EDGE.size());
			EDGE.push_back(Edge(b,a));
		}
		for(int i=0;i<(N-1)*2;i++)SZ[i]=DP[i]=-1;
		LL reduced=-1;
		int ans=-1;
		for(int i=0;i<N;i++)if(getmax(reduced,Solve(i)))ans=i;
		assert(ans!=-1);
		printf("%d\n",ans+1);
	}
	return 0;
}

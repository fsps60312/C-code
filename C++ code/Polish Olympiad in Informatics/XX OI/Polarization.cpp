#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
LL SZ[(250000-1)*2];
vector<int>ET[250000];
LL GetSZ(const int eoi)
{
	LL &ans=SZ[eoi];
	if(ans!=-1LL)return ans;
	ans=1LL;
	const Edge &eo=EDGE[eoi/2];
	const int u=(eoi&1?eo.b:eo.a),parent=(eoi&1?eo.a:eo.b);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int ei=ET[u][i];
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==parent)continue;
		if(nxt==e.a)ans+=GetSZ(ei*2);
		else ans+=GetSZ(ei*2+1);
	}
	return ans;
}
LL DP[(250000-1)*2];
LL GetDP(const int eoi)
{
	LL &ans=DP[eoi];
	if(ans!=-1LL)return ans;
	ans=0LL;
	const Edge &eo=EDGE[eoi/2];
	const int u=(eoi&1?eo.b:eo.a),parent=(eoi&1?eo.a:eo.b);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int ei=ET[u][i];
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==parent)continue;
		if(nxt==e.a)ans+=GetDP(ei*2)+GetSZ(ei*2);
		else ans+=GetDP(ei*2+1)+GetSZ(ei*2+1);
	}
	return ans;
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
			SZ[i*2]=SZ[i*2+1]=DP[i*2]=DP[i*2+1]=-1LL;
		}
		LL mx=0LL;
		for(int u=0;u<N;u++)
		{
			LL ta=N-1;
			for(int i=0;i<(int)ET[u].size();i++)
			{
				const int ei=ET[u][i];
				const Edge &e=EDGE[ei];
				if(e.a==u)ta+=GetDP(ei*2+1);
				else ta+=GetDP(ei*2);
			}
			if(ta>mx)mx=ta;
		}
		printf("%d %lld\n",N-1,mx);
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<cassert>
using namespace std;
int T,N,MOD,ANS;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Edge
{
	int u,cost;
	Edge(){}
	Edge(int _u,int _c):u(_u),cost(_c){}
};
vector<Edge>ET[100000];
bool VIS[100000];
int MX[100000],SZ[100000];
int BuildSZ(const int u,const int fa,vector<int>&s)
{
	if(VIS[u])return 0;
//	printf("buildsz u=%d\n",u);
	s.push_back(u);
	int &ans=SZ[u]=1;
	MX[u]=0;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=ET[u][i];
		if(e.u==fa)continue;
		int result=BuildSZ(e.u,u,s);
		ans+=result;
		getmax(MX[u],result);
	}
	return ans;
}
int FindWP(const int root)
{
	vector<int>s;
	BuildSZ(root,-1,s);
	for(int i=0;i<s.size();i++)getmax(MX[s[i]],s.size()-SZ[s[i]]);
//	printf("wpsz=%d\n",s.size());
	int u=s[0];
	for(int i=1;i<s.size();i++)if(MX[s[i]]<MX[u])u=s[i];
	return u;
}
void BuildDIST(const int u,const int fa,vector<int>&dist,int cnow)
{
	if(VIS[u])return;
	getmax(ANS,cnow);
	dist.push_back(cnow);
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=ET[u][i];
		if(e.u==fa)continue;
		BuildDIST(e.u,u,dist,(cnow+e.cost)%MOD);
	}
}
void SetRoot(const int root)
{
	assert(!VIS[root]);
	VIS[root]=true;
//	printf("root=%d\n",root);
	set<int>all;
	for(int i=0;i<ET[root].size();i++)
	{
		const Edge &e=ET[root][i];
		vector<int>dist;
		BuildDIST(e.u,-1,dist,e.cost);
		if(!all.empty())
		{
			for(int j=0;j<dist.size();j++)
			{
				auto it=all.upper_bound(MOD-1-dist[j]);
				if(it==all.begin())
				{
					it=all.end();
					it--;
					int ta=(*it)+dist[j]-MOD;
					assert(ta>=0&&ta<MOD);
					getmax(ANS,ta);
				}
				else
				{
					it--;
					int ta=(*it)+dist[j];
					assert(ta>=0&&ta<MOD);
					getmax(ANS,ta);
				}
			}
		}
		for(int j=0;j<dist.size();j++)all.insert(dist[j]);
	}
	for(int i=0;i<ET[root].size();i++)
	{
		const Edge &e=ET[root][i];
		if(VIS[e.u])continue;
		SetRoot(FindWP(e.u));
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&MOD);
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=false;
		for(int i=1,a,b,c;i<N;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			c%=MOD;
			ET[a].push_back(Edge(b,c)),ET[b].push_back(Edge(a,c));
		}
		ANS=0;
		SetRoot(FindWP(0));
		printf("%d\n",ANS);
	}
	return 0;
}

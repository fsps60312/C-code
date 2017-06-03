#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
int T,N,MOD,ANS;
void getmax(int &a,const int b){if(b>a)a=b;}
int rand()
{
	static unsigned int seed=20151003;
	const unsigned int mod=2147483648u;
	return seed=(seed*0xdefaced+83724)%mod;
}
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(int _a,int _b,int _c):a(_a),b(_b),c(_c){}
};
vector<Edge>EDGE;
vector<int>ET[100000];
bool VIS[100000];
void Dfs(const int u,const int fa,vector<int>&s,vector<int>&dist,const int cnow)
{
	if(VIS[u])return;
	getmax(ANS,cnow);
	s.push_back(u),dist.push_back(cnow);
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(u==e.a?e.b:e.a);
		if(nxt==fa)continue;
		Dfs(nxt,u,s,dist,(cnow+e.c)%MOD);
	}
}
void SetRoot(const int u)
{
//	printf("root u=%d\n",u);
	set<int>all;
	vector<vector<int> >ch;
	ch.resize(ET[u].size());
	VIS[u]=true;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int nxt=(u==e.a?e.b:e.a);
		vector<int>dist;
		ch[i].clear();
		Dfs(nxt,-1,ch[i],dist,e.c);
//		for(int j=0;j<ch[i].size();j++)printf(" %d",ch[i][j]);puts("");
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
	for(int i=0;i<ch.size();i++)if(ch[i].size())
	{
		vector<int>&v=ch[i];
		SetRoot(v[rand()%v.size()]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	int a=-2147483648;
//	printf("%d\n",a);
//	a=-a;
//	printf("%d\n",a);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&MOD);
		for(int i=0;i<N;i++)ET[i].clear(),VIS[i]=false;
		EDGE.clear();
		for(int i=0,a,b,c;i+1<N;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			c%=MOD;
			EDGE.push_back(Edge(a,b,c));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		ANS=0;
		SetRoot(rand()%N);
		printf("%d\n",ANS);
	}
	return 0;
}

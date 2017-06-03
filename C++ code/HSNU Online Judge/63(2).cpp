#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int a,b,c,idx;
	Edge(){}
	Edge(const int &_a,const int &_b,const int &_c,const int &i):a(_a),b(_b),c(_c),idx(i){}
	bool operator<(const Edge &e)const{return c<e.c;}
};
vector<Edge>EDGE;
vector<int>ET[7000];
int DJ[7000];
int FindDJ(const int &a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
bool ANS[300000],TAG[300000];
vector<int>S;
int MX[7000];
void Dfs(const int &u,const int &fa)
{
	for(int i=0;i<S.size();i++)MX[S[i]]=max(MX[S[i]],EDGE[fa].c);
	S.push_back(u);
	for(int i=0;i<ET[u].size();i++)
	{
		if(ET[u][i]==fa)continue;
		const Edge &e=EDGE[ET[u][i]];
		const int &nxt=(u==e.a?e.b:e.a);
		if(TAG[e.idx])Dfs(nxt,ET[u][i]);
		else if(e.c==MX[nxt])ANS[e.idx]=true;
	}
//	if(fa!=-1)for(int i=0;i<S.size();i++)MX[S[i]]=max(MX[S[i]],EDGE[fa].c);
}
void Solve()
{
	for(int i=0;i<N;i++)DJ[i]=i;
	for(int i=0;i<M;i++)ANS[i]=TAG[i]=false;
	int cnt=N;
	for(int i=0;i<M&&cnt>1;i++)
	{
		const Edge &e=EDGE[i];
		int a=FindDJ(e.a),b=FindDJ(e.b);
		if(a==b)continue;
		DJ[a]=b;
		cnt--;
		ANS[e.idx]=TAG[e.idx]=true;
//		printf("mst(%d,%d)\n",e.a+1,e.b+1);
	}
	if(cnt!=1){for(int i=0;i<M;i++)ANS[i]=false;return;}
	for(int i=0;i<N;i++)MX[i]=-INF;
	S.clear();
	Dfs(0,-1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c,i));
		}
		sort(EDGE.begin(),EDGE.end());
		for(int i=0;i<M;i++)
		{
			Edge &e=EDGE[i];
			ET[e.a].push_back(i);
			ET[e.b].push_back(i);
		}
		Solve();
		for(int i=0;i<M;i++)puts(ANS[i]?"TAK":"NIE");
	}
	return 0;
}

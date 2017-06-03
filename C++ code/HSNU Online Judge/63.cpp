#include<cstdio>
#include<vector>
#include<set>
#include<stack>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(const int &_a,const int &_b,const int &_c):a(_a),b(_b),c(_c){}
	bool operator<(const Edge &e)const{return c<e.c;}
};
vector<Edge>EDGE;
vector<int>ET[7000];
int DJ[7000];
int FindDJ(const int &a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
bool ANS[300000],TAG[300000];
set<int>S;
stack<int>MX[7000];
void Dfs(const int &u,const int &fa)
{
	if(fa!=-1)for(set<int>::iterator it=S.begin();it!=S.end();it++)MX[*it].push(max(MX[*it].top(),EDGE[fa].c));
	S.insert(u);
	for(int i=0;i<ET[u].size();i++)
	{
		const int &j=ET[u][i];
		if(j==fa)continue;
		const Edge &e=EDGE[j];
		int nxt=(u==e.a?e.b:e.a);
		if(TAG[j])Dfs(nxt,j);
		else if(S.find(nxt)!=S.end())
		{
			assert(MX[nxt].top()!=-INF);
			assert(e.c>=MX[nxt].top());
			printf("path(%d,%d)=%d\n",u+1,nxt+1,MX[nxt].top());
			if(e.c==MX[nxt].top())
			{
				printf("find(%d,%d)\n",e.a+1,e.b+1);
				ANS[j]=true;
			}
		}
	}
	S.erase(u);
	if(fa!=-1)for(set<int>::iterator it=S.begin();it!=S.end();it++)MX[*it].pop();
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
		ANS[i]=TAG[i]=true;
		printf("mst(%d,%d)\n",e.a+1,e.b+1);
	}
	if(cnt!=1){for(int i=0;i<M;i++)ANS[i]=false;return;}
	for(int i=0;i<N;i++)
	{
		while(!MX[i].empty())MX[i].pop();
		MX[i].push(-INF);
	}
	S.clear();
	Dfs(0,-1);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			EDGE.push_back(Edge(a,b,c));
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

#include<cstdio>
#include<vector>
#include<stack>
#include<cassert>
#include<set>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
vector<int>EA[600];
int PRE[600],LOW[600],PRE_CNT;
bool VIS[600];
int DJ[600];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
stack<int>STK;
void Dfs(const int u)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(const int nxt:EA[u])
	{
		if(!PRE[nxt])Dfs(nxt),getmin(LOW[u],LOW[nxt]);
		else if(!VIS[nxt])getmin(LOW[u],PRE[nxt]);
	}
	if(LOW[u]==PRE[u])
	{
		for(;;)
		{
			const int v=STK.top();STK.pop();
			VIS[v]=true;
			if(v==u)break;
			DJ[Find(v)]=Find(u);
		}
	}
}
vector<int>EU[600],ED[600];
int N;
void Rebuild()
{
	static vector<int>tmp[600];
	for(int i=0;i<N;i++)tmp[i].clear(),vector<int>().swap(tmp[i]);
	for(int i=0;i<N;i++)for(const int j:EU[i])tmp[Find(i)].push_back(Find(j));
	for(int i=0;i<N;i++)EU[i].clear(),tmp[i].swap(EU[i]);
	for(int i=0;i<N;i++)for(const int j:ED[i])tmp[Find(i)].push_back(Find(j));
	for(int i=0;i<N;i++)ED[i].clear(),tmp[i].swap(ED[i]);
}
int H[600];
bool SetH(const int u,const int h,set<int>&s)
{
	if(H[u]!=INF)return H[u]==h;
	s.insert(H[u]=h);
	for(const int nxt:EU[u])if(!SetH(nxt,h+1,s))return false;
	for(const int nxt:ED[u])if(!SetH(nxt,h-1,s))return false;
	return true;
}
int Solve()
{
	for(int i=0;i<N;i++)PRE[i]=0,DJ[i]=i;
	PRE_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
	Rebuild();
	set<int>all;
	for(int i=0;i<N;i++)all.insert(Find(i));
	for(const int i:all)H[i]=INF;
	set<int>s;
	int ans=0;
	for(const int i:all)if(H[i]==INF)
	{
		s.clear();
		if(!SetH(i,0,s))return false;
		ans+=s.size();
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	static int m1,m2;scanf("%d%d%d",&N,&m1,&m2);
	for(int i=0;i<N;i++)EU[i].clear(),ED[i].clear(),EA[i].clear();
	for(int i=0,a,b;i<m1;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		EU[a].push_back(b),ED[b].push_back(a);
	}
	for(int i=0,a,b;i<m2;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		EA[a].push_back(b);
	}
	const int ans=Solve();
	if(ans==-1)puts("NIE");
	else printf("%d\n",ans);
}

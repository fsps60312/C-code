#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M;
struct Edge
{
	int a,b,w;
	Edge(){}
	Edge(int a,int b,int w):a(a),b(b),w(w){}
	bool operator<(const Edge &e)const{return w<e.w;}
	int &To(int from){return from!=a?a:b;}
}EDGE[350*(350-1)/2];
set<int>AD[350];
int DJ[350];
int FindDJ(int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
set<int>CNT;
bool Dfs(int u,int fa,int &t,vector<int>&loop)
{
	if(u==t)return true;
	for(set<int>::iterator it=AD[u].begin();it!=AD[u].end();it++)
	{
		Edge &e=EDGE[*it];
		int &nxt=e.To(u);
		if(nxt==fa)continue;
		if(Dfs(nxt,u,t,loop)){loop.push_back(*it);return true;}
	}
	return false;
}
int Solve()
{
	CNT.clear();
	for(int i=0;i<N;i++)DJ[i]=i;
	int cnt=N,ans=INF;
	for(int i=0;i<M;i++)
	{
		int &a=EDGE[i].a,&b=EDGE[i].b;
		if(FindDJ(a)!=FindDJ(b))
		{
			DJ[FindDJ(a)]=FindDJ(b);
			cnt--;
		}
		else//delete min side in loop
		{
			vector<int>loop;
//			puts("a");
			assert(Dfs(a,-1,b,loop));
//			puts("b");
			int mn=INF,idx=-1;
			for(int j=0;j<loop.size();j++)
			{
				Edge &e=EDGE[loop[j]];
				if(e.w<mn)mn=e.w,idx=loop[j];
			}
			assert(idx!=-1);
			int &x=EDGE[idx].a,&y=EDGE[idx].b;
			AD[x].erase(idx);
			AD[y].erase(idx);
			CNT.erase(idx);
		}
		AD[a].insert(i);
		AD[b].insert(i);
		CNT.insert(i);
//		for(set<int>::iterator it=CNT.begin();it!=CNT.end();it++)printf(" %d",*it);puts("");
		if(cnt==1)
		{
			set<int>::iterator it=CNT.end();
			it--;
			ans=min(ans,EDGE[*it].w-EDGE[*CNT.begin()].w);
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d",&M);
		for(int i=0;i<N;i++)AD[i].clear();
		for(int i=0;i<M;i++)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b,&w=EDGE[i].w;
			scanf("%d%d%d",&a,&b,&w);
		}
		sort(EDGE,EDGE+M);
//		for(int i=0;i<M;i++)printf("%d: %d %d %d\n",i,EDGE[i].a,EDGE[i].b,EDGE[i].w);
		int ans=Solve();
		printf("%d\n",ans);
	}
	return 0;
}

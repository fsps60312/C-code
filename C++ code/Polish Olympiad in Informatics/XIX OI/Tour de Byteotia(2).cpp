#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(min(_a,_b)),b(max(_a,_b)){}
	bool operator<(const Edge &e)const{return a!=e.a?a<e.a:b<e.b;}
};
vector<Edge>EDGE;
map<Edge,int>IDX;
bool VIS[2000000];
int GetIdx(const Edge &e)
{
	const map<Edge,int>::iterator it=IDX.find(e);
	if(it!=IDX.end())return it->second;
	const int sz=IDX.size();
	EDGE.push_back(e);
	VIS[sz]=false;
	return IDX[e]=sz;
}
set<int>ET[1000000];
int N,M,K;
int PRE[1000000],PRE_CNT,BCC[2000000],BCC_CNT;
vector<int>STK;
int Dfs(const int u)
{
	int low=PRE[u]=++PRE_CNT;
	for(set<int>::iterator ei=ET[u].begin();ei!=ET[u].end();ei++)if(!VIS[*ei])
	{
		VIS[*ei]=true;
		STK.push_back(*ei);
		const Edge &e=EDGE[*ei];//printf("enter %d(%d,%d)\n",*ei,e.a+1,e.b+1);
		const int nxt=(u==e.a?e.b:e.a);
		if(!PRE[nxt])
		{
			const int nxtlow=Dfs(nxt);
			getmin(low,nxtlow);
			if(nxtlow>=PRE[u])
			{
				for(;;)
				{
					const int v=STK.back();STK.pop_back();
					BCC[v]=BCC_CNT;
//					printf("%d(%d,%d)=%d\n",v,EDGE[v].a+1,EDGE[v].b+1,BCC_CNT);
					if(v==*ei)break;
				}
				BCC_CNT++;
			}
		}
		else getmin(low,PRE[nxt]);
	}
	return low;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear(),IDX.clear();
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].insert(b),ET[b].insert(a);
	}
	for(int i=0;i<N;i++)
	{
		set<int>et;
		et.swap(ET[i]);
		for(set<int>::iterator nxt=et.begin();nxt!=et.end();nxt++)ET[i].insert(GetIdx(Edge(i,*nxt)));
	}
	for(int i=0;i<N;i++)PRE[i]=0;
	PRE_CNT=BCC_CNT=0;
	for(int i=0;i<N;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
	static int cnt[1000000];
	for(int i=0;i<BCC_CNT;i++)cnt[i]=0;
	vector<Edge>ans;
	for(int i=0;i<K;i++)
	{
		for(set<int>::iterator ei=ET[i].begin();ei!=ET[i].end();ei++)cnt[BCC[*ei]]++;
		for(set<int>::iterator ei=ET[i].begin();ei!=ET[i].end();ei++)
		{
			const Edge &e=EDGE[*ei];
			const int nxt=(i==e.a?e.b:e.a);
			ET[nxt].erase(*ei);
			if(--cnt[BCC[*ei]])ans.push_back(EDGE[*ei]);
		}
		ET[i].clear();
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)printf("%d %d\n",ans[i].a+1,ans[i].b+1);
	return 0;
}

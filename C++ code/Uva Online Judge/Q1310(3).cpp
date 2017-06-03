#include<cstdio>
#include<vector>
#include<stack>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
void getmin(int &a,const int b){if(b<a)a=b;}
struct Edge
{
	int end[2];
	int d;
	bool inuse;
	Edge(){}
	Edge(const int _a,const int _b,const int _d):end{_a,_b},d(_d),inuse(true){}
};
vector<Edge>EDGE;
vector<int>ET[2000];
int PRE[2000],LOW[2000],PRE_CNT;
vector<vector<int> >SCC;
stack<int>STK;
void DfsSCC(const int u,const int fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	for(const auto ei:ET[u])if(ei!=fa)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.end[0]?e.end[1]:e.end[0]);
		if(!PRE[nxt])
		{
			STK.push(ei);
			DfsSCC(nxt,ei);
			getmin(LOW[u],LOW[nxt]);
			if(LOW[nxt]>PRE[u])
			{
				assert(e.d==-1);
				EDGE[ei].inuse=false;
				vector<int>seq;
				for(;;)
				{
					const int v=STK.top();STK.pop();
					if(v==ei)break;
					seq.push_back(v);
				}
				if(!seq.empty())SCC.push_back(seq);
			}
		}
		else getmin(LOW[u],PRE[nxt]);
	}
	if(fa==-1)
	{
		vector<int>seq;
		while(!STK.empty())seq.push_back(STK.top()),STK.pop();
		if(!seq.empty())SCC.push_back(seq);
	}
}
int VIS[2000],VIS_CNT;
bool DfsCycle(const int u,int target,const int dep)
{
	assert(dep<=2000);
//	printf("u=%d,target=%d\n",u,target);
	bool ans=false;
	if(target>=0)
	{
		if(VIS[u])return false;
		VIS[u]=VIS_CNT;
		if(u==target)ans=true,target=-1,VIS_CNT++;
	}
	else
	{
		if(VIS[u])
		{
			ans=(VIS[u]<VIS_CNT);
			if(ans)VIS_CNT++; 
			return ans;
		}
		VIS[u]=VIS_CNT;
	}
	reloop:;
	for(const int ei:ET[u])
	{
		Edge &e=EDGE[ei];
		if(!e.inuse)continue;
		const int pred=e.d;
		if(e.d==-1)e.d=(u==e.end[0]?1:0);
		else if(e.end[e.d]==u)continue;
		const int nxt=e.end[e.d];
		if(DfsCycle(nxt,target,dep+1)&&!ans)
		{
			ans=true,target=-1;
			goto reloop;
		}
		else if(!ans)e.d=pred;
	}
	if(!ans)VIS[u]=0;
	return ans;
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		vector<int>twowayroad;
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			assert(a>=0&&a<N&&b>=0&&b<N);
			if(c==2)twowayroad.push_back(i);
			else assert(c==1);
			EDGE.push_back(Edge(a,b,c==1?1:-1));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		for(int i=0;i<N;i++)PRE[i]=0;
		SCC.clear(),PRE_CNT=0;
		DfsSCC(0,-1);
		assert(STK.empty());
		for(int i=0;i<N;i++)VIS[i]=0;
		for(const auto &scc:SCC)
		{
			assert(!scc.empty());
			VIS_CNT=1;
			bool found=false;
			for(const int ei:scc)
			{
				const Edge &e=EDGE[ei];
				if(e.d==1)
				{
					assert(DfsCycle(e.end[1],e.end[0],0));
					found=true;
					break;
				}
				else assert(e.d==-1);
			}
			if(!found)
			{
				EDGE[scc[0]].d=1;
				const Edge &e=EDGE[scc[0]];
				assert(DfsCycle(e.end[1],e.end[0],0));
			}
		}
		for(const int ei:twowayroad)
		{
			const Edge &e=EDGE[ei];
			if(e.d==0)printf("%d %d %d\n",e.end[1]+1,e.end[0]+1,1);
			else printf("%d %d %d\n",e.end[0]+1,e.end[1]+1,e.d==-1?2:1);
		}
	}
	return 0;
}

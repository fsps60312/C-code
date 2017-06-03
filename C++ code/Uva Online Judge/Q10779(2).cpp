#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
void getmin(int &a,int b){if(b<a)a=b;}
int T,N,M;
int In(int i){return i;}
int Im(int i){return N+i;}
int It(){return N+M;}
struct Edge
{
	int from,to,limit,flow;
};
vector<Edge> EDGE;
vector<int> GETO[10+25+1];
int STKR[10][25];
void add_EDGE(int a,int b,int l)
{
	GETO[a].push_back(EDGE.size());
	EDGE.push_back((Edge){a,b,l,0});
	GETO[b].push_back(EDGE.size());
	EDGE.push_back((Edge){b,a,0,0});
}
int DEP[10+25+1],DEP_CNT[10+25+2],VIS[10+25+1];
void build_DEPx()
{
	for(int i=0;i<=It();i++)DEP[i]=It()+1,VIS[i]=0;
	for(int i=0;i<=It()+1;i++)DEP_CNT[i]=0;
	queue<int> q;
	q.push(It());
	DEP[It()]=0;
	VIS[It()]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &e=EDGE[GETO[u][i]^1];
			if(e.flow==e.limit||VIS[e.from])continue;
			DEP[e.from]=DEP[e.to]+1;
			VIS[e.from]=1;
			q.push(e.from);
		}
	}
	for(int i=0;i<=It();i++)DEP_CNT[DEP[i]]++;
}
int CUR[10+25+1],PRE[10+25+1];
int do_flow()
{
	int x=It(),ans=INF;
	while(x!=In(0))
	{
		Edge &e=EDGE[PRE[x]];
		getmin(ans,e.limit-e.flow);
		x=e.from;
	}
	x=It();
	while(x!=In(0))
	{
		EDGE[PRE[x]].flow+=ans;
		EDGE[PRE[x]^1].flow-=ans;
		x=EDGE[PRE[x]].from;
	}
	return ans;
}
int get_MAXFLOW()
{
	build_DEPx();
	for(int i=0;i<=It();i++)CUR[i]=VIS[i]=0;
	int x=In(0),ans=0;
	while(DEP[In(0)]<=It())
	{
		if(x==It())
		{
			ans+=do_flow();
			for(int i=0;i<=It();i++)VIS[i]=0;
			x=In(0);
		}
		bool found=false;
		for(int &i=CUR[x];i<GETO[x].size();i++)
		{
			Edge &e=EDGE[GETO[x][i]];
			if(e.flow==e.limit||DEP[e.from]!=DEP[e.to]+1||VIS[e.to])continue;
			VIS[e.to]=1;
			found=true;
			PRE[e.to]=GETO[x][i];
			x=e.to;
			break;
		}
		if(!found)
		{
			if(--DEP_CNT[DEP[x]]==0)break;
			DEP[x]=It()+1;
			for(int i=0;i<GETO[x].size();i++)
			{
				Edge &e=EDGE[GETO[x][i]];
				if(e.flow==e.limit)continue;
				getmin(DEP[x],DEP[e.to]+1);
			}
			DEP_CNT[DEP[x]]++;
			CUR[x]=VIS[x]=0;
			if(x!=In(0))x=EDGE[PRE[x]].from;
		}
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin); 
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				STKR[i][j]=0;
			}
			int a;scanf("%d",&a);
			while(a--)
			{
				int k;scanf("%d",&k);
				k--;
				STKR[i][k]++;
			}
		}
		for(int i=0;i<=It();i++)
		{
			GETO[i].clear();
		}
		EDGE.clear();
		for(int i=0;i<M;i++)
		{
			add_EDGE(Im(i),It(),1);
			if(STKR[0][i])add_EDGE(In(0),Im(i),STKR[0][i]);
		}
		for(int i=1;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				if(STKR[i][j]>1)add_EDGE(In(i),Im(j),STKR[i][j]-1);
				else if(STKR[i][j]==0)add_EDGE(Im(j),In(i),1);
			}
		}
		printf("Case #%d: %d\n",kase++,get_MAXFLOW());
//		for(int i=0;i<EDGE.size();i+=2)
//		{
//			Edge &e=EDGE[i];
//			printf("Edge(%d,%d):flow %d/%d\n",e.from,e.to,e.flow,e.limit);
//		}
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=(1<<30);
struct Edge
{
	int from,to,limit,flow;
};
void getmin(int &a,int b){if(b<a)a=b;}
int N,M,K,S,T,DAY,ANS;
int I(int d,int x){return d*N+x;}
vector<Edge> EDGE;
vector<int> GETO[100*50];
int PRE[100*50],VIS[100*50];
struct Point
{
	int x,y;
};
vector<Point> COPY_EDGES;
void add_DAY()
{
	for(int i=0;i<N;i++)
	{
		GETO[I(DAY,i)].push_back(EDGE.size());
		EDGE.push_back((Edge){I(DAY,i),I(DAY+1,i),i==T?1000-ANS:1000,0});
		GETO[I(DAY+1,i)].push_back(EDGE.size());
		EDGE.push_back((Edge){I(DAY+1,i),I(DAY,i),i==T?ANS:0,0});
	}
	for(int i=0;i<COPY_EDGES.size();i++)
	{
		Point &p=COPY_EDGES[i];
		
		GETO[I(DAY,p.x)].push_back(EDGE.size());
		EDGE.push_back((Edge){I(DAY,p.x),I(DAY+1,p.y),1,0});
		GETO[I(DAY+1,p.y)].push_back(EDGE.size());
		EDGE.push_back((Edge){I(DAY+1,p.y),I(DAY,p.x),0,0});
		
		GETO[I(DAY,p.y)].push_back(EDGE.size());
		EDGE.push_back((Edge){I(DAY,p.y),I(DAY+1,p.x),1,0});
		GETO[I(DAY+1,p.x)].push_back(EDGE.size());
		EDGE.push_back((Edge){I(DAY+1,p.x),I(DAY,p.y),0,0});
	}
	DAY++;
}
int min(int a,int b){return a<b?a:b;}
void erase_2_edge(int i1,int i2)
{
	int v=min(EDGE[i1].flow,EDGE[i2].flow);
	EDGE[i1].flow-=v,EDGE[i1^1].flow+=v;
	EDGE[i2].flow-=v,EDGE[i2^1].flow+=v;
}
void erase_edge_flow(int i)
{
	if(i>=2&&EDGE[i].from+N==EDGE[i-2].to&&EDGE[i].to-N==EDGE[i-2].from)
	{
		erase_2_edge(i,i-2);
		return;
	}
	if(i+2<EDGE.size()&&EDGE[i].from+N==EDGE[i+2].to&&EDGE[i].to-N==EDGE[i+2].from)
	{
		erase_2_edge(i,i+2);
		return;
	}
}
int do_FLOW()
{
	int x=I(DAY,T),low=INF;
	while(x!=I(0,S))
	{
		Edge &e=EDGE[PRE[x]];
		getmin(low,e.limit-e.flow);
		x=e.from;
	}
	x=I(DAY,T);
	while(x!=I(0,S))
	{
		EDGE[PRE[x]].flow+=low;
		EDGE[PRE[x]^1].flow-=low;
		erase_edge_flow(PRE[x]);
		x=EDGE[PRE[x]].from;
	}
	return low;
}
int DEP[100*50],DEP_CNT[100];
void build_DEPx()
{
	for(int i=I(0,0);i<I(DAY,N);i++)
	{
		VIS[i]=0;
		DEP[i]=N+DAY;
	}
	for(int i=0;i<DAY+N;i++)DEP_CNT[i]=0;
	queue<int> q;
	q.push(I(DAY,T));
	VIS[I(DAY,T)]=1;
	DEP[I(DAY,T)]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &e=EDGE[GETO[u][i]^1];
			if(e.flow==e.limit||VIS[e.from])continue;
			VIS[e.from]=1;
			DEP[e.from]=DEP[u]+1;
			q.push(e.from);
		}
	}
	for(int i=I(0,0);i<I(DAY,N);i++)DEP_CNT[DEP[i]]++;
}
int CUR[200*50];
int get_MAXFLOW()
{
	build_DEPx();
	for(int i=I(0,0);i<I(DAY,N);i++)CUR[i]=0;
	int x=I(0,S);
	int ans=0;
	while(DEP[I(0,S)]<N+DAY)
	{
		if(x==I(DAY,T))
		{
			ans+=do_FLOW();
			x=I(0,S);
		}
		bool found=false;
		for(int &i=CUR[x];i<GETO[x].size();i++)
		{
			Edge &e=EDGE[GETO[x][i]];
			if(e.flow==e.limit||DEP[e.to]!=DEP[e.from]-1)continue;
			found=true;
			PRE[e.to]=GETO[x][i];
			x=e.to;
			break;
		}
		if(!found)
		{
			if(--DEP_CNT[DEP[x]]==0)break;
			CUR[x]=0;
			DEP[x]=N+DAY;
			for(int i=0;i<GETO[x].size();i++)
			{
				Edge &e=EDGE[GETO[x][i]];
				if(e.flow==e.limit)continue;
				getmin(DEP[x],DEP[e.to]+1);
			}
			DEP_CNT[DEP[x]]++;
			x=EDGE[PRE[x]].from;
		}
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin); 
	while(scanf("%d%d%d%d%d",&N,&M,&K,&S,&T)==5)
	{
		S--,T--;
		for(int i=0;i<N+K;i++)
		{
			for(int j=0;j<N;j++)
			{
				GETO[I(i,j)].clear();
			}
		}
		EDGE.clear();
		COPY_EDGES.clear();
		for(int i=0;i<N;i++)
		{
			GETO[I(0,i)].push_back(EDGE.size());
			EDGE.push_back((Edge){I(0,i),I(1,i),1000,0});
			GETO[I(1,i)].push_back(EDGE.size());
			EDGE.push_back((Edge){I(1,i),I(0,i),0,0});
		}
		for(int i=0;i<M;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			u--,v--;
			COPY_EDGES.push_back((Point){u,v});
			
			GETO[I(0,u)].push_back(EDGE.size());
			EDGE.push_back((Edge){I(0,u),I(1,v),1,0});
			GETO[I(1,v)].push_back(EDGE.size());
			EDGE.push_back((Edge){I(1,v),I(0,u),0,0});
			
			GETO[I(0,v)].push_back(EDGE.size());
			EDGE.push_back((Edge){I(0,v),I(1,u),1,0});
			GETO[I(1,u)].push_back(EDGE.size());
			EDGE.push_back((Edge){I(1,u),I(0,v),0,0});
		}
		ANS=0;
		DAY=1;
		while((ANS+=get_MAXFLOW())<K)
		{
			add_DAY();
		}
		printf("%d\n",DAY);
		vector<Point> ans;
		for(int i=0;i<K;i++)
		{
			VIS[i]=I(0,S);
		}
		for(int d=0;d<DAY;d++)
		{
			ans.clear();
			for(int x=0;x<N;x++)
			{
				for(int i=0;i<GETO[I(d,x)].size();i++)
				{
					Edge &e=EDGE[GETO[I(d,x)][i]];
					if(e.flow<=0||e.to%N==e.from%N)continue;
					ans.push_back((Point){e.from,e.to});
				}
			}
			printf("%d",ans.size());
			for(int i=0;i<K;i++)
			{
				bool found=false;
				for(int j=0;j<ans.size();j++)
				{
					if(ans[j].x==VIS[i])
					{
						VIS[i]=ans[j].y;
						ans[j].x=-1;
						printf(" %d %d",i+1,ans[j].y%N+1);
						found=true;
						break;
					}
				}
				if(!found)VIS[i]+=N;
			}
			printf("\n");
		}
	}
	return 0;
}

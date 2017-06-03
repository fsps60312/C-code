#include<cstdio>
#include<vector>
#include<queue> 
using namespace std;
const int INF=2147483647;
void termin(){printf("terminating...\n");int a[10];for(int i=0;;i--)a[i]=100;}
void getmin(int &a,int b){if(b<a)a=b;}
int T,N;
int WINS[25];
int ORI_MAT[25][25],MAT[25][25];
vector<int> GETO[25*26/2+2];
struct Edge
{
	int from,to,limit,flow;
};
vector<Edge> EDGE;
template<class T_TYPE>
void mswap(T_TYPE &a,T_TYPE &b)
{
	T_TYPE c=a;
	a=b,b=c;
}
int I(int t1,int t2)
{
	if(t1==t2)termin();
	if(t1<t2)mswap(t1,t2);
	return t1*(t1-1)/2+t2;
}
int I(int t)
{
	return N*(N-1)/2+t;
}
int I(char t)
{
	if(t=='S')return N*(N+1)/2;
	if(t=='T')return N*(N+1)/2+1;
	termin();
}
void add_EDGE(int a,int b,int v)
{
	if(a==b)termin();
	GETO[a].push_back(EDGE.size());
	EDGE.push_back((Edge){a,b,v,0});
	GETO[b].push_back(EDGE.size());
	EDGE.push_back((Edge){b,a,0,0});
}
int DEP[25*26/2+2],VIS[25*26/2+2],DEP_CNT[25*26/2+3];
void get_DEPx()
{
	for(int i=0;i<=I('T');i++)
	{
		DEP[i]=I('T')+1;
		VIS[i]=0;
	}
	for(int i=0;i<=I('T')+1;i++)
	{
		DEP_CNT[i]=0;
	}
	queue<int> q;
	q.push(I('T'));
	DEP[I('T')]=0;
	VIS[I('T')]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<GETO[u].size();i++)
		{
			Edge &e=EDGE[GETO[u][i]^1];
			if(e.flow==e.limit||VIS[e.from])continue;
			VIS[e.from]=1;
			DEP[e.from]=DEP[e.to]+1;
			q.push(e.from);
		}
	}
	for(int i=0;i<=I('T');i++)DEP_CNT[DEP[i]]++;
}
int CUR[25*26/2+2],PRE[25*26/2+2];
int try_flow()
{
	int x=I('T'),low=INF;
	while(x!=I('S'))
	{
		Edge &e=EDGE[PRE[x]];
		getmin(low,e.limit-e.flow);
		x=e.from;
	}
	x=I('T');
	while(x!=I('S'))
	{
		EDGE[PRE[x]].flow+=low;
		EDGE[PRE[x]^1].flow-=low;
		x=EDGE[PRE[x]].from;
	}
//	printf("low=%d\n",low);
	return low;
}
int get_MAXFLOW()
{
	get_DEPx();
	for(int i=0;i<=I('T');i++)
	{
		CUR[i]=0;
	}
	int x=I('S'),ans=0;
//	printf("a\n");
	while(DEP[I('S')]<=I('T'))
	{
//		printf("x=%d\n",x);
		if(x==I('T'))
		{
			//printf("a\n");
			ans+=try_flow();
			//printf("b\n");
			x=I('S');
		}
		bool found=false;
		for(int &i=CUR[x];i<GETO[x].size();i++)
		{
			Edge &e=EDGE[GETO[x][i]];
			if(e.flow==e.limit||DEP[e.from]!=DEP[e.to]+1)continue;
			PRE[e.to]=GETO[x][i];
//			CUR[x]=i;
			x=e.to;
			found=true;
			break;
		}
		if(!found)
		{
			if(--DEP_CNT[DEP[x]]==0)break;
			DEP[x]=I('T')+1;
			for(int i=0;i<GETO[x].size();i++)
			{
				Edge &e=EDGE[GETO[x][i]];
				if(e.flow==e.limit)continue;
				getmin(DEP[x],DEP[e.to]+1);
			}
			DEP_CNT[DEP[x]]++;
			CUR[x]=0;
			if(x!=I('S'))x=EDGE[PRE[x]].from;
		}
	}
//	printf("b\n");
	return ans;
}
bool can_win(int team)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			MAT[i][j]=ORI_MAT[i][j];
		}
	}
	int total=WINS[team];
	for(int i=0;i<N;i++)
	{
		total+=MAT[team][i];
		MAT[team][i]=MAT[i][team]=0;
	}
	for(int i=0;i<=I('T');i++)
	{
		GETO[i].clear(); 
	}
	EDGE.clear();
	for(int i=0;i<N;i++)
	{
		if(i==team)continue;
		if(WINS[i]>total)return false;
		add_EDGE(I(i),I('T'),total-WINS[i]);
	}
	total=0;
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			if(!MAT[i][j])continue;
			total+=MAT[i][j];
			add_EDGE(I('S'),I(i,j),MAT[i][j]);
			add_EDGE(I(i,j),I(i),INF);
			add_EDGE(I(i,j),I(j),INF);
		}
	}
//	printf("a\n");
	int ans=get_MAXFLOW();
	if(ans>total)termin();
	return ans==total;
//	printf("b\n");
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N*(N+1)/2+2;i++)VIS[i]=0;
		for(int i=0;i<N;i++)
		{
			//printf(" %d",I(i));
			VIS[I(i)]++;
			for(int j=i+1;j<N;j++)
			{
				//printf(" %d",I(i,j));
				VIS[I(i,j)]++;
			}
		}
		VIS[I('S')]++,VIS[I('T')]++;
		for(int i=0;i<N*(N+1)/2+2;i++)
		{
			if(VIS[i]!=1)termin();
		}
		for(int i=0;i<N;i++)
		{
			int d;scanf("%d%d",&WINS[i],&d);
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				scanf("%d",&ORI_MAT[i][j]);
			}
		}
		bool printed=false;
		for(int i=0;i<N;i++)
		{
//			printf("query team %d\n",i);
			if(can_win(i))
			{
				if(printed)putchar(' ');
				printed=true;
				printf("%d",i+1);
			}
		}
		printf("\n");
	}
	return 0;
}

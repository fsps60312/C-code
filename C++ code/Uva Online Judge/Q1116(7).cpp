#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
using namespace std;
int T,N,M,VIS[10000],FA[10000];
set<int>AD[10000];
struct Edge
{
	int a,b;
	Edge(){}
	Edge(int a,int b):a(min(a,b)),b(max(a,b)){}
	int To(int from){return from!=a?a:b;} 
	bool operator<(const Edge &e)const
	{
		return a!=e.a?a<e.a:b<e.b;
	}
}EDGE[19997];
map<Edge,int>ALL;
int GetE(int u,int i)
{
	set<int>::iterator it=AD[u].begin();
	while(i--)it++;
	return *it;
}
int To(int u,int i){return EDGE[GetE(u,i)].To(u);}
int NxtE(int e,int a){return GetE(a,0)!=e?GetE(a,0):GetE(a,1);}
void DeleteEdge(int a,int b)
{
	int e=ALL[Edge(a,b)];
	ALL.erase(Edge(a,b));
	AD[a].erase(e);
	AD[b].erase(e);
}
void PrintAns(int u,int fa)
{
	if(u==0){puts("");return;}
	printf(" %d",u+1);
	if(To(u,0)!=fa)PrintAns(To(u,0),u);
	else PrintAns(To(u,1),u);
}
queue<int>JUMP[10000];
void Push(Edge e,queue<Edge>&q)
{
	q.push(e);
	JUMP[e.a].push(e.b);
	JUMP[e.b].push(e.a);
}
Edge Pop(queue<Edge>&q)
{
	Edge e=q.front();q.pop();
	JUMP[e.a].pop();
	JUMP[e.b].pop();
	return e;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			M+=N;
			for(int i=0;i<N;i++)
			{
				AD[i].clear();
				VIS[i]=false;
				JUMP[i]=queue<int>();
				FA[i]=i;
			}
			ALL.clear();
			for(int i=0,a,b;i<M;i++)
			{
				scanf("%d%d",&a,&b);
				a--,b--;
				AD[a].insert(i);
				AD[b].insert(i);
				EDGE[i]=Edge(a,b);
				ALL[EDGE[i]]=i;
			}
			bool iscyc=true;
			for(int i=0;i<N;i++)if(AD[i].size()!=2)
			{
				iscyc=false;
				break;
			}
			if(!iscyc)
			{
				queue<Edge>q;
				for(int i=0;i<N;i++)
				{
					if(AD[i].size()==2&&!VIS[i])
					{
						int e=GetE(i,0);
						int l=EDGE[e].To(i);
						while(AD[l].size()==2)
						{
							e=NxtE(e,l);
							static int nxt;nxt=EDGE[e].To(l);
							FA[nxt]=l;
							l=nxt;
						}
						int r=EDGE[e].To(l);
						while(AD[r].size()==2)
						{
							VIS[r]=true;
							e=NxtE(e,r);
							static int nxt;nxt=EDGE[e].To(r);
							FA[nxt]=r;
							r=nxt;
						}
						Push(Edge(l,r),q);
					}
				}
				while(!q.empty())
				{
					Edge e=Pop(q);
					int &a=e.a,&b=e.b;
					if(VIS[a]||VIS[b])continue;
					DeleteEdge(a,b);
					M--;
					while(AD[a].size()==2&&a!=b)
					{
						VIS[a]=true;
						if(JUMP[a].size())a=JUMP[a].front();
						else
						{
							if(!VIS[To(a,0)])a=To(a,0);
							else a=To(a,1);
						}
					}
					while(AD[b].size()==2&&b!=a)
					{
						VIS[b]=true;
						if(JUMP[b].size())b=JUMP[b].front();
						else
						{
							if(!VIS[To(b,0)])b=To(b,0);
							else b=To(b,1);
						}
					}
					if(a==b)break;
					Push(Edge(a,b),q);
				}
			}
			printf("1");
			if(To(0,0)<To(0,1))PrintAns(To(0,0),0);
			else PrintAns(To(0,1),0);
			if(T)puts("");
		}
	}
	return 0;
}

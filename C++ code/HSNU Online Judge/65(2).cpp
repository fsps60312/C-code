#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int INF=2147483647;
int N,M,Q;
struct Edge
{
	int a,b,c;
	Edge(){}
	Edge(const int &_a,const int &_b,const int &_c):a(_a),b(_b),c(_c){}
};
vector<Edge>EDGE;
vector<int>ET[100];
int DIST[100],TMP[100];
bool INQ[100];
void Update(const int &s)
{
	if(DIST[s]==INF)return;
	static queue<int>q;
	q.push(s);
	INQ[s]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		for(int i=0;i<ET[u].size();i++)
		{
			Edge &e=EDGE[ET[u][i]];
			const int &nxt=(e.a==u?e.b:e.a);
			if(DIST[u]+e.c<DIST[nxt])
			{
				DIST[nxt]=DIST[u]+e.c;
				if(!INQ[nxt])
				{
					q.push(nxt);
					INQ[nxt]=true;
				}
			}
		}
	}
}
void Copy(int *a,int *b){for(int i=0;i<N;i++)b[i]=a[i];}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&Q);
	for(int i=0;i<N;i++)ET[i].clear(),INQ[i]=false;
	EDGE.clear();
	for(int i=0,a,b,c;i<M;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		a--,b--;
		EDGE.push_back(Edge(a,b,c));
		ET[a].push_back(i);
		ET[b].push_back(i);
	}
	for(int i=0;i<N;i++)DIST[i]=INF;
	DIST[0]=0;
	Update(0);
	Copy(DIST,TMP);
	while(Q--)
	{
		static int a,b,c,sz;
		scanf("%d%d%d",&a,&b,&c);
		a--,b--;
		sz=EDGE.size();
		EDGE.push_back(Edge(a,b,c));
		ET[a].push_back(sz);
		ET[b].push_back(sz);
		Update(a);
		Update(b);
		if(DIST[N-1]<TMP[N-1])
		{
			puts("1");
			Copy(DIST,TMP);
		}
		else
		{
			EDGE.pop_back();
			ET[a].pop_back();
			ET[b].pop_back();
			puts("0");
			Copy(TMP,DIST);
		}
	}
	return 0;
}

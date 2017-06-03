#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
struct Edge
{
	int _a,_b,_f,_ans;
	Edge(){}
	Edge(const int a,const int b,const int f):_a(a),_b(b),_f(f),_ans(-1){}
};
int N,M,GOAL[200000];
vector<int>ET[200000];
vector<Edge>EDGE;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),GOAL[i]=0;
		EDGE.clear();
		for(int i=0,a,b,f;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&f),--a,--b;
			EDGE.push_back(Edge(a,b,f));
			ET[a].push_back(i),ET[b].push_back(i);
			GOAL[a]+=f,GOAL[b]+=f;
		}
//		int target=-1;
//		for(int i=1;i<N;i++)
//		{
//			if(GOAL[i]%2==0)GOAL[i]/=2;
////			else assert(target==-1),target=i;
//		}
//		assert(target!=-1);
		queue<int>q;q.push(0);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			if(u==N-1)continue;
			for(const int ei:ET[u])
			{
				Edge &e=EDGE[ei];
				if(e._ans==-1)
				{
					int nxt;
					if(u==e._a)nxt=e._b,e._ans=0;
					else nxt=e._a,e._ans=1;
					GOAL[nxt]-=2*e._f;
//					assert(GOAL[nxt]>=0);
					if(GOAL[nxt]==0)q.push(nxt);
				}
			}
		}
//		for(int i=1;i<N;i++)printf("[%d]=%d\n",i,GOAL[i]);
//		for(int i=1;i<N;i++)assert(GOAL[i]==0);
		for(const Edge &e:EDGE)assert(e._ans!=-1),printf("%d\n",e._ans);
	}
	return 0;
}

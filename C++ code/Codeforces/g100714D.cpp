#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=2147483647;
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
struct Edge
{
	int _a,_b,_length;
	Edge(){}
	Edge(const int a,const int b,const int length):_a(a),_b(b),_length(length){}
};
struct Pq
{
	int _u,_dist,_id;
	Pq(){}
	Pq(const int u,const int dist,const int id):_u(u),_dist(dist),_id(id){}
};
bool operator<(const Pq &a,const Pq &b){return a._dist>b._dist;}
int N,K,L;
Pq DIST[100000];
vector<int>ET[100000];
vector<Edge>EDGE;
main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%lld%lld",&K,&N,&L)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear(),DIST[i]=Pq(-1,-1,-1);
		EDGE.clear();
		priority_queue<Pq>pq;
		for(int i=0,v;i<K;i++)scanf("%lld",&v),--v,pq.push(Pq(v,0,i));
		for(int i=0,a,b,l;i<L;i++)
		{
			scanf("%lld%lld%lld",&a,&b,&l),--a,--b;
			EDGE.push_back(Edge(a,b,l));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		int ans=INF;
		while(!pq.empty())
		{
			const Pq p=pq.top();pq.pop();
			if(DIST[p._u]._u!=-1)
			{
				if(DIST[p._u]._id!=p._id)getmin(ans,p._dist+DIST[p._u]._dist);
				continue;
			}
			DIST[p._u]=p;
			for(const int ei:ET[p._u])
			{
				const Edge &e=EDGE[ei];
				const int nxt=(p._u==e._a?e._b:e._a);
				pq.push(Pq(nxt,p._dist+e._length,p._id));
			}
		}
		assert(ans!=INF);
		printf("%lld\n",(long long)ans*3LL);
	}
	return 0;
}


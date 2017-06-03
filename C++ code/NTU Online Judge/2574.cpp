#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
struct Pq
{
	int U,DIST;
	Pq(){}
	Pq(const int _U,const int _DIST):U(_U),DIST(_DIST){}
};
bool operator<(const Pq &a,const Pq &b){return a.DIST>b.DIST;}
void Dijkastra(const int source,const vector<pair<int,int> >*et,int *dist)
{
	priority_queue<Pq>pq;
	pq.push(Pq(source,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(dist[p.U]!=-1)continue;
		dist[p.U]=p.DIST;
		for(const auto &nxt:et[p.U])pq.push(Pq(nxt.first,p.DIST+nxt.second));
	}
}
int N,M,D1[100000],DN[100000],A[100000],B[100000],C[100000];
vector<pair<int,int> >ET[100000],EF[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear(),EF[i].clear();
		for(int i=0;i<M;i++)
		{
			int &a=A[i],&b=B[i],&c=C[i]; 
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			ET[a].push_back(make_pair(b,c));
			EF[b].push_back(make_pair(a,c));
		}
		for(int i=0;i<N;i++)D1[i]=DN[i]=-1;
		Dijkastra(0,ET,D1);
		Dijkastra(N-1,EF,DN);
		const int dist=D1[N-1];
		for(int i=0;i<M;i++)
		{
			if(i)putchar(' ');
//			assert(D1[A[i]]!=-1&&DN[B[i]]!=-1);
			printf("%d",D1[A[i]]!=-1&&DN[B[i]]!=-1?D1[A[i]]+C[i]+DN[B[i]]-dist:-1);
		}
		puts("");
	}
	return 0;
}

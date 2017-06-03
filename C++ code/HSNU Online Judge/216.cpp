#include<cstdio>
#include<queue>
#include<set>
#include<cassert>
using namespace std;
int M,N,DIST[200][200],S[1000];
struct Pq
{
	int o,a,b,c;
	Pq(){}
	Pq(const int &oo,const int &aa,const int &bb,const int &cc):o(oo),a(min(aa,bb)),b(max(aa,bb)),c(cc){while(o<N&&S[o+1]==S[o])o++;}
	bool operator<(const Pq &p)const{return c>p.c;}
	int Code(){return o*40000+a*200+b;}
};
set<int>VIS;
int Solve()
{
	VIS.clear();
	priority_queue<Pq>pq;
	pq.push(Pq(0,1,2,DIST[0][S[0]]));
	pq.push(Pq(0,0,2,DIST[1][S[0]]));
	pq.push(Pq(0,0,1,DIST[2][S[0]]));
	while(!pq.empty())
	{
		Pq u=pq.top();pq.pop();
		if(VIS.find(u.Code())!=VIS.end())continue;
		VIS.insert(u.Code());
//		printf("%d:(%d,%d)%d\n",u.o,u.a,u.b,u.c);
		if(u.o+1>=N)return u.c;
		pq.push(Pq(u.o+1,u.a,u.b,u.c+DIST[S[u.o]][S[u.o+1]]));
		pq.push(Pq(u.o+1,S[u.o],u.b,u.c+DIST[u.a][S[u.o+1]]));
		pq.push(Pq(u.o+1,S[u.o],u.a,u.c+DIST[u.b][S[u.o+1]]));
	}
	assert(0);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&M);
	for(int i=0;i<M;i++)for(int j=0;j<M;j++)scanf("%d",&DIST[i][j]);
//	puts("a");
	for(int i=0;i<M;i++)assert(DIST[i][i]==0);
//	puts("b");
	for(N=0;scanf("%d",&S[N])==1;S[N++]--);
//	printf("N=%d,M=%d\n",N,M);
	printf("%d\n",Solve());
	return 0;
}

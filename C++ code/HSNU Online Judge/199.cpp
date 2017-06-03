#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>
using namespace std;
struct Pq
{
	int a,b,city;
	Pq(){}
	Pq(const int _a,const int _b,const int _c):a(_a),b(_b),city(_c){}
	bool operator<(const Pq &p)const{return city>p.city;}
};
int N,M;
vector<int>ET[100],EF[100];
int Solve()
{
	static bool vis[100][100];
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)vis[i][j]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0,1));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(vis[p.a][p.b])continue;
		vis[p.a][p.b]=true;
		printf("(%d,%d)=%d\n",p.a+1,p.b+1,p.city);
		if(p.a==1&&p.b==1)return p.city;
		for(const int nxt:ET[p.a])pq.push(Pq(nxt,p.b,p.city+(nxt==p.b?0:1)));
		for(const int nxt:EF[p.b])pq.push(Pq(p.a,nxt,p.city+(p.a==nxt?0:1)));
	}
	assert(0);return -1;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EF[i].clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),a--,b--,ET[a].push_back(b),EF[b].push_back(a);
		printf("%d\n",Solve());
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct Dp
{
	int rlen,cnt,p;
	Dp(){}
	Dp(const int _rlen,const int _cnt,const int _p):rlen(_rlen),cnt(_cnt),p(_p){}
};
struct Edge
{
	int a,b,dist;
	Edge(){}
	Edge(const int _a,const int _b,const int _dist):a(_a),b(_b),dist(_dist){}
};
vector<Edge>EDGE;
int N,L,P[1000];
vector<int>ET[1000];
vector<Dp>GetDP(const int u,const int pre_ei)
{
	vector<vector<Dp> >ch_ans;
	for(const int ei:ET[u])if(ei!=pre_ei)
	{
		const Edge &e=EDGE[ei];
		const int nxt=(u==e.a?e.b:e.a);
		ch_ans.push_back(GetDP(nxt,ei));
	}
	Dp best=Dp(0,0,P[u]);
	for(const auto &s:ch_ans)
	{
		best.rlen+=s.front().rlen;
		best.cnt+=s.front().cnt;
		best.p+=s.front().p;
	}
	if(best.p>=L)
	{
		if(pre_ei!=-1)best.rlen+=EDGE[pre_ei].dist;
		++best.cnt;
		best.p=0;
	}
	vector<Dp>ans;
	ans.push_back(best);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&L)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0;i<N;i++)scanf("%d",&P[i]);
		for(int i=0,a,b,dist;i<N-1;i++)
		{
			scanf("%d%d%d",&a,&b,&dist),--a,--b;
			EDGE.push_back(Edge(a,b,dist));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		Dp ans=GetDP(0,-1)[0];
		printf("rlen=%d,cnt=%d,p=%d\n",ans.rlen,ans.cnt,ans.p);
		printf("cnt=%d\n",ans.cnt);
	}
	return 0;
}

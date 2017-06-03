#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
struct Dp
{
	int rlen,cnt,p;
	Dp(){}
	Dp(const int _rlen,const int _cnt,const int _p):rlen(_rlen),cnt(_cnt),p(_p){}
	bool operator<(const Dp &d)const
	{
		if(cnt!=d.cnt)return cnt>d.cnt;
		if(p!=d.p)return p>d.p;
		if(rlen!=d.rlen)return rlen<d.rlen;
		return false;
	}
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
	Dp best=Dp(0,0,-1);
	for(const auto &s:ch_ans)
	{
		int rlen=0,cnt=0;
		for(const Dp &d:s)getmax(rlen,d.rlen),getmax(cnt,d.cnt);
		best.rlen+=rlen;
		best.cnt+=cnt;
	}
	static int dp[2][5001][51];
	for(int i=0;i<=best.rlen;i++)for(int j=0;j<=best.cnt;j++)dp[0][i][j]=-INF;
	int d=0;
	dp[0][0][0]=0;
	for(const auto &s:ch_ans)
	{
		for(int i=0;i<=best.rlen;i++)for(int j=0;j<=best.cnt;j++)dp[d^1][i][j]=-INF;
		for(const Dp &v:s)
		{
			for(int i=0;i<=best.rlen;i++)for(int j=0;j<=best.cnt;j++)if(dp[d][i][j]!=-INF)
			{
				getmax(dp[d^1][i+v.rlen][j+v.cnt],dp[d][i][j]+v.p);
			}
		}
		d^=1;
	}
	vector<Dp>ans;
	for(int i=0;i<=best.rlen;i++)for(int j=0;j<=best.cnt;j++)if(dp[d][i][j]!=-INF)
	{
		Dp v=Dp(i,j,dp[d][i][j]+P[u]);
		ans.push_back(v);
		if(v.p>=L)
		{
			v.p=0;
			++v.cnt;
			if(pre_ei!=-1)v.rlen+=EDGE[pre_ei].dist;
			ans.push_back(v);
		}
	}
	sort(ans.begin(),ans.end());
	while(!ans.empty()&&ans.back().cnt<ans.front().cnt-1)ans.pop_back();
	return ans;
}
#include<utility>
int main()
{
//	freopen("in.txt","r",stdin);
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
		const vector<Dp>&result=GetDP(0,-1);
		pair<int,int>ans=make_pair(-INF,-INF);
		for(const Dp &v:result)if(v.p==0)
		{
			getmax(ans,make_pair(v.cnt,-v.rlen));
		}
		if(ans.first==-INF)puts("-1");
		else printf("%d %d\n",ans.first,-ans.second);
	}
	return 0;
}

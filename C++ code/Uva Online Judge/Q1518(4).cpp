#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<map>
#include<queue>
using namespace std;
//void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const double INF=1e100;
void getmin(double &a,const double &b){if(b<a)a=b;}
int N;
map<string,int>IDX;
struct Edge
{
	int from,to,start,duration,possibility,delay;
	Edge(){}
	Edge(const int _f,const int _t,const int _s,const int _du,const int _p,const int _de):from(_f),to(_t),start(_s),duration(_du),possibility(_p),delay(_de){}
};
vector<Edge>EDGE;
vector<int>ET[2002],EF[2002];
double DP[2002][60];
int GetIdx(const string &s)
{
	const auto it=IDX.find(s);
	if(it!=IDX.end())return it->second;
	assert(N<2002);
	ET[N].clear(),EF[N].clear();
	for(int i=0;i<60;i++)DP[N][i]=INF;
	return IDX[s]=N++;
}
int ORIGIN,DESTINATE;
bool INQ[2002];
void Solve()
{
	for(int i=0;i<N;i++)INQ[i]=false;
	queue<int>q;
	q.push(DESTINATE),INQ[DESTINATE]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		for(const auto ei:EF[u])
		{
			const Edge &e=EDGE[ei];
			for(int time=0;time<60;time++)
			{
				double ta=(time<=e.start?e.start-time:e.start+60.0-time);
				ta+=(1.0-e.possibility/100.0)*(e.duration+DP[u][(e.start+e.duration)%60]);
				for(int i=1;i<=e.delay;i++)ta+=e.possibility/100.0/e.delay*(e.duration+i+DP[u][(e.start+e.duration+i)%60]);
				if(ta<DP[e.from][time])
				{
					DP[e.from][time]=ta;
					if(!INQ[e.from])q.push(e.from),INQ[e.from]=true;
				}
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		N=0,IDX.clear(),EDGE.clear();
		static char name1[21],name2[21];
		assert(scanf("%s%s",name1,name2)==2);
		ORIGIN=GetIdx(name1),DESTINATE=GetIdx(name2);
		assert(ORIGIN!=DESTINATE);
		static int connectcount;assert(scanf("%d",&connectcount)==1);
		while(connectcount--)
		{
			static int m,t,p,d;
			assert(scanf("%s%s%d%d%d%d",name1,name2,&m,&t,&p,&d)==6);
			const int from=GetIdx(name1),to=GetIdx(name2);
			assert(m>=0&&m<60&&p>=0&&p<=100&&from!=to);
			const int sz=EDGE.size();
			EDGE.push_back(Edge(from,to,m,t,p,d));
			ET[from].push_back(sz),EF[to].push_back(sz);
		}
		for(int i=0;i<60;i++)DP[DESTINATE][i]=0.0;
		Solve();
		double ans=INF;
		for(int i=0;i<60;i++)getmin(ans,DP[ORIGIN][i]);
		if(ans==INF)puts("IMPOSSIBLE");
		else
		{
			static char tmp[10000];
			sprintf(tmp,"%.8f",ans);
			int n=-1;while(tmp[++n]);
			while(tmp[--n]=='0')tmp[n]='\0';
			if(tmp[n]=='.')tmp[n]='\0';
			puts(tmp);
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}

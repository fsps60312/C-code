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
vector<int>EF[2002];
double DP[2002][60];
int GetIdx(const string &s)
{
	const auto it=IDX.find(s);
	if(it!=IDX.end())return it->second;
	assert(N<2002);
	EF[N].clear();
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
				double ta=(time<=e.start?(double)e.start-(double)time:(double)e.start+60.0-(double)time);
				ta+=(1.0-(double)e.possibility/100.0)*((double)e.duration+DP[u][(e.start+e.duration)%60]);
				double tmp=(double)(e.duration*e.delay+(1+e.delay)*e.delay/2);
				for(int i=1;i<=e.delay;i++)tmp+=DP[u][(e.start+e.duration+i)%60];
				ta+=(double)e.possibility/100.0/(double)e.delay*tmp;
				if(ta<DP[e.from][time])
				{
					DP[e.from][time]=ta;
					if(!INQ[e.from])q.push(e.from),INQ[e.from]=true;
				}
			}
		}
	}
}
//unsigned int Rand()
//{
//	static unsigned int seed=20151216;
//	seed*=0xdefaced;seed+=165604;
//	return seed+=seed>>20;
//}
int main()
{
//	double accuracy test
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
//	double ccc=0.0;
//	for(int i=0;i<1000;i++)
//	{
//		double aaa=0.0;
//		vector<double>bbb;
//		for(int i=0;i<120;i++)for(int j=0;j<1000;j++)
//		{
//			double v=Rand();
//			for(int k=0;k<10;k++)v*=Rand();
//			bbb.push_back(v),aaa+=v;
//		}
//		double mx=aaa;
//		for(auto v:bbb)aaa-=v;
//		if(aaa<0.0)aaa=-aaa;
//		if(aaa/mx>ccc)ccc=aaa/mx;
//	}
//	printf("%.15f\n",ccc);return 0;
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
			EF[to].push_back(sz);
		}
		for(int i=0;i<60;i++)DP[DESTINATE][i]=0.0;
		Solve();
		double ans=INF;
		for(int i=0;i<60;i++)getmin(ans,DP[ORIGIN][i]);
		if(ans==INF)puts("IMPOSSIBLE");
		else
		{
			static char tmp[10000];
			sprintf(tmp,"%.9f",ans);
//			trim trailing zeros: seems no effect
//			int n=-1;while(tmp[++n]);
//			while(tmp[--n]=='0')tmp[n]='\0';
//			if(tmp[n]=='.')tmp[n]='\0';
			puts(tmp);
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}

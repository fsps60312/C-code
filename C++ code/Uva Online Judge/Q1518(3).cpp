#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<map>
using namespace std;
void getmin(double &a,const double &b){if(b<a)a=b;}
int N;
map<string,int>IDX;
struct Edge
{
	int to,start,duration,possibility,delay;
	Edge(){}
	Edge(const int _t,const int _s,const int _du,const int _p,const int _de):to(_t),start(_s),duration(_du),possibility(_p),delay(_de){}
};
vector<Edge>ET[1000];
double DP[1000][60];
int GetIdx(const string &s)
{
	const auto it=IDX.find(s);
	if(it!=IDX.end())return it->second;
	ET[N].clear();
	for(int i=0;i<60;i++)DP[N][i]=-1.0;
	return IDX[s]=N++;
}
int ORIGIN,DESTINATE;
double GetDP(const int place,const int time)
{
	double &dp=DP[place][time];
	if(dp!=-1.0)return dp;
	dp=1e100;
	for(const Edge &e:ET[place])
	{
		const double wait=(time<=e.start?e.start-time:e.start+60.0-time);
		double ta=0.0;
		ta+=(100.0-e.possibility)/100.0*GetDP(e.to,(e.start+e.duration)%60);
		for(int i=1;i<=e.delay;i++)
		{
			ta+=e.possibility/100.0/e.delay*GetDP(e.to,(e.start+e.duration+i)%60);
		}
		getmin(dp,ta+wait);
	}
	return dp;
}
int main()
{
	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		N=0,IDX.clear();
		static char name1[21],name2[21];
		assert(scanf("%s%s",name1,name2)==2);
		ORIGIN=GetIdx(name1),DESTINATE=GetIdx(name2);
		static int connectcount;assert(scanf("%d",&connectcount)==1);
		while(connectcount--)
		{
			static int m,t,p,d;
			assert(scanf("%s%s%d%d%d%d",name1,name2,&m,&t,&p,&d)==6);
			const int from=GetIdx(name1),to=GetIdx(name2);
			ET[from].push_back(Edge(to,m,t,p,d));
		}
		for(int i=0;i<60;i++)DP[DESTINATE][i]=0.0;
		double ans=1e100;
		for(int i=0;i<60;i++)getmin(ans,GetDP(ORIGIN,i));
		if(ans==1e100)puts("IMPOSSIBLE");
		else printf("%.9f\n",ans);
	}
	return 0;
}

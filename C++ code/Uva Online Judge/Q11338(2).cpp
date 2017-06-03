#include<cstdio>
#include<cassert>
#include<utility>
#include<vector>
#include<cmath>
#include<queue>
using namespace std;
int N;
double X,Y,D;
vector<pair<double,double> >S;
double Sq(const double &v){return v*v;}
double Dist(const pair<double,double>&a,const pair<double,double>&b){return sqrt(Sq(a.first-b.first)+Sq(a.second-b.second));}
struct Pq
{
	int u;
	double dist;
	Pq(const int _u,const double &_dist):u(_u),dist(_dist){}
	bool operator<(const Pq &p)const{return dist>p.dist;}
};
double Solve()
{
	bool *vis=new bool[N];
	for(int i=0;i<N;i++)vis[i]=false;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0.0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(vis[p.u])continue;
		vis[p.u]=true;
		if(p.u==1)return p.dist;
		for(int i=0;i<N;i++)if(Dist(S[p.u],S[i])<=1.5)pq.push(Pq(i,p.dist+Dist(S[p.u],S[i])));
	}
	return 1e100;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf",&X,&Y)==2)
	{
		S.clear();
		S.push_back(make_pair(0.0,0.0));
		S.push_back(make_pair(X,Y));
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%lf%lf",&X,&Y);
			S.push_back(make_pair(X,Y));
		}
		scanf("%lf",&D);
		N+=2;
//		printf("Solve=%.8f\n",Solve());
		if(Solve()<=D)puts("I am lucky!");
		else puts("Boom!");
	}
	return 0;
}

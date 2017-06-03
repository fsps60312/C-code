#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
#include<cmath>
using namespace std;
struct Point
{
	double x,y,z;
	double dist;
	int pre_id;
	Point(){}
	Point(const double _x,const double _y,const double _z):x(_x),y(_y),z(_z){}
	bool operator<(const Point &p)const{return z<p.z;}
};
double Sq(const double a){return a*a;}
double Dist(const Point &a,const Point &b){return sqrt(Sq(a.x-b.x)+Sq(a.y-b.y)+Sq(a.z-b.z));}
void Solve2(const vector<Point>&pre,vector<Point>&now,const int pl,const int pr,const int nl,const int nr)
{
	if(nl>nr)return;
	const int nmid=(nl+nr)/2;
	int &pmid=now[nmid].pre_id=-1;
	double &mindist=now[nmid].dist=1e300;
	for(int i=pl;i<=pr;i++)
	{
		const double dist=pre[i].dist+Dist(pre[i],now[nmid]);
		if(dist<mindist)mindist=dist,pmid=i;
	}
	assert(pmid!=-1);
	Solve2(pre,now,pl,pmid,nl,nmid-1),Solve2(pre,now,pmid,pr,nmid+1,nr);
}
int N;
vector<Point>S[200001];
double Solve1(const int l,const int r,const vector<int>&lowbound,const vector<int>&upbound)
{
	if(l>r)return 1e300;
	const int mid=(l+r)/2;
	for(int i=lowbound[1];i<=upbound[1];i++)S[1][i].dist=Dist(S[0][mid],S[1][i]),S[1][i].pre_id=mid;
	for(int i=2;i<=N;i++)Solve2(S[i-1],S[i%N],lowbound[i-1],upbound[i-1],lowbound[i%N],upbound[i%N]);
	double ans=S[0][mid].dist;
	vector<int>midbound;
	midbound.resize(N,0);
	for(int i=N-1,cur=S[0][mid].pre_id;i>=1;cur=S[i--][cur].pre_id)midbound[i]=cur;
	midbound[0]=mid;
	return min(ans,min(Solve1(l,mid-1,lowbound,midbound),Solve1(mid+1,r,midbound,upbound)));
}
int main()
{
	freopen("underground.in","r",stdin);
	freopen("underground.out","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)S[i].clear();
		for(int i=0,cnt;i<N;i++)
		{
			double x,y,z;scanf("%lf%lf%d",&x,&y,&cnt);
			while(cnt--)scanf("%lf",&z),S[i].push_back(Point(x,y,z));
			sort(S[i].begin(),S[i].end());
		}
		vector<int>lowbound,upbound;
		for(int i=0;i<N;i++)lowbound.push_back(0),upbound.push_back((int)S[i].size()-1);
		printf("%.9f\n",Solve1(0,(int)S[0].size()-1,lowbound,upbound));
	}
	return 0;
}

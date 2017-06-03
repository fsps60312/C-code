#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
#include<set>
#include<cmath>
using namespace std;
const double PI=acos(-1.0),EPS=1e-9;
double A;
inline double F(const double t)
{
	return max(0.0,A*t);
}
inline double getA(const double t)
{
	return 0.5*F(t)*F(t)-0.5*F(t-2.0*PI)*F(t-2.0*PI);
}
inline double Integrate(const double l,const double r)
{
	assert(l<=r);
	const double mid=(l+r)/2.0;
	const double v=getA(mid),nxtV=(getA(l)+4.0*getA(mid)+getA(r))/6.0;
	if(fabs(v-nxtV)<EPS)return nxtV*(r-l);
	else return Integrate(l,mid)+Integrate(mid,r);
}
int N,M;
vector<double>THETA;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		static int kase=0;
		printf("Spiral %d: ",++kase);
		scanf("%lf",&A);
		THETA.clear();
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			double v;
			scanf("%lf",&v);
			THETA.push_back(v);
		}
		sort(THETA.begin(),THETA.end());
		scanf("%d",&M);
		if(THETA.empty()&&M>0)
		{
			for(int i=0;i<M;i++)
			{
				double t,r;
				scanf("%lf%lf",&r,&t);
			}
			puts("-1");
			continue;
		}
		{
			set<pair<int,int> >regions;
			for(int i=0;i<M;i++)
			{
				const double mod=2.0*PI*A;
				double t,r;
				scanf("%lf%lf",&r,&t);
				auto it=upper_bound(THETA.begin(),THETA.end(),t);
				if(it==THETA.end())it=THETA.begin(),t-=2.0*PI;
				regions.insert(make_pair(it-THETA.begin(),(int)((r-A*t)/mod+1.0+EPS)));
			}
			double ans=0;
			for(const auto &p:regions)
			{
				assert(p.first>=0);
				const double l=2.0*PI*p.second+(p.first==0?THETA[N-1]-2.0*PI:THETA[p.first-1]);
				const double r=2.0*PI*p.second+THETA[p.first];
//				printf("(%.3f,%.3f): +%.4f\n",l,r,Integrate(l,r));
				ans+=Integrate(l,r);
			}
			printf("%.4f liters\n",ans/10.0);
		}
	}
	return 0;
}

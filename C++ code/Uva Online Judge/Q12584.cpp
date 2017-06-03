#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
struct LapTop
{
	double c,t,r;
	LapTop(){}
	LapTop(const double &_c,const double &_t,const double &_r):c(_c),t(_t),r(_r){}
};
int N;
double C;
vector<LapTop>L;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int querycount;
	while(scanf("%d%d",&N,&querycount)==2)
	{
		if(N==0&&querycount==0)break;
		scanf("%lf",&C);
		L.clear();
		double discharge_rate=0.0,remain_capacity=0.0;
		for(int i=0;i<N;i++)
		{
			static LapTop l;
			scanf("%lf%lf%lf",&l.c,&l.t,&l.r);
			L.push_back(l);
			discharge_rate+=l.c/l.t;
			remain_capacity+=l.r;
		}
		static int kase=1;
		printf("Case %d:\n",kase++);
		if(true)
		{
			const double ans=discharge_rate/C;
			printf("%d\n",fabs(ans-round(ans))<EPS?(int)(ans+0.5):(int)ans+1);
		}
		for(int m;querycount--;)
		{
			scanf("%d",&m);
			if(discharge_rate<=m*C+EPS)puts("-1.000");
			else
			{
				const double ans=remain_capacity/(discharge_rate-m*C);
				if(ans>100000.0)puts("-1.000");
				else printf("%.3f\n",ans);
			}
		}
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double EPS=1e-9;
struct Laptop
{
	double c,t,r;
	Laptop(){}
	Laptop(const double &_c,const double &_t,const double &_r):c(_c),t(_t),r(_r){}
	bool operator<(const Laptop &l)const{return r/(c/t)<l.r/(l.c/l.t);}
};
int N;
double C;
vector<Laptop>L;
double Solve(const int m)
{
	if(m==0)return L[0].r/(L[0].c/L[0].t);
	double total_remain=0.0,remain=0.0,total_d_rate,d_rate=0.0;
	for(const auto &l:L)total_remain+=l.r,total_d_rate+=l.c/l.t;
	for(int i=0;i<m;i++)remain+=L[i].r,d_rate+=L[i].c/L[i].t;
	for(int i=m;i<N;i++)
	{
		const Laptop &lap=L[i];
		if(d_rate>C*m+EPS&&remain/(d_rate-C*m)<lap.r/(lap.c/lap.t))return remain/(d_rate-C*m);
		remain+=lap.r,d_rate+=lap.c/lap.t;
	}
	return remain/(d_rate-C*m);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int querycount;
	while(scanf("%d%d",&N,&querycount)==2)
	{
		if(N==0&&querycount==0)break;
		scanf("%lf",&C);
		L.clear();
		double discharge_rate=0.0;
		for(int i=0;i<N;i++)
		{
			static Laptop l;
			scanf("%lf%lf%lf",&l.c,&l.t,&l.r);
			L.push_back(l);
			discharge_rate+=l.c/l.t;
		}
		static int kase=1;
		printf("Case %d:\n",kase++);
		if(true)
		{
			const double ans=discharge_rate/C;
			printf("%d\n",fabs(ans-round(ans))<EPS?(int)(ans+0.5):(int)ans+1);
		}
		sort(L.begin(),L.end());
		for(int m;querycount--;)
		{
			scanf("%d",&m);
			if(discharge_rate<=m*C+EPS)puts("-1.000");
			else
			{
				const double ans=Solve(m);
				if(ans>100000.0)puts("-1.000");
				else printf("%.3f\n",ans);
			}
		}
	}
	return 0;
}

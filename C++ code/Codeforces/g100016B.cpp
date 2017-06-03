#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Opl
{
	double angle;
	int id;
	bool operator<(const Opl &o)const{return angle<o.angle;}
};
int N,K;
Opl OPL[2000];
double DP[2000][2000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%lf",&OPL[i].angle),OPL[i].id=i+1;
		sort(OPL,OPL+N);
		for(int i=0;i<N;i++)OPL[N+i]=OPL[i];
		double max_area=0.0;
		vector<int>best_ans;
		for(int i=0;i<N;i++)
		{
			vector<int>ans;
			const double &area=Solve(OPL+i,ans);
			if(area>max_area)max_area=area,best_ans=ans;
		}
		if(best_ans.empty())puts("0");
		else
		{
			sort(best_ans.begin(),best_ans.end(),[](const int a,const int b)->bool{return OPL[a].angle<OPL[b].angle;});
			for(int i=0;i<K;i++)
			{
				if(i)putchar(' ');
				printf("%d",best_ans[i]);
			}
			puts("");
			assert((int)best_ans.size()==K);
		}
		//sin(a)+sin(b)=sin((a+b)/2+(a-b)/2)+sin((a+b)/2-(a-b)/2)
		//=sin((a+b)/2)cos((a-b)/2)+cos((a+b)/2)sin((a-b)/2)
	}
	return 0;
}

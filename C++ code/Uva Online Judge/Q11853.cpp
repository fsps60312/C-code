#include<cstdio>
#include<cmath>
#include<vector>
#include<cassert>
#include<map>
using namespace std;
const double PI=acos(-1.0);
struct Oppo
{
	double x,y,range;
	Oppo(){}
	Oppo(const double &_x,const double &_y,const double &_r):x(_x),y(_y),range(_r){}
};
struct Arrow
{
	double x,y;
	Arrow(){}
	Arrow(const double &_x,const double &_y):x(_x),y(_y){}
	int Quadrant()const
	{
		if(x<0.0&&y<=0.0)return 1;
		if(x<=0.0&&y>0.0)return 2;
		if(x>0.0&&y>=0.0)return 3;
		if(x>=0.0&&y<0.0)return 4;
		assert(0);return -1;
	}
	bool operator<(const Arrow &b)const
	{
		const int qa=Quadrant(),qb=b.Quadrant();
		if(qa!=qb)return qa<qb;
		const double ra=sqrt(x*x+y*y),rb=sqrt(b.x*b.x+b.y*b.y);
		if(qa==1)return x/ra<b.x/rb;
		if(qa==2)return x/ra<b.x/rb;
		if(qa==3)return x/ra>b.x/rb;
		if(qa==4)return x/ra>b.x/rb; 
		assert(0);return false;
	}
};
double Sq(const double &a){return a*a;}
int N;
vector<Oppo>OPPO;
vector<int>ET[1001];
int FirstTouchButtom()
{
	double loc=1e100;
	int ans=-1;
	for(int i=0;i<N;i++)
	{
		const Oppo &o=OPPO[i];
		if(o.y<=o.range)
		{
			double x=o.x-sqrt(o.range*o.range-o.y*o.y);
			if(x<loc)loc=x,ans=i;
		}
	}
	return ans;
}
void BuildEdge()
{
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
	{
		Oppo &oa=OPPO[i],&ob=OPPO[j];
		if(Sq(oa.range+ob.range)<Sq(oa.x-ob.x)+Sq(oa.y-ob.y))ET[i].push_back(j),ET[j].push_back(i);
	}
	for(int i=0;i<N;i++)
	{
		multimap<Arrow,int>idx;
		for(const auto nxt:ET[i])idx.insert(make_pair(Arrow(OPPO[nxt].x-OPPO[i].x,OPPO[nxt].y-OPPO[i].y),nxt));
		ET[i].clear();
		for(const auto &it:idx)ET[i].push_back(it.second);
	}
}
bool Solve(double &lans,double &rans)
{
	const int start=FirstTouchButtom();
	if(start==-1){lans=0.0,rans=0.0;return true;}
	if(OPPO[start].x<=OPPO[start].range)lans=OPPO[start].y+sqrt(Sq(OPPO[start].range)-Sq(OPPO[start].x));
	else lans=0.0;
	BuildEdge();
	
}
int main()
{
	static int casecount;scanf("%d",&casecount);
	while(casecount--)
	{
		scanf("%d",&N);
		OPPO.clear();
		for(int i=0;i<N;i++)
		{
			static double x,y,r;
			scanf("%lf%lf%lf",&x,&y,&r),OPPO.push_back(Oppo(x,y,r));
		}
		double lans,rans;
		if(Solve(lans,rans))printf("%.2lf %.2lf %.2lf %.2lf\n",0.0,lans,1000.0,rans);
		else puts("IMPOSSIBLE");
	}
	return 0;
}

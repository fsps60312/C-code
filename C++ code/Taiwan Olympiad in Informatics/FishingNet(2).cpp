#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
bool IsOnLeft(const double x1,const double y1,const double x2,const double y2,bool normal)
{
	bool ans=(x1*y2-x2*y1>0.0);
	return normal?ans:!ans;
}
bool IsOnRight(const double x1,const double y1,const double x2,const double y2,bool normal)
{
	return !IsOnLeft(x1,y1,x2,y2,normal);
}
bool ShouldAdd(map<double,double>&s,const double x,const double y,bool is_up)
{
	if(s.empty())return true;
	auto itt=s.find(x);
	const bool found=(itt!=s.end());
	if(found)
	{
		if(is_up&&y<=itt->second)return false;
		if(!is_up&&y>=itt->second)return false;
	}
	else
	{
		itt=s.upper_bound(x);
		if(itt!=s.end()&&itt!=s.begin())
		{
			auto il=itt,ir=itt;--il;
			if(IsOnLeft(x-il->first,y-il->second,ir->first-il->first,ir->second-il->second,is_up))return false;
		}
	}
	const auto it=itt;
	auto ir=s.begin(),im=s.begin();
	if(found)im=ir=it,++im,++ir;
	else im=ir=it;
	if(ir!=s.end())
	{
		++ir;
		for(;ir!=s.end()&&IsOnRight(im->first-ir->first,im->second-ir->second,x-ir->first,y-ir->second,is_up);++ir,s.erase(im++));
	}
	auto il=s.begin();
	if(found)il=im=it;
	else il=im=it;
	if(il!=s.begin())
	{
		puts("start");
		printf("im=(%.3f,%.3f),il=(%.3f,%.3f)\n",im->first,im->second,il->first,il->second);
		--il,--im;
		printf("im=(%.3f,%.3f),il=(%.3f,%.3f)\n",im->first,im->second,il->first,il->second);
		if(il!=s.begin())
		{
	puts("b");
			--il;
			printf("im=(%.3f,%.3f),il=(%.3f,%.3f)\n",im->first,im->second,il->first,il->second);
			for(;IsOnLeft(im->first-il->first,im->second-il->second,x-il->first,y-il->second,is_up);)
			{
				puts("pass");
				s.erase(im--);
				if(il==s.begin())break;
				--il;
			}
	puts("c");
		}
	}
	return true;
}
#include<cmath>
double Hypot(const double x,const double y){return sqrt(x*x+y*y);}
double Length(const map<double,double>&s)
{
	double ans=0.0;
	auto il=s.begin(),ir=s.begin();
	if(ir!=s.end())
	{
		++ir;
		for(;ir!=s.end();++il,++ir)
		{
			ans+=Hypot(il->first-ir->first,il->second-ir->second);
		}
	}
	return ans;
}
int N;
map<double,double>UP,DOWN;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		double x,y;scanf("%lf%lf",&x,&y);
		if(ShouldAdd(UP,x,y,true))UP[x]=y;
		if(ShouldAdd(DOWN,x,y,false))DOWN[x]=y;
	}
	
//	for(const auto &p:UP)printf("(%.2f,%.2f)",p.first,p.second);puts("");
//	for(const auto &p:DOWN)printf("(%.2f,%.2f)",p.first,p.second);puts("");
	printf("%d %.10f\n",(int)(UP.size()+DOWN.size())-2,Length(UP)+Length(DOWN));
	return 0;
}

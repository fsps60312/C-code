#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
const long double EPS=1e-9;
bool IsOnLeft(const long double x1,const long double y1,const long double x2,const long double y2,bool normal)
{
	if(normal)return x1*y2-x2*y1>EPS;
	else return x1*y2-x2*y1<-EPS;
}
bool IsOnRight(const long double x1,const long double y1,const long double x2,const long double y2,bool normal)
{
	if(!normal)return x1*y2-x2*y1>EPS;
	else return x1*y2-x2*y1<-EPS;
}
bool ShouldAdd(map<long double,long double>&s,const long double x,const long double y,bool is_up)
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
//	const auto it=itt;
	auto ir=s.begin(),im=s.begin();
	im=ir=s.upper_bound(x);
	if(ir!=s.end())
	{
		++ir;
		for(;ir!=s.end()&&!IsOnLeft(im->first-ir->first,im->second-ir->second,x-ir->first,y-ir->second,is_up);++ir,s.erase(im++));
	}
	auto il=s.begin();
	il=im=s.upper_bound(x);
	if(il!=s.begin())
	{
//		puts("start");
//		printf("im=(%.3f,%.3f),il=(%.3f,%.3f)\n",im->first,im->second,il->first,il->second);
		--il,--im;
//		printf("im=(%.3f,%.3f),il=(%.3f,%.3f)\n",im->first,im->second,il->first,il->second);
		if(il!=s.begin())
		{
//	puts("b");
			--il;
//			printf("im=(%.3f,%.3f),il=(%.3f,%.3f)\n",im->first,im->second,il->first,il->second);
			for(;!IsOnRight(im->first-il->first,im->second-il->second,x-il->first,y-il->second,is_up);)
			{
//				puts("pass");
				s.erase(im--);
				if(il==s.begin())break;
				--il;
			}
//	puts("c");
		}
	}
	return true;
}
#include<cmath>
long double Hypot(const long double x,const long double y){return sqrt(x*x+y*y);}
long double Length(const map<long double,long double>&s)
{
	long double ans=0.0;
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
map<long double,long double>UP,DOWN;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	int ans=0;
	for(int i=0;i<N;i++)
	{
		double x,y;scanf("%lf%lf",&x,&y);
		bool added=false;
		if(ShouldAdd(UP,x,y,true))UP[x]=y,added=true;
		if(ShouldAdd(DOWN,x,y,false))DOWN[x]=y,added=true;
		if(added)ans++;
	}
	
//	for(const auto &p:UP)printf("(%.2f,%.2f)",p.first,p.second);puts("");
//	for(const auto &p:DOWN)printf("(%.2f,%.2f)",p.first,p.second);puts("");
	printf("%d %.10f\n",(int)(UP.size()+DOWN.size())-2,(double)(Length(UP)+Length(DOWN)));
	return 0;
}

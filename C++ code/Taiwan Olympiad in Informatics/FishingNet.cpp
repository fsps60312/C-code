#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
int N;
map<double,double>UP,DOWN;
bool ShouldAddUP(const double x,const double y)
{
	if(UP.empty())return true;
	auto it=UP.find(x);
	const bool found=(it!=UP.end());
	if(found)
	{
		if(y<=it->second)return false;
	}
	else
	{
		it=UP.upper_bound(x);
		if(it!=UP.end()&&it!=UP.begin())
		{
			auto il=it,ir=it;--il;
			if(IsOnLeft(x-il->first,y-il->second,ir->first-il->first,ir->second-il->second))return false;
		}
	}
	auto ir=UP.begin(),im=UP.begin();
	if(found)im=ir=it,++im,++ir;
	else im=ir=it;
	if(ir!=UP.end())
	{
		++ir;
		for(;ir!=UP.end()&&IsOnRight(im->first-ir->first,im->second-ir->second,x-ir->first,y-ir->second);++ir,UP.erase(im++));
	}
	auto il;
	if(found)il=im=it;
	else il=im=it;
	if(il!=UP.begin())
	{
		--il,--im;
		if(il!=UP.begin())
		{
			--il;
			for(;IsOnLeft(im->first-il->first,im->second-il->second,x-il->first,y-il->second);--il,UP.erase(im--))
			{
				if(il==UP.begin())break;
			}
		}
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		double x,y;scanf("%lf%lf",&x,&y);
		if(ShouldAddUP(x,y))UP[x]=y;
		if(ShouldAddDOWN(x,y))DOWN[x]=y;
	}
	return 0;
}

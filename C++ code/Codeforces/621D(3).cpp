#include<cstdio>
#include<cassert>
#include<cmath>
#include<utility>
using namespace std;
const double EPS=1e-8;
char ANS[12][8]=
{
	"x^y^z",
	"x^z^y",
	"(x^y)^z",
	"(x^z)^y",
	"y^x^z",
	"y^z^x",
	"(y^x)^z",
	"(y^z)^x",
	"z^x^y",
	"z^y^x",
	"(z^x)^y",
	"(z^y)^x"
};
pair<bool,double>Log1(const double x,const double y,const double z)
{
//	return log(log(X)*pow(Y,Z))=log(log(X))+Z*log(Y)
	const double lx=log(x);
	pair<bool,double>ans;
	if(fabs(lx)<EPS)ans=make_pair(true,-1e300);
	else
	{
		ans.first=(lx>0.0);
		ans.second=log(fabs(lx))+z*log(y);
	}
	return ans;
}
pair<bool,double>Log2(const double x,const double y,const double z)
{
//	return log(log(x)*X*Y);
	const double lx=log(x);
	pair<bool,double>ans;
	if(fabs(lx)<EPS)ans=make_pair(true,-1e300);
	else
	{
		ans.first=(lx>0.0);
		ans.second=log(fabs(lx))+log(y)+log(z);
	}
	return ans;
}
double X,Y,Z;
pair<bool,double>GetValue(const int id)
{
	switch(id)
	{
		case 1:return Log1(X,Y,Z);
		case 2:return Log1(X,Z,Y);
		case 3:return Log2(X,Y,Z);
		case 4:return Log2(X,Z,Y);
		case 5:return Log1(Y,X,Z);
		case 6:return Log1(Y,Z,X);
		case 7:return Log2(Y,X,Z);
		case 8:return Log2(Y,Z,X);
		case 9:return Log1(Z,X,Y);
		case 10:return Log1(Z,Y,X);
		case 11:return Log2(Z,X,Y);
		case 12:return Log2(Z,Y,X);
		default:assert(0);return make_pair(false,-1.0);
	}
}
bool Bigger(const pair<bool,double>&a,const pair<bool,double>&b)
{
	if(a.first&&!b.first)return true;
	if(!a.first&&b.first)return false;
	if(a.first)
	{
		return a.second>b.second+EPS;
	}
	else
	{
		return a.second+EPS<b.second;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf%lf",&X,&Y,&Z)==3)
	{
		pair<bool,double>mx=GetValue(1);
		int ans=1;
		for(int i=2;i<=12;i++)
		{
			const pair<bool,double>&v=GetValue(i);
			if(Bigger(v,mx))mx=v,ans=i;
		}
		printf("%s\n",ANS[ans-1]);
	}
	return 0;
}

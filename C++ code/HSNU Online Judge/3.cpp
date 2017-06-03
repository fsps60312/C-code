#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
LL N;
struct City
{
	LL d,c;
	City(){}
	City(LL d,LL c):d(d),c(c){}
}CITY[100000];
bool Solve(LL money)
{
	LL sum=0;
	for(LL i=0;i<N;i++)sum+=max(0LL,CITY[i].c-money-CITY[i].d);
	for(LL i=0;i<N;i++)if(CITY[i].c<money)
	{
		sum-=money-CITY[i].c+CITY[i].d;
		if(sum<0)return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		LL l=0,r=0,mid;
		for(LL i=0;i<N;i++)
		{
			LL &c=CITY[i].c,&d=CITY[i].d;
			scanf("%lld%lld",&d,&c);
			r=max(r,c);
		}
		while(l<r)
		{
			mid=l+(r-l+1)/2;
			if(Solve(mid))l=mid;
			else r=mid-1;
		}
		printf("%lld\n",l);
	}
	return 0;
}

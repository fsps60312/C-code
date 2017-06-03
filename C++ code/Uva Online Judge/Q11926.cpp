#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
struct OneTime
{
	int l,r;
	OneTime(){}
	OneTime(const int _l,const int _r):l(_l),r(_r){} 
};
struct Repeat
{
	int l,r,interval;
	Repeat(){}
	Repeat(const int _l,const int _r,const int _i):l(_l),r(_r),interval(_i){}
};
vector<OneTime>ONETIME;
vector<Repeat>REPEAT;
bool Conflict(const OneTime &a,const OneTime &b){return min(a.r,b.r)>max(a.l,b.l);}
bool Conflict(const OneTime &a,const Repeat &b)
{
	if(a.r<=b.l)return false;
	if(Conflict(a,OneTime(b.l,b.r)))return true;
	assert(a.l>=b.r);
	int n=(a.l-b.r)/b.interval+1;
	int l=b.l+b.interval*n,r=b.r+b.interval*n;
	return Conflict(a,OneTime(l,r));
}
bool Conflict(const Repeat &a,const Repeat &b)
{
	
}
int N,M;
bool Solve()
{
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(Conflict(ONETIME[i],ONETIME[j]))return false;
	for(int i=0;i<N;i++)for(int j=0  ;j<M;j++)if(Conflict(ONETIME[i],REPEAT[j]))return false;
	for(int i=0;i<M;i++)for(int j=i+1;j<M;j++)if(Conflict(REPEAT[i],REPEAT[j]))return false;
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		ONETIME.clear(),REPEAT.clear();
		for(int i=0,a,b;i<N;i++)scanf("%d%d",&a,&b),ONETIME.push_back(OneTime(a,b));
		for(int i=0,a,b,c;i<M;i++)scanf("%d%d%d",&a,&b,&c),REPEAT.push_back(Repeat(a,b,c));
		puts(Solve()?"NO CONFLICT":"CONFLICT");
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<map>
using namespace std;
long long P,B,N;
struct pairtype
{
	long long x,y;
};
pairtype dfs(long long a,long long b,pairtype c,pairtype d)
{
	if(b==0)
	{
		if(a!=1) c.x=0;
		return c;
	}
	long long e=a/b;
	c.x-=d.x*e;
	c.y-=d.y*e;
	return dfs(b,a%b,d,c);
}
long long inverse(long long a)
{
	//ax+Py==1
	pairtype b,c;
	b.x=c.y=1;
	b.y=c.x=0;
	pairtype ans=dfs(a,P,b,c);
	return ans.x;
}
long long solve()
{
	long long a=sqrt(P)+1,now=1;
	map<long long,long long> ans;
	for(long long i=0;i<a;i++)
	{
		if(now==N) return i;
		if(ans.find(now)==ans.end()) ans[now]=i;
		now=now*B%P;
	}
	long long b=(inverse(now)%P+P)%P;
	for(long long i=1;i<a;i++)
	{
		N=N*b%P;
		if(ans.find(N)!=ans.end()) return i*a+ans[N];
	}
	return -1;
}
int main()
{
	while(scanf("%lld%lld%lld",&P,&B,&N)==3)
	{
		//B^L===N
		//x*x^-1===1
		//x*y-k*P==1
		long long ans=solve();
		if(ans!=-1) printf("%lld\n",ans);
		else printf("no solution\n");
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
void Gcd(const LL a,const LL b,LL &x,LL &y,const LL mod)
{
	if(b==0LL){assert(a==1LL);x=1LL,y=0LL;return;}
	Gcd(b,a%b,y,x,mod);//by+(a-a/b*b)x=1, ax+b(y-a/b*x)
	(y-=a/b*x)%=mod;
}
LL Rev(const LL v,const LL mod)
{
	static LL x,y;
	Gcd(v,mod,x,y,mod);
	return (x%mod+mod)%mod;
}
LL Pow(LL a,LL p,const LL mod)
{
	LL ans=1LL;
	for(;p;p>>=1)
	{
		if(p&1LL)(ans*=a)%=mod;
		(a*=a)%=mod;
	}
	return ans;
}
int N;
int main()
{
	const LL mod=1e9+7;
	while(scanf("%d",&N)==1)
	{
		map<int,int>map_s;
		for(int i=0,v;i<N;i++)scanf("%d",&v),map_s[v]++;
		vector<pair<int,int> >s;
		for(const auto &it:map_s)s.push_back(p);
		LL *left=new LL[s.size()+1],*rigt=new LL[s.size()+1];
		left[0]=1LL;
		for(int i=0;i<(int)s.size();i++)left[i+1]=left[i]*(s[i+1].second+1LL)%(mod-1LL);
		rigt[s.size()]=1LL;
		for(int i=(int)s.size()-1;i>=0;i--)rigt[i]=rigt[i+1]*(s[i].second+1LL)%(mod-1LL);
		LL ans=1LL;
		for(int i=0;i<(int)s.size();i++)
		{
			const auto &it=s[i];
			LL p=all*Rev(it.second+1LL,(LL)1e9+6)%((LL)1e9+6);
			(p*=(it.second+1LL)*it.second/2LL%((LL)1e9+6))%=((LL)1e9+6);
			(ans*=Pow(it.first,p,1e9+7))%=(LL)1e9+7;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

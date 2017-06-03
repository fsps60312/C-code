#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
using namespace std;
typedef long long LL;
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
		for(const auto &it:map_s)s.push_back(it);
		LL *left=new LL[s.size()+1],*rigt=new LL[s.size()+1];
		left[0]=1LL;
		for(int i=0;i<(int)s.size();i++)left[i+1]=left[i]*(s[i].second+1LL)%(mod-1LL);
		rigt[s.size()]=1LL;
		for(int i=(int)s.size()-1;i>=0;i--)rigt[i]=rigt[i+1]*(s[i].second+1LL)%(mod-1LL);
		LL ans=1LL;
		for(int i=0;i<(int)s.size();i++)
		{
			const auto &it=s[i];
//			printf("(%d,%d)\n",it.first,it.second);
			LL p=left[i]*rigt[i+1]%(mod-1LL);
			(p*=(it.second+1LL)*it.second/2LL%(mod-1LL))%=(mod-1LL);
			(ans*=Pow(it.first,p,mod))%=mod;
		}
		delete[]left;delete[]rigt;
		printf("%lld\n",ans);
	}
	return 0;
}

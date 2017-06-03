#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL A,B,C,D;
LL Gcd(LL a,LL b)
{
	if(b)while((a%=b)&&(b%=a));
	return a+b;
}
LL Solve()
{
	const LL g=Gcd(B,C);
	//Gcd(n*B,C)==D
	if(D%g!=0)return 0;
	//Gcd(n*(B/g),(C/g))==(D/g)
	//Gcd(n,(C/g))==(D/g)
	if(C%D!=0)return 0;
	C/=D;
	//Gcd(n/(D/g),(C/D))==1
	//n*B<A
	//n<=(A-1)/B
	//n/(D/g)<=(A-1)/B/(D/g)
	A=(A-1)/B/(D/g);
	vector<LL>p;
	for(LL i=2;i*i<=C;i++)if(C%i==0)
	{
		p.push_back(i);
		while((C/=i)%i==0);
	}
	if(C>1)p.push_back(C);
	vector<pair<LL,int> >f;
	f.push_back(make_pair(1,0));
	for(const LL &v:p)
	{
		for(int i=(int)f.size()-1;i>=0;i--)f.push_back(make_pair(f[i].first*v,f[i].second+1));
	}
	LL ans=0;
	for(const auto &v:f)(v.second&1?ans-=A/v.first:ans+=A/v.first);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
		printf("%lld\n",Solve());
	}
	return 0;
}

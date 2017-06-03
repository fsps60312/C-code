#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL PowMod(LL a,int p,const LL mod)
{
	LL ans=1LL;
	while(p)
	{
		if(p&1)(ans*=a)%=mod;
		(a*=a)%=mod;
		p>>=1;
	}
	return ans;
}
struct Poly
{
	vector<LL>s;
	int c,n;
	Poly(const int _c,const int _n):c(_c),n(_n){s.clear(),s.resize(n,0LL);}
	Poly operator*(const Poly &p)const
	{
		Poly ans=Poly(c+p.c,n);
		const LL m=PowMod(10,p.c,n);
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)
		{
			(ans.s[(i*m+j)%n]+=s[i]*p.s[j])%=MOD;
		}
		return ans;
	}
};
int N,B,K,X;
vector<Poly>PS;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&B,&K,&X)==4)
	{
		Poly now=Poly(1,X);
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			now.s[v%X]++;
		}
		PS.clear();
		PS.push_back(now);
		for(int i=1;i<=30;i++)
		{
			now=now*now;
			PS.push_back(now);
		}
		now=Poly(0,X);
		now.s[0]++;
		for(int i=0;i<=30;i++)if(B&(1<<i))now=now*PS[i];
		printf("%lld\n",now.s[K]);
	}
	return 0;
}

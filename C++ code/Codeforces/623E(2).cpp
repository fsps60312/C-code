#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
struct Poly
{
	vector<LL>S;
	int N;
	Poly(){}
	Poly(const int _N,const int _K):N(_N){S.resize(_K+1);}
	LL &operator[](const int i){return S[i];}
	LL operator[](const int i)const{return S[i];}
};
LL Pow2(LL p)
{
	LL ans=1LL,a=2LL;
	for(;p;p>>=1)
	{
		if(p&1LL)ans*=a;
		a*=a;
	}
	return ans;
}
int K;
LL C(const int a,const int b)
{
	LL ans=1LL;
	for(int i=b+1;i<=a;i++)(ans*=i)/=i-b;
	return ans;
}
Poly operator*(const Poly &a,const Poly &b)
{
	Poly s=Poly(a.N+b.N,K);
	s[0]=0LL;
	for(int i=1;i<=K;i++)
	{
		s[i]=0LL;
		for(int j=0;j<i;j++)
		{
			s[i]+=a[j]*b[i-j]*C(i,j)*Pow2((LL)j*b.N);
		}
	}
	return s;
}
LL N;
LL Solve()
{
	if(N>K)return 0LL;
	static Poly p[20];
	p[0]=Poly(1,K);
	for(int i=0;i<=K;i++)p[0][i]=1LL;
	p[0][0]=0LL;
	int bit;
	for(bit=1;(1<<bit)<=N;bit++)p[bit]=p[bit-1]*p[bit-1];
	Poly ans;
	bool inited=false;
	for(bit--;bit>=0;bit--)if(N&(1<<bit))
	{
		if(!inited)ans=p[bit],inited=true;
		else ans=ans*p[bit];
	}
	LL ret=0LL;
	for(int i=0;i<=K;i++)ret+=ans[i]*C(K,i);//,printf("ans[%d]=%lld\n",i,ans[i]);
	return ret;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%d",&N,&K)==2)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}

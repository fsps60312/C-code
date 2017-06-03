#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
void BuildPrime(vector<LL>&p,const LL bound)
{
	bool *isp=new bool[bound+1LL];
	for(LL i=2LL;i<=bound;i++)isp[i]=true;
	assert(p.empty());
	for(LL i=2LL;i<=bound;i++)
	{
		if(isp[i])p.push_back(i);
		for(int j=0;i*p[j]<=bound;j++)
		{
			isp[i*p[j]]=false;
			if(i%p[j]==0LL)break;
		}
	}
	delete[]isp;
//	for(int i=0;i<100;i++)printf("%lld\n",p[i]);
}
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
LL Gcd(const LL a,const LL b){return b==0?a:Gcd(b,a%b);}
void MakeCoprime(map<LL,int>&s)
{
	for(LL low=1LL;;)
	{
		map<LL,int>::iterator it0=s.lower_bound(low),it=it0;
		if(it0==s.end())break;
		const LL af=it->first;low=af+1LL;
		const int as=it->second;
		for(++it;it!=s.end();++it)
		{
			const LL bf=it->first;
			const int bs=it->second;
			const LL g=Gcd(af,bf);
			if(g!=1LL)
			{
				s.erase(it0);
				s.erase(it);
				s[g]+=as+bs;
				s[af/g]+=as;
				s[bf/g]+=bs;
				getmin(low,g),getmin(low,af/g),getmin(low,bf/g);
				break;
			}
		}
	}
//	for(map<LL,int>::iterator it=s.begin();it!=s.end();++it)printf("(%lld,%d)\n",it->first,it->second);puts("");
}
LL Mul(LL a,LL b,const LL mod)
{
	if(!a)return 0LL;
	LL ans=Mul(a>>1,b,mod);
	if((ans<<=1)>=mod)ans-=mod;
	if(a&1LL)
	{
		if((ans+=b)>=mod)ans-=mod;
	}
	return ans;
}
LL Pow(LL a,LL p,const LL mod)
{
	LL ans=1LL;
	for(;p;p>>=1)
	{
		if(p&1LL)ans=Mul(ans,a,mod);
		a=Mul(a,a,mod);
	}
	return ans;
}
bool PrimalityTest(const LL n,const LL a,const LL u,const int t)
{
	if(a<=1LL||a>=n-1LL)return true;
	LL x=Pow(a,u,n);
	if(x==1LL||x==n-1LL)return true;
	for(int i=0;i<t-1;i++)
	{
		x=Mul(x,x,n);
		if(x==1LL)return false;
		if(x==n-1LL)return true;
	}
	return false;
}
bool IsPrime(const LL n)
{
	assert(n>=2LL);
	if(n==2LL)return true;
	if(n%2LL==0LL)return false;
	LL u=n-1LL;
	int t=0;
	for(;u%2LL==0LL;u>>=1,++t);
	static LL data[7]={2,325,9375,28178,450775,9780504,1795265022};
	for(int i=0;i<7;i++)if(!PrimalityTest(n,data[i]%n,u,t))return false;
	return true;
}
bool IsSquare(const LL n)
{
	LL l=1LL,r=n;
	while(l<r)
	{
		const LL mid=(l+r)/2LL;
		if(mid<n/mid)l=mid+1;
		else r=mid;
	}
	return r*r==n;
}
void Update(const int k,int &ansk,int &ansd)
{
	if(k>ansk)ansk=k,ansd=0;
	if(k==ansk)++ansd;
}
void Update(LL n,const int k,int &ansk,int &ansd,const vector<LL>&p)
{
	for(int i=0;p[i]*p[i]*p[i]<=n;i++)
	{
		int cnt=0;
		for(;n%p[i]==0LL;n/=p[i],++cnt);
		Update(cnt*k,ansk,ansd);
	}
	if(n==1LL)return;
	if(IsSquare(n))Update(2*k,ansk,ansd);
	else if(IsPrime(n))Update(k,ansk,ansd);
	else Update(k,ansk,ansd),Update(k,ansk,ansd);
}
void MulBigIntegerByTwo(vector<int>&s)
{
	for(int i=0;i<(int)s.size();i++)s[i]<<=1;
	for(int i=0;i<(int)s.size();i++)if(s[i]>=10)
	{
		if(i+1==(int)s.size())s.push_back(0);
		s[i+1]+=s[i]/10;
		s[i]%=10;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	vector<LL>primes;
	BuildPrime(primes,1100000LL);
	for(int n;scanf("%d",&n)==1;)
	{
		map<LL,int>s;
		for(int i=0;i<n;i++)
		{
			LL v;scanf("%lld",&v);
			++s[v];
		}
		MakeCoprime(s);
		int ansk=1,ansd=0;
		for(map<LL,int>::iterator it=s.begin();it!=s.end();++it)Update(it->first,it->second,ansk,ansd,primes);
		vector<int>ansds;
		ansds.push_back(1);
		for(int i=0;i<ansd;i++)MulBigIntegerByTwo(ansds);
		assert((ansds[0]--)>0);
		printf("%d\n",ansk);
		for(int i=(int)ansds.size()-1;i>=0;i--)putchar('0'+ansds[i]);
		puts("");
	}
	return 0;
}

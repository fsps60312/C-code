#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
struct Bit
{
	int N;
	int S[300001];
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int val){for(;i<=N;i+=i&(-i))S[i]+=val;}
	LL Query(int i){int ans=0;for(;i;i-=i&(-i))ans+=S[i];return ans;}
}BIT;
LL MOD;
LL Pow(LL a,LL p)
{
	LL ans=1;
	for(;p;p>>=1)
	{
		if(p&1)(ans*=a)%=MOD;
		(a*=a)%=MOD;
	}
	return ans;
}
vector<int>P;
void BuildPrime()
{
	bool *isp=new bool[310001];
	for(int i=2;i<=310000;i++)isp[i]=true;
	for(int i=2;i<=310000;i++)
	{
		if(isp[i])P.push_back(i);
		for(int j=0;i*P[j]<=310000;j++)
		{
			isp[i*P[j]]=false;
			if(i%P[j]==0)break;
		}
	}
//	for(int i=0;i<100;i++)printf("%lld\n",P[i]);
}
vector<int>Factorize(int n)
{
	vector<int>ans;
	for(int i=2;i*i<=n;i++)if(n%i==0)
	{
		ans.push_back(i);
		while(n%i==0)n/=i;
	}
	if(n>1)ans.push_back(n);
	return ans;
}
void Exgcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0){assert(a==1);x=1,y=0;return;}
	Exgcd(b,a%b,y,x);//by+(a-a/b*b)x=1,b(y-a/b*x)+ax=1
	y-=a/b*x;
}
LL Inv(const LL v)
{
	static LL x,y;
	Exgcd(v,MOD,x,y);
	return (x+MOD)%MOD;
}
int N,S[300000],CNT[30];
void Mul(LL &val,int n,const vector<int>&f)
{
	for(int i=0;i<(int)f.size();i++)
	{
		while(n%f[i]==0)++CNT[i],n/=f[i];
	}
	(val*=n)%=MOD;
}
void Div(LL &val,int n,const vector<int>&f)
{
	for(int i=0;i<(int)f.size();i++)
	{
		while(n%f[i]==0)--CNT[i],n/=f[i];
	}
//	printf("n=%d,MOD=%lld,n^MOD=%lld\n",n,MOD,Pow(n,MOD+1));
	(val*=Inv(n))%=MOD;
}
vector<vector<LL> >DP;
int main()
{
//	freopen("in.txt","r",stdin);
	BuildPrime();
	while(scanf("%d%lld",&N,&MOD)==2)
	{
		const vector<int>factors=Factorize((int)MOD);
//		for(int i=0;i<(int)factors.size();i++)printf(" %d",factors[i]);puts("");
		DP.clear(),DP.resize(factors.size());
		for(int i=0;i<(int)factors.size();i++)
		{
			LL ans=1;
			for(int j=0;j<=N;j++,(ans*=factors[i])%=MOD)DP[i].push_back(ans);
		}
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		static int cnt[300001];
		BIT.Clear(300000);
		for(int i=1;i<=300000;i++)cnt[i]=0;
		for(int i=0;i<30;i++)CNT[i]=0;
		LL ans=0LL,val=1LL;
		for(int i=N-1,n=1;i>=0;i--,n++)
		{
			LL mul=BIT.Query(S[i]-1);
			Div(val,++cnt[S[i]],factors);
//			printf("mul=%lld, SEG.S[1]=%lld\n",mul,SEG.S[1]);
			for(int j=0;j<(int)factors.size();j++)(mul*=DP[j][CNT[j]])%=MOD;
			(ans+=val*mul)%=MOD;
			Mul(val,n,factors);
//			printf("mul %d, div %d, result=%lld\n",n,cnt[S[i]],mul);
			BIT.Add(S[i],1);
		}
		printf("%lld\n",(ans+1)%MOD);
	}
	return 0;
}

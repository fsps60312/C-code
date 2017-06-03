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
int PID[300001];
void BuildPrime()
{
	bool *isp=new bool[310001];
	for(int i=2;i<=310000;i++)isp[i]=true;
	for(int i=2;i<=310000;i++)
	{
		if(isp[i])P.push_back(i);
		for(int j=0;i*P[j]<=310000;j++)
		{
			PID[i*P[j]]=-P[j];
			isp[i*P[j]]=false;
			if(i%P[j]==0)break;
		}
	}
	for(int i=0;i<(int)P.size();i++)PID[P[i]]=i;
//	for(int i=0;i<100;i++)printf("%lld\n",P[i]);
}
struct SegTree
{
	int N;
	LL S[120000];
	int CNT[120000];
	void Build(const int id,const int l,const int r)
	{
		S[id]=1;
		CNT[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N){N=_N;Build(1,0,N);}
	void Add(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r)
		{
			S[id]=Pow(P[r],CNT[id]+=val);
			return;
		}
		const int mid=(l+r)/2;
		if(loc<=mid)Add(id*2,l,mid,loc,val);
		else Add(id*2+1,mid+1,r,loc,val);
		S[id]=S[id*2]*S[id*2+1]%MOD;
	}
	void Add(const vector<int>&s)
	{
		for(int i=0;i<(int)s.size();i++)Add(1,0,N,s[i],1);
	}
	void Sub(const vector<int>&s)
	{
		for(int i=0;i<(int)s.size();i++)Add(1,0,N,s[i],-1);
	}
}SEG;
vector<int>Factorize(int n)
{
	vector<int>ans;
	for(;n>1;)
	{
		const int p=PID[n];
		if(p>=0){ans.push_back(p);break;}
		else ans.push_back(PID[-p]),n/=-p;
	}
	for(int i=0;i<(int)ans.size();i++)assert(ans[i]>=0);
//	printf("n=%d, factor =",n);
//	for(int i=0;i<(int)ans.size();i++)printf(" %d",P[ans[i]]);puts("");
	return ans;
}
int N,S[300000];
int main()
{
//	freopen("in.txt","r",stdin);
	BuildPrime();
	const int M=(int)P.size();
	while(scanf("%d%lld",&N,&MOD)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		static int cnt[300001];
		BIT.Clear(300000);
		for(int i=1;i<=N;i++)cnt[i]=0;
		SEG.Build(M-1);
		LL ans=0LL;
		for(int i=N-1,n=1;i>=0;i--,n++)
		{
			const LL mul=BIT.Query(S[i]-1);
			SEG.Sub(Factorize(++cnt[S[i]]));
//			printf("mul=%lld, SEG.S[1]=%lld\n",mul,SEG.S[1]);
			(ans+=mul*SEG.S[1])%=MOD;
			SEG.Add(Factorize(n));
//			printf("mul %d, div %d, result=%lld\n",n,cnt[S[i]],SEG.S[1]);
			BIT.Add(S[i],1);
		}
		printf("%lld\n",(ans+1)%MOD);
	}
	return 0;
}

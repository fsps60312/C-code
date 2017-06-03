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
	void Add(const int id,const int l,const int r,const int loc,const int val)
	{
		if(l==r)
		{
			S[id]=Pow(P[r],CNT[id]+=val);
			return;
		}
		const int mid=(l+r)/2;
		Add(id*2,l,mid,loc,val);
		Add(id*2+1,mid+1,r,loc,val);
		S[id]=S[id*2]*S[id*2+1]%MOD;
	}
//	int QueryCnt(const int id,const int l,const int r,const int loc)
//	{
//		if(l==r)return CNT[id];
//		const int mid=(l+r)/2;
//		return loc<=mid?QueryCnt(id*2,l,mid,loc):QueryCnt(id*2+1,mid+1,r,loc);
//	}
}SEG;
int N,S[300000];
int main()
{
	BuildPrime();
	const int M=(int)P.size();
	freopen("in.txt","r",stdin);
	while(scanf("%d%lld",&N,&MOD)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		static int cnt[300001];
		BIT.Clear(N);
		for(int i=1;i<=N;i++)cnt[i]=0;
		SEG.Build(1,0,M-1);
		LL ans=0LL; 
		for(int i=N-1,n=1;i>=0;i--,n++)
		{
			const LL mul=BIT.Query(S[i]-1);
			(ans+=mul*SEG.S[1])%=MOD;
			SEG.Add(Factorize(n));
			SEG.Sub(Factorize(++cnt[S[i]]));
			BIT.Add(S[i],1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

#include<cstdio>
typedef long long LL;
const LL MOD=1000000007LL;
int N;
LL S[250000],DP[250000];
int DEP[250000];
struct Bit
{
	LL s[250001];
	void clear(){for(int i=1;i<=N;i++)s[i]=0LL;}
	int lowbit(const int &i){return i&(-i);}
	void Add(int i,const LL &v){while(i<=N){s[i]+=v,s[i]%=MOD;i+=lowbit(i);}}
	LL Query(int i){LL ans=0LL;while(i){ans+=s[i],ans%=MOD;i-=lowbit(i);}return ans;}
}BIT;
LL Solve()
{
	int ans=0;
	for(int i=0;i<N;i++)
	{
		int l=0,r=ans,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(DP[mid]<S[i])l=mid+1;
			else r=mid;
		}
		DP[l]=S[i];
		DEP[i]=l+1;
		if(l==ans)ans++;
	}
	BIT.clear();
	for(int i=0;i<N;i++)
	{
		if(DEP[i]==1LL){BIT.Add(1,1LL);continue;}
		static LL v;v=((BIT.Query(DEP[i]-1)-BIT.Query(DEP[i]-2))%MOD+MOD)%MOD;
//		printf("%d:%lld\n",i,v);
		BIT.Add(DEP[i],v);
	}
	return ((BIT.Query(ans)-BIT.Query(ans-1))%MOD+MOD)%MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		printf("%lld\n",Solve());
	}
	return 0;
}

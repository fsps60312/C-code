#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
const int MAX_N=100000;
const LL MOD=900720143;
namespace Sparse
{
	int S[17][MAX_N],B[MAX_N+1],N;
	void Build(const int n,const int *s)
	{
		N=n;
		for(int i=0;i<N;i++)S[0][i]=s[i];
		for(int b=1;b<=16;b++)
		{
			for(int i=0;i+(1<<b)<=N;i++)S[b][i]=max(S[b-1][i],S[b-1][i+(1<<(b-1))]);
		}
		for(int b=0,i=1;i<=N;i++)
		{
			while((1<<(b+1))<=i)++b;
			B[i]=b;
		}
	}
	int Get(const int l,const int r)
	{
		assert(0<=l&&l<=r&&r<N);
		const int b=B[r-l+1];
		return max(S[b][l],S[b][r-(1<<b)+1]);
	}
	void SpBuild(const int n,const int *s)
	{
		map<int,int>pre;
		static int t[MAX_N];
		for(int i=0;i<n;i++)
		{
			t[i]=pre[s[i]]-1;
			pre[s[i]]=i+1;
		}
		Build(n,t);
	}
	int SpGet(const int i)
	{
		int l=0,r=i;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Get(mid,i)>=mid)l=mid+1;
			else r=mid;
		}
		return r;
	}
};
struct Bit
{
	int N;
	LL S[MAX_N+1];
	void clear(const int n)
	{
		N=n;
		for(int i=1;i<=N;i++)S[i]=0;
	}
	void Add(int i,const LL v)
	{
		for(++i;i<=N;i+=i&(-i))(S[i]+=v)%=MOD;
	}
	LL Get(int i)
	{
		LL ans=0;
		for(++i;i;i-=i&(-i))(ans+=S[i])%=MOD;
		return ans;
	}
	LL Sum(const int l,const int r)
	{
		return ((Get(r)-Get(l-1))%MOD+MOD)%MOD;
	}
}B[2];
int N,K,S[MAX_N],L[MAX_N];
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);for(int i=-1;i<=1000;i++)printf("%d\n",i);return 0;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		Sparse::SpBuild(N,S);
		for(int i=0;i<N;i++)L[i]=Sparse::SpGet(i);
		B[0].clear(N+1);
		B[0].Add(0,1);
		int d=0;
		for(;K--;d^=1)
		{
			B[d^1].clear(N+1);
			for(int i=0;i<N;i++)
			{
				B[d^1].Add(i+1,B[d].Sum(L[i],i));
			}
		}
		printf("%lld\n",B[d].Sum(N,N));
	}
	return 0;
}

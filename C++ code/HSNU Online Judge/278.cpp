#include<cstdio>
#include<algorithm>
#include<cassert> 
using namespace std;
typedef long long LL;
int N;
LL P;
LL MinRank(const LL u)
{
	LL l=u,r=(1LL<<N)-1LL-u;
	LL ans=0LL;
	for(int i=N-1;i>=0;i--)
	{
		if(r>0LL)
		{
			r--;
			const LL sum=1LL+l+r;
			l/=2LL,r/=2LL;
			if(l+r<sum/2LL)l++;
		}
		else
		{
			assert(l>0LL);
			ans+=1LL<<i;
			l--;
			l/=2LL;
		}
		assert(1LL+l+r==(1LL<<i));
	}
	assert(l==0LL&&r==0LL);
	return ans+1LL;
}
LL MaxRank(const LL u)
{
	LL l=u,r=(1LL<<N)-1LL-u;
	LL ans=0LL;
	for(int i=N-1;i>=0;i--)
	{
		if(l>0LL)
		{
			ans+=1LL<<i;
			l--;
			const LL sum=1LL+l+r;
			l/=2LL,r/=2LL;
			if(l+r<sum/2LL)r++;
		}
		else
		{
			assert(r>0LL);
			r--;
			r/=2LL;
		}
		assert(1LL+l+r==(1LL<<i));
	}
	assert(l==0LL&&r==0LL);
	return ans+1LL;
}
LL WeakWinner()
{
	LL l=0LL,r=(1LL<<N)-1LL;
	while(l<r)
	{
		const LL mid=(l+r+1LL)/2LL;
		if(MinRank(mid)<=P)l=mid;
		else r=mid-1LL;
	}
	return r;
}
LL StrongLoser()
{
	LL l=0LL,r=(1LL<<N);
	while(l<r)
	{
		const LL mid=(l+r)/2LL;
		if(MaxRank(mid)<=P)l=mid+1LL;
		else r=mid;
	}
	return r;
}
int main()
{
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%lld",&N,&P);
		printf("%lld %lld\n",StrongLoser()-1LL,WeakWinner());
	}
	return 0;
}

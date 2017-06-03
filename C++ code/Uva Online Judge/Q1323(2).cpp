#include<cstdio>
#include<vector>
#include<set>
#include<cassert>
using namespace std;
int K,ANS[100];
struct Pair
{
	int p,e;
	Pair(){}
	Pair(const int _p,const int _e):p(_p),e(_e){}
};
vector<Pair>MERSENNE;
//if and only if N is multiplication of distinct Mersenne Primes
//Sum of factor of N is 2^n-1
set<int>DP;
int GetMPrime(int n)
{
	int ans=0;
	for(int i=0;i<MERSENNE.size();i++)
	{
		const Pair &m=MERSENNE[i];
		int cnt=0;
		while(n%m.p==0)n/=m.p,cnt++;
		if(cnt==1)ans|=(1<<i);
		else if(cnt>1)return -1;
	}
	if(n>1)return -1;
	return ans;
}
int main()
{
	MERSENNE.push_back(Pair(3,2));
	MERSENNE.push_back(Pair(7,3));
	MERSENNE.push_back(Pair(31,5));
	MERSENNE.push_back(Pair(127,7));
	MERSENNE.push_back(Pair(8191,13));
	MERSENNE.push_back(Pair(131071,17));
	MERSENNE.push_back(Pair(524287,19));
	MERSENNE.push_back(Pair(2147483647,31));
	while(scanf("%d",&K)==1)
	{
		DP.clear();
		DP.insert(0);
		for(int i=0,n;i<K;i++)
		{
			scanf("%d",&n);
			int s=GetMPrime(n);
			if(s!=-1)
			{
				vector<int>toadd;
				for(const auto v:DP)if(!(v&s))toadd.push_back(v|s);
				for(const auto v:toadd)DP.insert(v);
			}
		}
		int ans=-1;
		for(const int v:DP)
		{
			int ta=0;
			for(int i=0;i<MERSENNE.size();i++)if(v&(1<<i))ta+=MERSENNE[i].e;
			if(ta>ans)ans=ta;
		}
		assert(ans!=-1);
		if(ans==0)puts("NO");
		else printf("%d\n",ans);
	}
	return 0;
}

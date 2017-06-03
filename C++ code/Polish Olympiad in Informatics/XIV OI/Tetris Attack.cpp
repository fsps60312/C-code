#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
struct Bit
{
	int S[100001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i){for(i=N-i;i<=N;i+=i&(-i))++S[i];}
	int Query(int i){int ans=0;for(i=N-i;i;i-=i&(-i))ans+=S[i];return ans;}
}BIT;
int N,S[100000],LOC[100000];
multimap<int,int>Q;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N*2;i++)scanf("%d",&S[i]),--S[i];
		for(int i=0;i<N*2;i++)LOC[S[i]]=i;
		Q.clear();
		for(int i=0;i<N*2;i++)if(i<LOC[S[i]])Q.insert(make_pair(i,LOC[S[i]]));
		BIT.Clear(N*2);
		int cur=N*2;
		long long ans=0;
		for(multimap<int,int>::const_reverse_iterator it=Q.rbegin();it!=Q.rend();++it)
		{
			for(;cur>it->first;--cur)if(cur<LOC[S[cur]])BIT.Add(LOC[S[cur]]);
			ans+=BIT.Query(it->second+1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

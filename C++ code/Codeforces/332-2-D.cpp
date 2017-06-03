#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
//N*M+(N-1)*(M-1)+(N-2)*(M-2)...+(N-(N-1))*(M-(N-1))
//=N*N*M+((N-1)*N*(2N-1)/6)-(N*(N-1)/2)*(N+M)
//=N*N*M+(NN-N)(2N-1)/6-(NN-N)*(N+M)/2
//=N*N*M+(NN-N)((2N-1)/6-3(N+M)/6)
//=NNM+(NN-N)(-N-3M-1)/6
//=NNM+(-NNN-3NNM-NN+NN+3NM+N)/6
//=(-NNN+3NNM+3NM+N)/6
//=N(-NN+3NM+3M+1)/6
//6X=-NNN+3NNM+3NM+N
//3NNM+3NM=6X+NNN-N
//M=(6X+NNN-N)/(3NN+3N)
//=(6X/N+NN-1)/(3N+3)
//=(2X/N+(NN-1)/3)/(N+1)
//=2X/N/(N+1)+(N-1)/3
LL Function(const LL &n,const LL &m){return n*(-n*n+3LL*n*m+3LL*m+1LL)/6LL;}
LL X;
struct Pair
{
	LL n,m;
	Pair(){}
	Pair(const LL &_n,const LL &_m):n(_n),m(_m){}
	bool operator<(const Pair &p)const{return n!=p.n?n<p.n:m<p.m;}
	bool operator==(const Pair &p)const{return n==p.n&&m==p.m;}
};
int main()
{
	while(scanf("%I64d",&X)==1)
	{
		vector<Pair>ans;
		for(LL n=1LL,m;(m=(6LL*X+n*n*n-n)/(3LL*n*n+3LL*n))>=n;n++)if((6LL*X+n*n*n-n)%(3LL*n*n+3LL*n)==0LL)
		{
			ans.push_back(Pair(n,m)),ans.push_back(Pair(m,n));
		}
		sort(ans.begin(),ans.end());
		ans.resize(unique(ans.begin(),ans.end())-ans.begin());
		printf("%d\n",ans.size());
		for(int i=0;i<ans.size();i++)
		{
			printf("%I64d %I64d\n",ans[i].n,ans[i].m);
		}
	}
	return 0;
}

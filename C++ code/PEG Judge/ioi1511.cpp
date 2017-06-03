#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
int N,K,L;
int *S;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&K,&L);
	S=new int[N+1];
	S[0]=-1;
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&S[i]);
		if(S[i]==0)i--,N--;
		else assert(S[i]<L&&S[i-1]<=S[i]);
	}
	K=min(K,N);
	LL *left=new LL[N+1],*right=new LL[N+1];
	left[0]=right[0]=0LL;
	for(int i=1;i<=N;i++)
	{
		left[i]=left[max(i-K,0)]+2LL*S[i];
		right[i]=right[max(i-K,0)]+2LL*(L-S[N+1-i]);
	}
	LL ans=INF;
	for(int i=0;i<=N;i++)
	{
		const LL &ta=left[i]+right[N-i];
		if(ta<ans)ans=ta;
	}
	for(int i=1;i+K-1<=N;i++)
	{
		const LL &ta=L+left[i-1]+right[N+1-(i+K)];
		if(ta<ans)ans=ta;
	}
	printf("%lld\n",ans);
	delete[]left;
	delete[]right;
	return 0;
}

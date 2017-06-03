#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int N,Z[499999];
char S[500001];
LL Solve()
{
	if(N==1)return 0LL;
	assert(N>=2);
	Z[0]=(S[0]!=S[1]?1:0);
	for(int i=1,mx=0;i+1<N;i++)
	{
		if(mx+1+Z[mx]-1>=i+1)Z[i]=min((mx+1+Z[mx]-1)-(i+1)+1,Z[mx-(i-mx)]);
		else Z[i]=0;
		while(i-Z[i]>=0&&i+1+Z[i]<N&&S[i-Z[i]]!=S[i+1+Z[i]])++Z[i];
		if(i+Z[i]>=mx+Z[mx])mx=i;
	}
	LL ans=0LL;
	for(int i=0;i+1<N;i++)ans+=Z[i];//,printf("Z[%d]=%d\n",i,Z[i]);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&N,S)==2)
	{
		printf("%lld\n",Solve());
	}
	return 0;
}

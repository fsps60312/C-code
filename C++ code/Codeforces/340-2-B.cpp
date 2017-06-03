#include<cstdio>
typedef long long LL;
int N,S[100];
LL Solve()
{
	bool allzero=true;
	for(int i=0;i<N;i++)if(S[i]==1){allzero=false;break;}
	if(allzero)return 0LL;
	int l,r;
	for(r=N-1;S[r]==0;r--);
	for(l=0;S[l]==0;l++);
	LL ans=1LL;
	for(int i=l+1,cnt=1;i<=r;i++)
	{
		if(S[i]==0)cnt++;
		else ans*=cnt,cnt=1;
	}
	return ans;
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		printf("%I64d\n",Solve());
	}
	return 0;
}

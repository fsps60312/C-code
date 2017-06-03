#include<cstdio>
int N,K,S[100000];
int main()
{
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	long long ans=0LL;
	for(int l=0,r=-1,sum=0;l<N;l++)
	{
		while(r+1<N&&sum+S[r+1]<=K)sum+=S[++r];
		ans+=N-1-r;
		sum-=S[l];
	}
	printf("%lld\n",ans);
	return 0;
}

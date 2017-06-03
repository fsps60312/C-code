#include<cstdio>
#include<cstdlib>
int T,n,S[1000];
int solve()
{
	if(n<=2) return n;
	int ans=2;
	int now=S[0];
	for(int i=2;i<n;i++)
	{
		if(now+S[i-1]<S[i])
		{
			now+=S[i-1];
			ans++;
		}
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",&S[i]);
		printf("%d\n",solve());
	}
	return 0;
}

#include<cstdio>
int T,N,S[100];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		int mn=100000;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i]);
			if(S[i]<mn)mn=S[i];
		}
		int ans=0;
		for(int i=0;i<N;i++)ans+=S[i]-mn;
		printf("%d\n",ans);
	}
	return 0;
}

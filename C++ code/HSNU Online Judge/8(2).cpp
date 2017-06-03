#include<cstdio>
int N,S[300000];
int main()
{
	while(scanf("%d",&N)==1)
	{
		int ans;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i]);
			if(S[i]==N)
			{
				ans=N;
				for(int j=N,k=i;;j--)
				{
					while(k>=0&&S[k]!=j)k--;
					if(k==-1)break;
					ans--;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

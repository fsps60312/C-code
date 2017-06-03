#include<cstdio>
#include<cstdlib>
int T,n,ans;
char S[2001];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",&S);
		n=-1;
		while(S[++n]);
		ans=0;
		for(int i=1;i<n;i++)
		{
			bool isans=false;
			for(int j=0;j<n;j++)
			{
				if(S[(i+j)%n]<S[(ans+j)%n])
				{
					isans=true;
					break;
				}
				else if(S[(i+j)%n]>S[(ans+j)%n]) break;
			}
			if(isans) ans=i;
		}
		printf("%d\n",ans);
	}
	return 0;
}

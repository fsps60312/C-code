#include<cstdio>
#include<cstdlib>
int T,n,ans[10];
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<=9;i++) ans[i]=0;
		for(int i=1,j;i<=n;i++)
		{
			j=i;
			while(j)
			{
				ans[j%10]++;
				j/=10;
			}
		}
		/*int now=1;
		while(n)
		{
			int a=n%10;
			n/=10;
			for(int i=1;i<=a;i++) ans[i]+=now;
			for(int i=0;i<=9;i++) ans[i]+=n*now;
			int b=n;
			while(b)
			{
				ans[b%10]+=a;
				b/=10;
			}
			now*=10;
		}*/
		printf("%d",ans[0]);
		for(int i=1;i<=9;i++) printf(" %d",ans[i]);printf("\n");
	}
	return 0;
}

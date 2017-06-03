#include<cstdio>
#include<cstdlib>
int T,a,b;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&a,&b);
		if(b%a==0) printf("%d %d\n",a,b);
		else printf("-1\n");
	}
}

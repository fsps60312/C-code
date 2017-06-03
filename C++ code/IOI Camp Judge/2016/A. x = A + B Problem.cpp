#include<cstdio>
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int a;scanf("%d",&a);
		printf("%d %d\n",a/2,a-a/2);
	}
	return 0;
}

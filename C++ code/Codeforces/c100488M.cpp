#include<cstdio>
int A,B;
int main()
{
	while(scanf("%d%d",&A,&B)==2)
	{
		printf("%d\n",A*B);
		for(int i=0;i<A;i++)for(int j=B-1;j>=0;j--)
		{
			if(i!=0||j!=B-1)putchar(' ');
			printf("%d",i*B+j+1);
		}
		puts("");
	}
	return 0;
}

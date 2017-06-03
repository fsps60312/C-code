#include<cstdio>
#include<cstdlib>
int a,b,T;
int main()
{
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		scanf("%d%d",&a,&b);
		printf("Case #%d: ",t);
		if(a>b)
		{
			int c=a;
			a=b;
			b=c;
		}
		if(a==1)
		{
			printf("Bob\n");
		}
		else if(a==2)
		{
			switch(b%4)
			{
				case 0:
					printf("Draw\n");
					break;
				case 1:
					printf("Bob\n");
					break;
				case 2:
				default:
					printf("Ana\n");
					break;
				
			}
		}
		else if(a%2||b%2) printf("Bob\n");
		else if(a*b/4%2) printf("Ana\n");
		else printf("Draw\n");
	}
	return 0;
}

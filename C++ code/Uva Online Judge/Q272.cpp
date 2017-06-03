#include<cstdio>
#include<cstdlib>
int main()
{
	//freopen("in.txt","r",stdin);
	int n=1;
	char c;
	while(scanf("%c",&c)==1)
	{
		if(c=='"')
		{
			if(n%2) printf("``");
			else printf("''");
			n++;
		}
		else printf("%c",c);
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
char S1[4],S2[2],S3[4];
int T,n;
void dfsprint(int a,int b)
{
	if(b==13) return;
	dfsprint(a/2,b+1);
	printf("%d",a%2);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s%s",S1,S2,S3);
		n=-1;
		int a=0,b=0;
		while(S1[++n])
		{
			a*=16;
			if(S1[n]<='9') a+=S1[n]-'0';
			else a+=S1[n]-'A'+10;
		}
		n=-1;
		while(S3[++n])
		{
			b*=16;
			if(S3[n]<='9') b+=S3[n]-'0';
			else b+=S3[n]-'A'+10;
		}
		dfsprint(a,0);
		printf(" %s ",S2);
		dfsprint(b,0);
		printf(" = ");
		if(S2[0]=='+') printf("%d\n",a+b);
		else printf("%d\n",a-b);
	}
	return 0;
} 

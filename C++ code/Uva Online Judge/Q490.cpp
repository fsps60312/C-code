#include<cstdio>
#include<cstdlib>
char S[101][101];
int n,m;
int main()
{
	//freopen("input.txt","r",stdin);
	for(int i=0;i<101;i++)
	{
		for(int j=0;j<101;j++)
		{
			S[i][j]=' ';
		}
	}
	int a=0,b=0;
	n=m=0;
	while(scanf("%c",&S[a][b])==1)
	{
		if(S[a][b]=='\n') S[a][b]=' ',a++,b=0;
		else
		{
			if(a>n) n=a;
			if(b>m) m=b;
			b++;
		}
	}
	for(int i=0;i<=m;i++)
	{
		for(int j=n;j>=0;j--) printf("%c",S[j][i]);
		printf("\n");
	}
	return 0;
}

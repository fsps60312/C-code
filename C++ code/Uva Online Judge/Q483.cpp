#include<cstdio>
#include<cstdlib>
char S[1000000],c;
int main()
{
	//freopen("input.txt","r",stdin);
	while(scanf("%s%c",S,&c)==2)
	{
		int n=-1;
		while(S[++n]);
		for(int i=n-1;i>=0;i--) printf("%c",S[i]);
		printf("%c",c);
	}
	return 0;
}

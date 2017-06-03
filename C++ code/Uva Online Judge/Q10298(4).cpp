#include<cstdio>
char LINE[1000001];
int N,F[1000001];
int buildF(char *s,int *f)
{
	int i;
	f[0]=f[1]=0;
	for(i=1;s[i];i++)
	{
		int u=f[i];
		while(u&&s[u]!=s[i])u=f[u];
		f[i+1]=s[u]==s[i]?++u:0;
	}
	return i;
}
int main()
{
	while(scanf("%s",LINE)==1)
	{
		N=buildF(LINE,F);
		printf("%d\n",N%(N-F[N])?1:N/(N-F[N]));
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
int T,n,now;
char S[100];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		n=0,now=0;
		for(int i=0;S[i];i++)
		{
			if(S[i]=='X')
			{
				now=0;
			}
			else
			{
				now++;
				n+=now;
			}
		}
		printf("%d\n",n);
	}
	return 0;
}

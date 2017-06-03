#include<cstdio>
#include<cstdlib>
int state=1,S[1000],n,now;
int* ptr;
char c;
int main()
{
	ptr=S;
	n=0;
	while(scanf("%d%c",ptr,&c)==2)
	{
		if(state%2)
		{
			if(c=='\n')
			{
				state++,ptr=&now;
				continue;
			}
			n++;
			ptr++;
		}
		else
		{
			int i,ans=0,power;
			for(i=n,power=1;i>=0;i--)
			{
				ans+=S[i]*power;
				power*=now;
			}
			printf("%d",ans);
			if(c!='\n') printf(" ");
			else
			{
				printf("\n");
				state++,n=0,ptr=S;
			}
		}
	}
	return 0;
} 

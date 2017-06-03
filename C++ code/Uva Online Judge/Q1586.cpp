#include<cstdio>
#include<cstdlib>
int T,ans,a,b;
char S[100];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		ans=0,a=0,b=0;
		for(int i=0;S[i];i++)
		{
			switch(S[i])
			{
				case'C':
					{
						ans+=a*(b==0?1:b);
						a=12010;
						b=0;
					}break;
				case'H':
					{
						ans+=a*(b==0?1:b);
						a=1008;
						b=0;
					}break;
				case'O':
					{
						ans+=a*(b==0?1:b);
						a=16000;
						b=0;
					}break;
				case'N':
					{
						ans+=a*(b==0?1:b);
						a=14010;
						b=0;
					}break;
				default:
					{
						b*=10;
						b+=S[i]-'0';
					}break;
			}
			//printf("%d.%d\n",ans/1000,ans%1000);
		}
		ans+=a*(b==0?1:b);
		printf("%d.%03d\n",ans/1000,ans%1000);
	}
	return 0;
}

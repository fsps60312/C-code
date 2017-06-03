#include<cstdio>
#include<cstdlib>
char S[]="=-0987654321`\][POIUYTREWQ';LKJHGFDSA/.,MNBVCXZ";
int main()
{
	char c;
	while(scanf("%c",&c)==1)
	{
		int i;
		for(i=0;S[i];i++)
		{
			if(S[i]==c)
			{
				printf("%c",S[i+1]);
				break;
			}
		}
		if(!S[i]) printf("%c",c);
	}
	return 0;
}

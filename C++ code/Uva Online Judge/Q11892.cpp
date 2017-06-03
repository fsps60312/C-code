#include<cstdio>
#include<cstdlib>
int T,n,j;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		bool hass=false;
		bool isdouble=true;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&j);
			if(j==1) isdouble^=1;
			else hass=true;
		}
		if(!hass&&isdouble)
		{
			printf("piloop\n");
		}
		else printf("poopi\n");
	}
	return 0;
}

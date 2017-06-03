#include<cstdio>
#include<cstdlib>
char S[102];
int main()
{
	while(scanf("%s",S)==1)
	{
		int n,survive=0,is0=0;
		for(n=1;S[n];n++)
		{
			if(S[n-1]=='0')
			{
				if(S[n]=='0') survive++;
				//else dead++;
				is0++;
			}
		}
		if(S[n-1]=='0')
		{
			if(S[0]=='0') survive++;
			//else dead++;
			is0++;
		}
		//shoot:survive/(survive+dead)==survive/is0
		//rotate:is0/n
		survive*=n;
		is0*=is0;
		if(survive<is0) printf("ROTATE\n");
		else if(survive>is0) printf("SHOOT\n");
		else printf("EQUAL\n");
	}
	return 0;
}

#include<cstdio>
int N;
int main()
{
	while(scanf("%d",&N)==1)
	{
		N%=5;
		switch(N)
		{
			case 0:puts("U");break;
			case 1:puts("G");break;
			case 2:puts("Y");break;
			case 3:puts("T");break;
			case 4:puts("I");break;
		}
	}
	return 0;
}

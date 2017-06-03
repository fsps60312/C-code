#include<cstdio>
int N;
char S[1000],L;
void solve()
{
	L=1;
	for(int _d=9,p=0,d;;L++)
	{
		d=_d-_d/10;
		if(N<=d)
		{
			N+=p;
			for(int i=(L-1)/2;i>=0;i--)
			{
				S[i]='0'+N%10;
				N/=10;
			}
			return;
		}
		N-=d;
		if(!(L&1))_d=_d*10+9,p=p*10+9;
	}
}
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		solve();
		for(int i=0;i<L;i++)printf("%c",S[i<L/2?i:L-1-i]);
		printf("\n");
	}
	return 0;
}

#include<cstdio>
int N;
int Solve()
{
	int x=2*N,y=-N;//3x+5y==N
	y+=x/5*3;
	x%=5;
	if(y<0)return -1;
	return x+y;
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		int ans=Solve();
		if(ans==-1)puts("This is Kongming's Trap!!!");
		else printf("%d\n",ans);
	}
	return 0;
}

#include<cstdio>
int T,A,B,N,M,MOD,VIS[100000000];
int solve()
{
	A%=MOD,B%=MOD;
	if(N<2)return N?B:A;
	for(int i=0;i<MOD*MOD;i++)VIS[i]=-1;
	for(int n=2,c;;n++)
	{
		c=(A+B)%MOD;
		int v=A*MOD+B;
		A=B,B=c;
//		printf("%d:%d\n",n,c);
		if(n==N)return c;
		if(VIS[v]!=-1)
		{
			int peri=n-VIS[v];
			n=(N-n)%peri+VIS[v];
			for(int i=0;i<MOD*MOD;i++)if(VIS[i]==n)return i;
		}
		else VIS[v]=n;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&A,&B,&N,&M);
		MOD=1;while(M--)MOD*=10;
		printf("%d\n",solve());
	}
	return 0;
}

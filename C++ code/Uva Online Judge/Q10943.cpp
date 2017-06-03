#include<cstdio>
#include<cstdlib>
long long N,K,C[202][202];
int main()
{
	//C[0][1]=0;
	//for(int i=0;i<102;i++) C[i][i]=C[i][0]=1;
	for(int i=1;i<202;i++)
	{
		C[i][0]=1;
		for(int j=1;j<i;j++)
		{
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			C[i][j]%=1000000;
		}
		C[i][i]=1; 
	}
	while(scanf("%lld%lld",&N,&K)==2)
	{
		//ans is H(N+1,K-1)==C(N+K-1,K-1);
		if(N==0&&K==0) break;
		printf("%lld\n",C[N+K-1][K-1]);
	}
	return 0;
}

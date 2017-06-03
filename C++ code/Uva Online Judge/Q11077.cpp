#include<cstdio>
#include<cstdlib>
unsigned long long C[22][22],level[22],n,k;
int main()
{
	level[0]=1;
	for(unsigned long long i=1;i<=21;i++)
	{
		level[i]=level[i-1]*i;
		printf("%llu %llu\n",i,level[i]);
		C[i][0]=1;
		C[i][i]=1;
	}
	for(unsigned long long i=2;i<=21;i++)
	{
		for(unsigned long long j=1;j<i;j++)
		{
			C[i][j]=C[i-1][j-1]+C[i-1][j];
		}
	}
	/*for(long long i=1;i<=10;i++)
	{
		for(long long j=0;j<=10;j++) printf("%llu ",C[i][j]);
		printf("\n");
	}*/
	//freopen("in.txt","r",stdin);
	while(scanf("%llu%llu",&n,&k)==2)
	{
		if(n==0&&k==0) break;
		unsigned long long ans;
		if(k==0) ans=1;
		//else if(k==1) ans=C[n][2];
		else//if k==1 n-2(n-k-1) element has already in the right place
		{
			//k+1 element are in the wrong place
			//(k+1 0)(k+1)!-(k+1 1)(k)!+(k+1 2)(k-1)!-......
			//x=2
			//2!*1-1!*2+0!*1=1
			//x=3
			//3!*1-2!*3+1!*3-0!*1=6-6+3-1=2
			ans=0;
			for(unsigned long long i=2;i<=k+1;i++)
			{
				if(i&1) ans-=C[k+1][i]*level[k+1-i];
				else ans+=C[k+1][i]*level[k+1-i];
			}
			ans*=C[n][k+1];
		}
		printf("%llu\n",ans);
	}
	return 0;
}

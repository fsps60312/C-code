#include<cstdio>
#define abs(x) (x>=0?x:-(x))
const int SecPerDay=60*60*12;
int K,M;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main()
{
	while(scanf("%d%d",&K,&M)==2)
	{
		printf("%d %d ",K,M);
		M=abs(K-M);//time displacement
		M=SecPerDay/gcd(SecPerDay,M);//rolls
		printf("%d rolls\n");
		K=K*M%SecPerDay;//time lose
		printf("lose %d\n",K);
		K=(SecPerDay-K)%SecPerDay;//time win
		if(K<=59)printf("12:%02d\n",K);
		else printf("%02d:%02d\n",K/60,K%60);
	}
	return 0;
}

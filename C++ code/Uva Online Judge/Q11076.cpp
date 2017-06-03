#include<cstdio>
#include<cstdlib>
unsigned long long tmp[13],level[13];
int n,digit[10];
unsigned long long ans;
int main()
{
	tmp[0]=0,level[0]=1;
	for(unsigned long long i=1,j=1;i<13;i++)
	{
		level[i]=level[i-1]*i;
		tmp[i]=tmp[i-1]+j;
		j*=10;
	}
	//printf("%lf\n",level[12]);
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&n)==1&&n)
	{
		if(n==0) break;
		for(int i=0;i<10;i++) digit[i]=0;
		ans=0;
		for(int i=0,j;i<n;i++)
		{
			scanf("%d",&j);
			ans+=j;
			digit[j]++;
		}
		//printf("%llu %llu %llu\n",(unsigned long long)(ans+0.5),tmp[n],level[n-1]);
		//printf("%llu %llu %llu\n",(unsigned long long)(ans+0.5),tmp[n],level[n-1]);
		ans*=level[n-1];
		//printf("%lf\n",ans+0.5);
		for(int i=0;i<10;i++)
		{
			ans/=level[digit[i]];
		}
		ans*=tmp[n];
		printf("%llu\n",ans);
	}
	return 0;
}

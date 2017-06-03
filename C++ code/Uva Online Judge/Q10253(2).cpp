#include<cstdio>
#include<cstdlib>
long long f[31];
long long n;
long long tmp[30];
long long C(long long a,long long b)//C(a+b-1,b);
{
	double ans=1;
	for(int i=0;i<b;i++) ans*=(a-i);
	for(int i=1;i<=b;i++) ans/=i;
	return (long long)(ans+0.5);
}
void addfromtmp(long long a,long long b)
{
	//printf("%lld\n",a);
	//for(int i=0;i<=b;i++) printf(" %lld",tmp[i]);printf("\n");
	long long now=1,ans=1;
	for(int i=1;i<=b;i++)
	{
		if(tmp[i]==tmp[i-1])
		{
			now++;
		}
		else
		{
			ans*=C(f[tmp[i-1]]+now-1,now);
			now=1;
		}
	}
	f[a]+=C(f[tmp[b]]+now-1,now)*ans;
	//printf(" %lld\n",f[a]);
}
void dfs(long long a,long long b,long long c,long long d)//site, rest, now, tmp site
{
	tmp[d]=b;
	addfromtmp(a,d);
	for(long long i=c;i<=b/2;i++)
	{
		tmp[d]=i;
		dfs(a,b-i,i,d+1);
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	/*long long aa,bb;
	while(scanf("%lld%lld",&aa,&bb)==2)
	{
		printf("%lld\n",H(aa,bb));
	}
	return 0;*/
	f[1]=1,f[2]=1;
	for(long long i=3;i<=30;i++)
	{
		f[i]=0;
		for(int j=1;j<=i/2;j++)
		{
			tmp[0]=j;
			dfs(i,i-j,j,1);//site, rest, now, tmp site
		}
		//printf("  %lld\n",f[i]);
	}
	while(scanf("%lld",&n)==1)
	{
		if(n==0) break;
		printf("%lld\n",n==1?1:f[n]*2);
	}
	return 0;
}

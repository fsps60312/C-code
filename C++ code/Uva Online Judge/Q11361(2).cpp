#include<cstdio>
#include<cstdlib>
long long T,A,B,K,digit[11],tmp[11][100][10000];
long long mod(long long a)
{
	a%=K;
	return a>=0?a:a+K;
}
long long state(long long a,long long b,long long c)
{
	if(a==0) return b==0&&c==0?1:0;
	if(tmp[a][b][c]!=-1) return tmp[a][b][c];
	long long ans=0;
	for(int i=0;i<=9;i++)
	{
		ans+=state(a-1,mod(b-i),mod(c-i*digit[a]));
	}
	return tmp[a][b][c]=ans;
}
long long serch(long long a,long long b,long long c,long long d)
{
	//printf("%lld %lld %lld %lld\n",a,b,c,d);
	if(a==0||b==1) return 0;
	long long ans=0,e=0;
	for(int i=0;i<=9;i++)
	{
		if((i+1)*digit[b]-1>a)
		{
			e=i;
			break;
		}
		ans+=state(b-1,mod(c-i),mod(d-i*digit[b]));
	}
	ans+=serch(a-e*digit[b],b-1,mod(c-e),mod(d-e*digit[b]));
	return ans;
}
int main()
{
	/*K=11;
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<100;j++)
		{
			for(int k=0;k<K;k++) tmp[i][j][k]=-1;
		}
	}
	printf("%lld %lld %lld\n",state(1,0,0),state(2,0,0),state(3,0,0));
	freopen("in.txt","r",stdin);*/
	digit[1]=1;
	for(int i=2;i<11;i++) digit[i]=digit[i-1]*10;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&A,&B,&K);
		for(int i=0;i<11;i++)
		{
			for(int j=0;j<100;j++)
			{
				for(int k=0;k<K;k++) tmp[i][j][k]=-1;
			}
		}
		long long ans=serch(B,10,0,0)-serch(A-1,10,0,0);
		printf("%lld\n",ans);
	}
	return 0;
}

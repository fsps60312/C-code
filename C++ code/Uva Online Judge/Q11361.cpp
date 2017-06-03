#include<cstdio>
#include<cstdlib>
long long T,A,B,K;
long long tmp[11][100][10000];//digits, digit sum's mod, num's mod
long long digit[12];
long long mod(long long a)
{
	a%=K;
	return a>=0?a:a+K;
}
long long countmod(long long a)
{
	long long ans=0;
	for(int i=11;i>=1;i--)
	{
		ans+=a/digit[i];
		a%=digit[i];
	}
	return mod(ans);
}
long long state(long long a,long long b,long long c)//digits, digits sum's mod, sum's mod
{
	if(a==1) return b==c?1:0;
	if(tmp[a][b][c]!=-1) return tmp[a][b][c];
	long long ans=0;
	for(int i=0;i<=9;i++)
	{
		ans+=state(a-1,mod(b-i),mod(c-i*digit[a]));
	}
	return tmp[a][b][c]=ans;
}
long long serch(long long a,long long b,long long c)
{
	printf("%lld %lld %lld\n",a,b,c);
	long long ans=0;
	if(c==1)
	{
		for(long long i=a;i<=b;i++)
		{
			if(countmod(i)==0&&mod(i)==0) ans++;
		}
		return ans;
	}
	long long bas=a/digit[c+1]*digit[c+1];
	long long d=countmod(bas);
	long long e=mod(bas);
	long long Min=11,Max=-1;
	for(int i=0;i<=9;i++)
	{
		if(bas+i*digit[c]>=a&&bas+(i+1)*digit[c]-1<=b)
		{
			if(i<Min) Min=i;
			if(i+1>Max) Max=i+1;
			//printf(" %lld %lld %lld %lld\n",mod(d+i),mod(e+i*digit[c]),state(c-1,mod(d+i),mod(e+i*digit[c])));
			ans+=state(c,mod(d+i),mod(e+i*digit[c]));
		}
	}
	if(Min==11&&Max==-1) return serch(a,b,c-1);
	//printf(" %lld\n",ans);
	ans+=serch(a,Min*digit[c]-1,c-1);
	//printf(" %lld\n",ans);
	ans+=serch(Max*digit[c],b,c-1);
	//printf(" %lld\n",ans);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	digit[1]=1;
	for(int i=2;i<12;i++) digit[i]=digit[i-1]*10;
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
        long long ans=serch(A,B,10);
        printf("%lld\n",ans);
    }
    return 0;
}

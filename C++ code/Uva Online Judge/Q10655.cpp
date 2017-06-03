#include<cstdio>
#include<cstdlib>
typedef long long LL;
LL qpow[100],p,q,n,pow2[100];//q^(2^i)
struct pairtype
{
	LL x,y;
};
pairtype quadsum[100];//a^(2^i)+b^(2^i)
LL questqpow(LL a)
{
	LL ans=1;
	for(int i=0;i<32;i++)
	{
		if(a&(1LL<<i))
		{
			ans*=qpow[i];
		}
	}
	return ans;
}
LL pow(LL a)
{
	pairtype ans;
	ans.y=0,ans.x=2;//a^0+b^0
	for(int j=0;j<32;j++)
	{
		if(a&(1LL<<j))
		{
			ans.x=quadsum[j].x,ans.y=quadsum[j].y;
			for(int i=j+1;i<32;i++)
			{
				if(a&(1LL<<i))
				{
	LL c=ans.x*quadsum[i].x;//(a^i+b^i)(a^j+b^j)=ans+a^j*b^i+a^i*b^j=ans+q^d(a^e+b^e)
	LL d=ans.y<quadsum[i].y?ans.y:quadsum[i].y;
	LL e=ans.y<quadsum[i].y?quadsum[i].y-ans.y:ans.y-quadsum[i].y;
	c-=questqpow(d)*pow(e);
	ans.x=c,ans.y=ans.y+quadsum[i].y;
				}
			}
			break;
		}
	}
	//printf("%lld:%lld %lld\n",a,ans.x,ans.y);
	return ans.x;
}
char S[10000];
bool isnum(char a)
{
	return a>='0'&&a<='9';
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	pow2[0]=1;
	for(int i=1;i<100;i++) pow2[i]=pow2[i-1]<<1;
	while(gets(S))
	{
		int a=0;
		while(S[a]&&!isnum(S[a])) a++;
		p=0;
		while(S[a]&&isnum(S[a]))
		{
			p*=10;
			p+=S[a]-'0';
			a++;
		}
		while(S[a]&&!isnum(S[a])) a++;
		q=0;
		while(S[a]&&isnum(S[a]))
		{
			q*=10;
			q+=S[a]-'0';
			a++;
		}
		while(S[a]&&!isnum(S[a])) a++;
		if(!S[a]) break;
		n=0;
		while(S[a]&&isnum(S[a]))
		{
			n*=10;
			n+=S[a]-'0';
			a++;
		}
		qpow[0]=q;
		for(int i=1;i<100;i++) qpow[i]=qpow[i-1]*qpow[i-1];
		quadsum[0].x=p;//a+b
		quadsum[0].y=1;
		for(int i=1;i<100;i++)
		{
			quadsum[i].x=quadsum[i-1].x*quadsum[i-1].x-2*qpow[i-1];//a^2+2ab+b^2
			quadsum[i].y=quadsum[i-1].y<<1;
		}
		//printf("%lld %lld pass\n",quadsum[1].x,quadsum[2].x);
		printf("%lld\n",pow(n));
	}
	return 0;
}

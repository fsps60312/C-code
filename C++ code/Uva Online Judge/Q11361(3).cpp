#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;
struct pairtype
{
	int a;
	int b;
	int c;
	bool operator()(pairtype a,pairtype b)
	{
		if(a.a!=b.a) return a.a<b.a;
		if(a.b!=b.b) return a.b<b.b;
		return a.c<b.c;
	}
};
map<pairtype,long long,pairtype> tmp;
long long T,A,B,K;
long long digit[11];
long long mod(long long a)
{
	a%=K;
	return a>=0?a:a+K;
}
long long state(long long a,long long b,long long c)//a stars, digit sum mod is b, mod is c
{
	if(a==0) return b==0&&b==c?1:0;
	pairtype d;
	d.a=a;
	d.b=b;
	d.c=c;
	if(tmp.find(d)!=tmp.end()) return tmp[d];
	long long ans=0;
	for(long long i=0;i<=9;i++)
	{
		ans+=state(a-1,mod(b-i),mod(c-i*digit[a]));
	}
	return tmp[d]=ans;
}
long long query(long long a)
{
	a++;
	long long mod1=0,mod2=0,ans=0;
	for(long long i=10;i>=1;i--)//1234 -> 234 -> 34 -> 4
	{//i==4, j==1
		long long j=a/digit[i];//summarize digit i
		//0***
		//10**+11**
		//120*+121*+122*
		//1234
		for(long long k=0;k<j;k++)//(i==4) k==1 -> 0000~0999, k==2 -> 1000~1999, ......
		{
			ans+=state(i-1,mod(mod1-k),mod(mod2-k*digit[i]));
			//printf(" %lld %lld state(%lld, %lld, %lld)==%lld\n",k,digit[i],i-1,mod(mod1-k),mod(mod2-k*digit[i]),state(i-1,mod(mod1-k),mod(mod2-k*digit[i])));
		}
		mod1=mod(mod1-(j));
		mod2=mod(mod2-(j)*digit[i]);
		a%=digit[i];
	}
	return ans;
}
/*void testmode()
{
	while(scanf("%lld",&K)==1)
	{
		for(long long i=0;i<11;i++)
		{
			for(long long j=0;j<100;j++)
			{
				for(long long k=0;k<K;k++)
				{
					tmp[i][j][k]=-1;
				}
			}
		}
		long long C,D,E;
		while(scanf("%lld%lld%lld",&C,&D,&E)==3)
		{
			printf("%lld\n",state(C,D,E));
		}
		printf("Please enter K:\n");
		char cc[1000];
		scanf("%s",cc);
	}
}*/
int main()
{
	//testmode();
	//freopen("in.txt","r",stdin);
	digit[1]=1;
	for(long long i=2;i<11;i++) digit[i]=digit[i-1]*10;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&A,&B,&K);
		/*for(long long i=0;i<11;i++)
		{
			for(long long j=0;j<K;j++)
			{
				for(long long k=0;k<K;k++)
				{
					tmp[i][j][k]=-1;
				}
			}
		}*/
		tmp.clear();
		long long ans=query(B)-query(A-1);
		printf("%lld\n",ans); 
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
/*struct pairtype
{
	long long x;
	long long y;
};*/
long long T,x,k;
//pairtype tmp;
/*pairtype dfs(long long a,long long b,pairtype c,pairtype d)//a==c.x*flo+c.y*cei, so is b&d
{
	if(b==0) return 
}*/
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&x,&k);
		//flo=cei=x/k;
		if(x%k)//cei-flo==1
		{
			/*if((x<0)^(k<0))
			{
				flo--;
			}
			else
			{
				cei++;
			}
			//cei-flo==1
			//x*cei-x*flo==x
			flo*=-1;*/
			printf("%lld %lld\n",-x,x);
		}
		else//flo*k==x
		{
			printf("0 %lld\n",k);
		}
		//find p*flo+q*cei==x
		//tmp=gcd(flo,cei);
		//tmp.x*flo+tmp.y*cei==1
		//p==x*tmp.x, q==x*tmp.y
		//printf("%lld %lld\n",x*tmp.x,x*tmp.y);
	}
	return 0;
}

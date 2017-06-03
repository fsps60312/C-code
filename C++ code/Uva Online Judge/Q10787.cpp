#include<cstdio>
#include<cstdlib>
int T,amin,amax,bmin,bmax,mmin,mmax;
int floor(int a,int b)
{
	int c=a/b;
	return b*c<=a?c:c-1; 
}
int main()
{
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d%d%d%d%d",&amin,&amax,&bmin,&bmax,&mmin,&mmax);
		//how many b*2===0(mod m)
		bmin*=2,bmax*=2;
		int ans=0,a,b;
		for(int i=mmin;i<=mmax;i++)
		{
			a=floor(bmin,i);
			if(bmin%i==0) a--;
			b=floor(bmax,i);
			if(i&1)
			{
				if(b&1) b--;
				if(!a&1) a++;
				ans+=(b-a+1)/2;
			}
			else
			{
				ans+=b-a;
			}
		}
		printf("Case %d: %d\n",kase,ans*(amax-amin+1));
	}
	return 0;
}

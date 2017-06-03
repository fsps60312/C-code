#include<cstdio>
#include<cstdlib>
int T,m,n,p[30],times,ans;
int check(int a,int b,int c)
{
	int d=0;
	while(c)
	{
		d+=c/a;
		c/=a;
	}
	return d/b;
}
int main()
{
	p[0]=2,p[1]=3;
	for(int i=2,j;;i++)
	{
		p[i]=p[i-1];
		do
		{
			p[i]+=2;
			for(j=0;p[j]*p[j]<=p[i];j++)
			{
				if(p[i]%p[j]==0) break;
			}
		}while(p[i]%p[j]==0);
		if(p[i]>=75) break;
	}
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d",&m,&n);
		times=0,ans=2147483647;
		int j;
		for(int i=0;p[i]*p[i]<=m;i++)
		{
			while(m%p[i]==0)
			{
				m/=p[i];
				times++;
			}
			if(times)
			{
				j=check(p[i],times,n);
				if(j<ans) ans=j;
			}
			times=0;
		}
		if(m>1)
		{
			j=check(m,1,n);
			if(j<ans) ans=j;
		}
		printf("Case %d:\n",kase++);
		if(ans) printf("%d\n",ans);
		else printf("Impossible to divide\n");
	}
	return 0;
}

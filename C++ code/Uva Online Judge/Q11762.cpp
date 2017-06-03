#include<cstdio>
#include<cstdlib>
struct pairtype
{
	double e;
	int factor;
	int now;
};
int T,n;
pairtype ans[1000001];
int p[100000];
int main()
{
	for(int i=1;i<=1000000;i++)
	{
		ans[i].e=0;
		ans[i].factor=0;
	}
	p[0]=2,p[1]=3;
	for(int i=2;p[i-2]<=1000000;i++)
	{
		p[i]=p[i-1];
		int j;
		do
		{
			p[i]+=2;
			for(j=0;p[j]*p[j]<=p[i];j++)
			{
				if(p[i]%p[j]==0) break;
			}
		}while(p[i]%p[j]==0);
		//ans[p[i]].e=i+1;
	}
	//for(int i=0;i<50;i++) printf("%d\n",p[i]);printf("\n");
	//printf("pass p\n");
	ans[1].e=0;
	ans[1].factor=1;
	//ans[2].e=1;
	//ans[3].e=2;
	//S=1*p+2*q*p+3*q^2*p+......
	//qS=   1*p*q+2*q^2*p+......
	//(1-q)S=p/(1-q)=1;
	//S=1/p
	int now=0;
	for(int i=1;i<=1000000;i++)
	{
		if(i==p[now]) now++;
		ans[i].now=now;
	}
	for(int i=1;i<=1000000;i++)
	{
		//if(i==p[now]) now++;
		//ans[i].e=now/ans[i].e;//p is 1/now
		//ans[i].e+=1;
		ans[i].e=(ans[i].e+ans[i].now)/ans[i].factor;
		for(int j=0;i*p[j]<=1000000;j++)
		{
			ans[i*p[j]].e+=ans[i].e;
			ans[i*p[j]].factor++;
		}
	}
	//for(int i=1;i<50;i++) printf("%d %lf\n",i,ans[i]);
	//printf("pass ans\n");
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d",&n);
		printf("Case %d: %.10lf\n",kase,ans[n].e);
	}
	return 0;
}

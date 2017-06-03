#include<cstdio>
#include<cstdlib>
struct pairtype
{
	double x,y;
};
pairtype S[20];
int n;
double t;
double calr(int a,int b)
{
	//r/S[a].x+(t-r)/S[a].y==r/S[b].x+(t-r)/S[b].y
	//r(1/S[a].x-1/S[b].x)==(t-r)(1/S[b].y-1/S[a].y)
	//r(1/S[a].x-1/S[b].x+1/S[b].y-1/S[a].y)==t(1/S[b].y-1/S[a].y)
	double i=1.0;
	double c=i/S[a].x-i/S[b].x+i/S[b].y-i/S[a].y,d=t*(i/S[b].y-i/S[a].y);
	if(c==0) return -1;
	return d/c;
}
double findmin(double a,double b)
{
	double ans=(a/S[0].x+b/S[0].y)-(a/S[n].x+b/S[n].y);
	for(int i=1;i<n;i++)
	{
		double j=(a/S[i].x+b/S[i].y)-(a/S[n].x+b/S[n].y);
		if(j<ans) ans=j;
	}
	return ans;
}
int main()
{
	while(scanf("%lf%d",&t,&n)==2)
	{
		n--;
		for(int i=0;i<=n;i++)
		{
			scanf("%lf%lf",&S[i].x,&S[i].y);
		}
		//S[0].x=
		double ans1=-1.0,ans2=0.0;
		for(int i=0;i<n;i++)
		{
			for(int j=i+1;j<n;j++)
			{
				double r=calr(i,j);//i people & j people
				if(r<=0||r>=t) continue;
				double k=findmin(r,t-r);//run, swim
				//printf(" r=%.3lf,k=%.3lf\n",r,k);
				if(k>ans1) ans1=k,ans2=r;
			}
		}
		double k=findmin(0,t);//run, swim
		if(k>ans1) ans1=k,ans2=0;
		k=findmin(t,0);//run, swim
		if(k>ans1) ans1=k,ans2=t;
		//printf("t=%.3lf\n",t);
		if(ans1<0)
		{
			printf("The cheater cannot win.\n");
		}
		else
		{
			printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n",ans1*3600,ans2,t-ans2);
		}
	}
	return 0;
}

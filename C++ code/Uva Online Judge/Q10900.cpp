#include<cstdio>
#include<cstdlib>
long long pow2[32];
double ftmp[32];
int n;
double t;
double f(int a)
{
	if(ftmp[a]!=-1) return ftmp[a];
	if(a==n+1) return ftmp[a]=(double)pow2[n];
	//f(i)=sum(max(f(i+1)*p,2^i);
	double x=pow2[a-1]/f(a+1);
	if(x<=t) return ftmp[a]=f(a+1)*(t+1)/2;
	//x>t
	return ftmp[a]=(1-x)/(1-t)*f(a+1)*(x+1)/2+pow2[a-1]*(x-t)/(1-t);
}
int main()
{
	//freopen("in.txt","r",stdin);
	pow2[0]=1;
	for(int i=1;i<=31;i++) pow2[i]=pow2[i-1]<<1;
	while(scanf("%d%lf",&n,&t)==2&&(n||t>0))
	{
		for(int i=1;i<=n+1;i++) ftmp[i]=-1;
		printf("%.3lf\n",f(1));
		//for(int i=1;i<=n+1;i++) printf(" %.3lf",ftmp[i]);printf("\n");
	}
	return 0;
}

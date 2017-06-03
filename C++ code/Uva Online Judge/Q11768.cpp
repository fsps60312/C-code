#include<cstdio>
#include<cstdlib>
double x,y;
long long T,x1,y1,x2,y2;
int addt[10][10];//**i+j*addt[i][j]==**0
int loopn[]={1,10,5,10,5,2,5,10,5,10};
long long dfs(long long a,long long b)
{
	if(b==0) return a;
	return dfs(b,a%b);
}
long long gcd(long long a,long long b)
{
	if(a<0) a=-a;
	if(b<0) b=-b;
	return a>b?dfs(a,b):dfs(b,a);
}
int main()
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			addt[i][j]=-1;
			for(int k=0;k<10;k++)
			{
				if((i+j*k)%10==0)
				{
					addt[i][j]=k;
					break;
				}
			}
		}
	}
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lf%lf",&x,&y);
		x1=x*10,y1=y*10;
		scanf("%lf%lf",&x,&y);
		x2=x*10,y2=y*10;
		long long a=x2-x1,b=y2-y1,c=gcd(a,b);
		a/=c,b/=c;
		//x1+a*c=x2, y1+b*c==y2
		//find a*d+x1===0, b*d+y1===0(mod 10)
		//then all integer point: (x1+a*(d+loopn[a%10])*r, y1+a*(d+loopn[b%10])*r)
		//d==addt[x1%10][a%10]+loopn[a%10]*r
		//d==addt[y1%10][b%10]+loopn[b%10]*r
		//d===addt[x1%10][a%10](mod loopn[a%10])
		//d===addt[y1%10][b%10](mod loopn[b%10])
	}
	return 0;
}

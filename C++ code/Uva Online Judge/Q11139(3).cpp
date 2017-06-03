#include<cstdio>
#include<cstdlib>
long long ans[121],concavequads[121][121],gcdsum[121][121],gcd[121][121];//gcdsum[i][j]=gcd(0~i,0~j)
long long sumconcavequads(int x,int y)
{
	//area=inside+onside/2-1
	//insides=areas-onside/2+1s
	//one corner (*4)
	long long onside1=0,area1=0,sum1=0,onside2=0,area2=0,sum2=0,onside3=0,area3=0,sum3=0;
	//onsides==gcd(1~x-1,y)*(y-1)+gcd(1~y-1,x)*(x-1)+gcd(1~x-1,1~y-1)
	//onside1==onsides*4
	if(x>=2&&y>=2)
	{
	onside1+=(gcdsum[x-1][y]-gcdsum[0][y]-gcdsum[x-1][y-1]+gcdsum[0][y-1])*(y-1);//from (1,y) to (x-1,y), repeat (y-1) times
	onside1+=(gcdsum[y-1][x]-gcdsum[0][x]-gcdsum[y-1][x-1]+gcdsum[0][x-1])*(x-1);//from (1,x) to (y-1,x), repeat (x-1) times
	onside1+=gcdsum[x-1][y-1]-gcdsum[0][y-1]-gcdsum[x-1][0]+gcdsum[0][0];//from (1,1) to (x-1,y-1)
	//printf(" %lld\n",onside1);
	onside1*=4;//possible on four corner
	//areas==xy(x-1)(y-1)-(y-1)(1~x-1)y/2-(x-1)(1~y-1)x/2-(1~x-1)(1~y-1)/2
	//area1==areas*4
	area1+=x*y*(x-1)*(y-1)*4;//repeat (x-1)(y-1) times
	area1-=(y-1)*x*(x-1)*y;
	area1-=(x-1)*y*(y-1)*x;
	area1-=x*(x-1)*y*(y-1)/2;//(not always integer)
	//1s==(x-1)(y-1)
	//sum1==1s*4
	sum1+=(x-1)*(y-1)*4;
	//printf("%lld %lld %lld\n",onside1,area1,sum1);
	//two corner (*4)(upside down included)
	//onsides==gcd(0,y)*(y-1)+gcd(1~y-1,x)*2+gcd(0,x)*(x-1)+gcd(1*x-1,y)*2
	//onside2==onsides*2
	onside2+=(y*(y-1)+(gcdsum[y-1][x]-gcdsum[y-1][x-1]-gcdsum[0][x]+gcdsum[0][x-1])*2)*2;
	onside2+=(x*(x-1)+(gcdsum[x-1][y]-gcdsum[x-1][y-1]-gcdsum[0][y]+gcdsum[0][y-1])*2)*2;
	//areas==(x+y-2)*xy/2
	//area2==areas*2
	area2+=(x+y-2)*x*y;
	//1s==(x-1)+(y-1)
	//sum2==1s*2
	sum2+=(x+y-2)*2;
	//printf("%lld %lld %lld\n",onside2,area2,sum2);
	}
	//three corner (*4)
	//onsides==gcd(x,y)+x+y
	//onside3==onsides*4
	onside3+=(gcd[x][y]+x+y)*4;
	area3+=x*y*2;
	sum3+=4;
	//printf("%lld %lld %lld\n",onside3,area3,sum3);
	long long onside=onside1+onside2+onside3;
	long long area=area1+area2+area3;
	long long sum=sum1+sum2+sum3;
	long long ans=area-onside/2+sum;
	return ans;
}
long long dfs(int a,int b)
{
	if(b==0) return a;
	return dfs(b,a%b);
}
long long gcdf(int a,int b)
{
	return a>b?dfs(a,b):dfs(b,a);
}
long long C4(long long a)
{
	if(a<4) return 0;
	return a*(a-1)/2*(a-2)/3*(a-3)/4;
}
long long C3(long long a)
{
	if(a<3) return 0;
	return a*(a-1)/2*(a-2)/3;
}
long long contans(long long n)
{
	n++;
	long long ans=C4(n*n);
	//ans-=C4(n)*n*2;//same row||column
	//ans-=C3(n)*(n*(n-1))*n*2;//three same row||column
	long long c3=0,c4=0;
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<n;j++)
		{
			long long k=gcd[i][j]-1;//
			long long l=(n-i+1)*(n-j+1);
			c3+=k*(n*n-(k+1))*l;
			c4+=k*(k-1)*l;
		}
	}
	ans-=(c3-c4*3);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			ans-=(n-i+1)*(n-j+1)*concavequads[i][j];
		}
	}
	return ans;
}
int main()
{
	for(int i=0;i<=120;i++)
	{
		for(int j=0;j<=120;j++)
		{
			gcd[i][j]=gcdf(i,j);
		}
	}
	gcdsum[0][0]=0;
	for(int i=1;i<=120;i++)
	{
		gcdsum[i][0]=gcdsum[i-1][0]+i;//gcd(i,0)==i
		gcdsum[0][i]=gcdsum[0][i-1]+i;//gcd(0,i)==i
	}
	for(int i=1;i<=120;i++)
	{
		for(int j=1;j<=120;j++)
		{
			gcdsum[i][j]=gcdsum[i-1][j]+gcdsum[i][j-1]-gcdsum[i-1][j-1]+gcd[i][j];
		}
	}
	//printf("%lld\n",sumconcavequads(2,2));	return 0;
	for(int i=1;i<5;i++)
	{
		for(int j=1;j<5;j++)
		{
			printf("%lld ",sumconcavequads(i,j));
		}
		printf("\n");
	}
	for(int i=1;i<=120;i++)
	{
		for(int j=1;j<=120;j++)
		{
			concavequads[i][j]=sumconcavequads(i,j);
		}
	}
	//f[x][y]=E(g(i,j)*(x-i+1)*(y-j+1))
	for(int i=1;i<=120;i++) ans[i]=contans(i);
	int n;
	while(scanf("%d",&n)==1)
	{
		printf("%d %lld\n",n,ans[n]);
	}
	return 0;
}

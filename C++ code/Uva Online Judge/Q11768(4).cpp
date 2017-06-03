#include<cstdio>
#include<cstdlib>
int T,x[8],y[8];
double ddd[4];
bool vis[10][10];
int gcd(int a,int b)
{
	return b==0?(a>=0?a:-a):gcd(b,a%b);
}
int trans[]={1,10,5,10,5,2,5,10,5,10};
int lcm(int a,int b)
{
	return a/gcd(a,b)*b;
}
int mod(int a)
{
	return (a%10+10)%10;
}
int solve(int a,int b,int c,int d)
{
	int ans=0;
	while(a%10||b%10)
	{
		if(vis[a%10][b%10]) return -1;
		vis[a%10][b%10]=true;
		a+=c,b+=d;
		ans++;
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		for(int i=0;i<4;i++) scanf("%lf",&ddd[i]);
		x[0]=ddd[0]*10,y[0]=ddd[1]*10;
		x[1]=ddd[2]*10,y[1]=ddd[3]*10;
		x[2]=x[1]-x[0],y[2]=y[1]-y[0];
		int gc=gcd(x[2],y[2]);
		x[3]=x[2]/gc,y[3]=y[2]/gc;
		for(int i=0;i<10;i++)
		{
			for(int j=0;j<10;j++)
			{
				vis[i][j]=false;
			}
		}
		int ans=solve(mod(x[0]),mod(y[0]),mod(x[3]),mod(y[3]));
		if(ans==-1||ans>gc)
		{
			printf("0\n");
		}
		else
		{
			printf("%d\n",(gc-ans)/lcm(trans[mod(x[3])],trans[mod(y[3])])+1);
		}
	}
}

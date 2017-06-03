#include<cstdio>
#include<cstdlib>
long long n,ans,state[121][121];//one at (0,0) another at (n,m)
long long C(long long a,long long b)
{
	return a*(a-1);//because b is always 2
}
int dfs(int a,int b)
{
	if(b==0) return a;
	return dfs(b,a%b);
}
int gcd(int a,int b)
{
	return a>b?gcd(a,b):gcd(b,a);
}
int main()
{
	state[1][1]=1;
	for(int i=1;i<=120;i++)
	{
		for(int j=1;j<=120;j++)
		{
			state[i][j]=0;
			//the case one dot on (i,j)
			int k=gcd(i,j)-1;
			state[i][j]+=C((i-2)*(j-2)-k,2);//case not on rim
			state[i][j]+=2*((j-1)*((j-2)*(i-1)-k));//case on side1, another not on rim
			state[i][j]+=2*((i-1)*((i-2)*(j-1)-k));//case on side2, another not on rim
			//has no multi cases(no need to multiply 4)
			state[i][j]+=(j-1)*(j-1);//case both on side1
			state[i][j]+=(i-1)*(i-1);//case both on side2
			state[i][j]+=4*(i-2)*(j-2);//case on side1 & side2, not on corner
			state[i][j]+=2*(i+j-3);//case one on corner, another on rim
			state[i][j]++;//both on corner
			//the case no dot on (i,j), the one on (i,y), another on (x,j)
			for(int l=1;l<j;l++)//l is y
			{
				k=gcd(i,l)-1;
				state[i][j]+=C((i-2)*(j-1)-k,2);
				state[i][j]+=2*(j-2)*((j-1)*(i-1)-1);//case not in (i,0)
			}
		}
	}
	while(scanf("%lld",&n)==1&&n)
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				ans+=state[i][j]*(n-i+1)*(n-j+1);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

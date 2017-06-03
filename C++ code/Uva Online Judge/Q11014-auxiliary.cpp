#include<cstdio>
#include<cstdlib>
int dfs(int a,int b)
{
	return b==0?a:dfs(b,a%b);
}
int gcd(int a,int b,int c)
{
	return dfs(a,dfs(b,c));
}
int f1(int a)
{
	int ans=0;
	for(int i=1;i<=a;i++)
	{
		for(int j=1;j<=a;j++)
		{
			if(gcd(i,j,a)==1)
			{
				ans++;
			}//else
				//printf("(%d,%d)",i,j);
		}
	}
	return ans;
}
int f2(int a)
{
	int ans=0;
	for(int i=1;i<=a;i++)
	{
		for(int j=i;j<=a;j++)
		{
			if(gcd(i,j,a)==1) ans++;
		}
	}
	return ans;
}
int phi(int a)
{
	int ans=0;
	for(int i=1;i<=a;i++)
	{
		if(dfs(i,a)==1) ans++;
	}
	return ans;
}
int main()
{
	//freopen("Q11014.txt","w",stdout);
	printf("%d\n",f1(2));
	printf("%d\n",f1(3));
	printf("%d\n",f1(6));
	//return 0;
	for(int i=1;i<=100;i++)
	{
		printf("%d:\t%d\t%d\t%d\n",i,f1(i),f2(i),phi(i));
	}
}

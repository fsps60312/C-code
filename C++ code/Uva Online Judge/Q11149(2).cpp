#include<cstdio>
#include<cstdlib>
int n,K;
int mod(int a)
{
	return (a%10+10)%10;
}
struct Matrix
{
	int s[40][40];
	Matrix operator*(Matrix a)
	{
		Matrix ans;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				ans.s[i][j]=0;
				for(int k=0;k<n;k++)
				{
					ans.s[i][j]+=s[i][k]*a.s[k][j];
					ans.s[i][j]=mod(ans.s[i][j]);
				}
			}
		}
		return ans;
	}
	Matrix operator*=(Matrix a)
	{
		return (*this)=(*this)*a;
	}
	Matrix operator+(Matrix a)
	{
		Matrix ans;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				ans.s[i][j]=mod(s[i][j]+a.s[i][j]);
			}
		}
		return ans;
	}
	Matrix operator+=(Matrix a)
	{
		return (*this)=(*this)+a;
	}
	void show()
	{
		for(int i=0;i<n;i++)
		{
			printf("%d",s[i][0]);
			for(int j=1;j<n;j++)
			{
				printf(" %d",s[i][j]);
			}
			printf("\n");
		}
	}
};
Matrix Apow[32];
Matrix Asum[32];
Matrix I()
{
	Matrix ans;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			ans.s[i][j]=(i==j?1:0);
		}
	}
	return ans;
}
Matrix getpow(int a)
{
	Matrix ans=I();
	for(int i=0;i<32;i++)
	{
		if((1<<i)&a)
		{
			ans*=Apow[i];
		}
		else if((1<<i)>a) break;
	}
	return ans;
}
Matrix getsum(int a)
{
	int now=0;
	Matrix ans;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			ans.s[i][j]=0;
		}
	}
	for(int i=0;i<32;i++)
	{
		if((1<<i)&a)
		{
			ans+=Asum[i]*getpow(now);
			now+=(1<<i);
		}
		else if((1<<i)>a) break;
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	Matrix A;
	while(scanf("%d%d",&n,&K)==2&&n)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				scanf("%d",&A.s[i][j]);
				A.s[i][j]=mod(A.s[i][j]);
			}
		}
		Apow[0]=A;
		Asum[0]=A;
		for(int i=1;i<32;i++)
		{
			Apow[i]=Apow[i-1]*Apow[i-1];
			Asum[i]=Asum[i-1]+Asum[i-1]*Apow[i-1];
		}
		getsum(K).show();
		printf("\n");
	}
	return 0;
}

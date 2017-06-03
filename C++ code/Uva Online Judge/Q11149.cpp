#include<cstdio>
#include<cstdlib>
int n,K;
int mod(double a)
{
	int b=(int)(a+0.5);
	return (b%10+10)%10;
}
struct Matrix
{
	double s[40][40];
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
		return *this=*this*a;
	}
	Matrix operator-(Matrix a)
	{
		Matrix ans;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				ans.s[i][j]=s[i][j]-a.s[i][j];
			}
		}
		return ans;
	}
	Matrix operator+=(Matrix a)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				s[i][j]+=a.s[i][j];
			}
		}
		return *this;
	}
	void swapr(int a,int b)
	{
		double j;
		for(int i=0;i<n;i++)
		{
			j=s[a][i];
			s[a][i]=s[b][i];
			s[b][i]=j;
		}
	}
	void addto(int a,int b,double c)
	{
		for(int i=0;i<n;i++)
		{
			s[b][i]+=s[a][i]*c;
		}
	}
};
void show(Matrix a)
{
	for(int i=0;i<n;i++)
	{
		printf("%d",mod(a.s[i][0]));
		for(int j=1;j<n;j++)
		{
			printf(" %d",mod(a.s[i][j]));
		}
		printf("\n");
	}
}
Matrix I()
{
	Matrix ans;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			ans.s[i][j]=i==j?1:0;
		}
	}
	return ans;
}
bool iszero(double a)
{
	return a>=-1e-5&&a<=1e-5;
}
Matrix inver(Matrix a)
{
	Matrix ans=I();
	//printf("stage0:\n");	show(ans);	show(a);
	for(int i=0;i<n;i++)
	{
		if(iszero(a.s[i][i]))
		{
			bool breaked=false;
			for(int j=i+1;j<n;j++)
			{
				if(!iszero(a.s[j][i]))
				{
					a.swapr(i,j);
					ans.swapr(i,j);
					//printf("pass\n");
					breaked=true;
					break;
				}
			}
			if(!breaked)
			{
				printf("error\n");
			}
		}
		for(int j=i+1;j<n;j++)
		{
			double k=-a.s[j][i]/a.s[i][i];
			a.addto(i,j,k);
			ans.addto(i,j,k);
		}
		//show(a);
	}
	//printf("stage1:\n");	show(ans);	show(a);
	for(int i=n-1;i>=0;i--)
	{
		for(int j=i-1;j>=0;j--)
		{
			double k=-a.s[j][i]/a.s[i][i];
			a.addto(i,j,k);
			ans.addto(i,j,k);
		}
	}
	//printf("stage2:\n");	show(ans);	show(a);
	return ans;
}
Matrix pow(Matrix a,int b)
{
	Matrix ans=I();
	while(b)
	{
		if(b&1)
		{
			ans*=a;
		}
		a*=a;
		b>>=1;
	}
	return ans;
}
bool haveinver(Matrix a)
{
	//show(a);
	double ans=0;
	//printf("%lf\n",ans);
	for(int i=0;i<n;i++)
	{
		double k=1;
		for(int j=0;j<n;j++)
		{
			k*=a.s[(i+j)%n][j];
		}
		ans+=k;
	}
	//printf("%lf\n",ans);
	for(int i=0;i<n;i++)
	{
		double k=1;
		for(int j=0;j<n;j++)
		{
			k*=a.s[((i-j)%n+n)%n][j];
		}
		ans-=k;
	}
	//printf("haveinver:%lf\n",ans);
	return !iszero(ans);
}
bool iszero(Matrix a)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(!iszero(a.s[i][j])) return false;
		}
	}
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	Matrix a;
	while(scanf("%d%d",&n,&K)==2&&n)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				scanf("%lf",&a.s[i][j]);
				a.s[i][j]=mod(a.s[i][j]);
			}
		}
		//printf("%d\n",haveinver(I()-a));
		//IS=A+A^2+A^3+...+A^K
		//AS=  A^2+A^3+...+A^K+A^(K+1)
		//(I-A)S=A-A^(K+1)
		//S=(I-A)^-1*(A-A^(K+1))
		Matrix ans;
		if(haveinver(I()-a))
		{
			//show(a);
			ans=inver(I()-a);
			//printf("a\n");
			//show(ans);
			//printf("true\n");
			ans*=(a-pow(a,K+1));//*(I()-pow(a,K));
			//printf("b\n");
			//show(ans);
		}
		else
		{
			ans=I()*a;
			Matrix now=a*a;
			//printf("a\n");
			//show(ans);
			for(int i=2;i<=K&&!iszero(now);i++)
			{
				ans+=now;
				now*=a;
			}
			//printf("false\n");
		}
		show(ans);
		printf("\n");
	}
	return 0;
}

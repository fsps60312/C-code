#include<cstdio>
#include<cstdlib>
int T,N,L,FAIL[13];
char S[13];
void buildfail()
{
	int u=0;
	FAIL[0]=FAIL[1]=0;
	for(int i=1;S[i];i++)
	{
		while(u&&S[i]!=S[u])u=FAIL[u];
		if(S[i]==S[u])u++;
		FAIL[i+1]=u;
	}
}
struct Matrix
{
	double s[12][12];
	void init()
	{
		for(int i=0;i<L;i++)
		{
			for(int j=0;j<L;j++)
			{
				s[i][j]=0;
			}
		}
	}
	void build()
	{
		for(int i=0;i<L;i++)
		{
			for(int c=0;c<N;c++)
			{
				int u=i;
				while(u&&S[u]!='A'+c)u=FAIL[u];
				if(S[u]=='A'+c)u++;
				if(u==L)continue;
				s[u][i]+=1.0/N;
			}
		}
	}
	void addto(int r1,int r2,double addv)
	{
		for(int i=0;i<L;i++)
		{
			s[r2][i]+=s[r1][i]*addv;
		}
	}
	void exchange(int r1,int r2)
	{
		double a;
		for(int i=0;i<L;i++)
		{
			a=s[r1][i];
			s[r1][i]=s[r2][i];
			s[r2][i]=a;
		}
	}
	Matrix operator-(Matrix a)
	{
		Matrix ans;
		for(int i=0;i<L;i++)
		{
			for(int j=0;j<L;j++)
			{
				ans.s[i][j]=s[i][j]-a.s[i][j];
			}
		}
		return ans;
	}
	Matrix operator*(Matrix a)
	{
		Matrix ans;
		for(int r=0;r<L;r++)
		{
			for(int c=0;c<L;c++)
			{
				double &d=ans.s[r][c];
				d=0;
				for(int i=0;i<L;i++)
				{
					d+=s[r][i]*a.s[i][c];
				}
			}
		}
		return ans;
	}
	void show()
	{
		for(int r=0;r<L;r++)
		{
			for(int c=0;c<L;c++)
			{
				printf(" %.3lf",s[r][c]);
			}
			printf("\n");
		}
		printf("\n");
	} 
}M;
Matrix I()
{
	Matrix ans;
	ans.init();
	for(int i=0;i<L;i++)ans.s[i][i]=1;
	return ans;
}
double mul(Matrix a,double* b)
{
	double tb[L],ans=0;
	for(int i=0;i<L;i++)
	{
		tb[i]=0;
		for(int j=0;j<L;j++)
		{
			tb[i]+=a.s[i][j]*b[j];
		}
		ans+=tb[i];
	}
	for(int i=0;i<L;i++)b[i]=tb[i];
	return ans;
}
bool iszero(double a)
{
	double errorrate=1e-7;
	return a>-errorrate&&a<errorrate;
}
Matrix inv(Matrix a)
{
	Matrix ans=I();
	//printf("initial a:\n");a.show();
	for(int r=0;r<L;r++)
	{
		if(iszero(a.s[r][r]))
		{
			for(int tr=r+1;tr<L;tr++)
			{
				if(!iszero(a.s[tr][r]))
				{
					a.exchange(r,tr);
					ans.exchange(r,tr);
					break;
				}
			}
		}
		if(iszero(a.s[r][r]))return ans;
		for(int tr=0;tr<L;tr++)
		{
			if(tr==r)continue;
			double d=-a.s[tr][r]/a.s[r][r];
			a.addto(r,tr,d);
			ans.addto(r,tr,d);
			//printf(" d=%lf",d);
		}
	}
	//printf("Matrix a:\n");a.show();
	//printf("Matrix ans:\n");ans.show();
	for(int r=0;r<L;r++)
	{
		double d=1/a.s[r][r];
		for(int c=0;c<L;c++)
		{
			a.s[r][c]*=d;
			ans.s[r][c]*=d;
		}
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d",&T);
	int kase=0;
	while(T--)
	{
		scanf("%d%s",&N,S);
		if(kase)printf("\n");
		L=-1;while(S[++L]);
		buildfail();
		M.init();
		M.build();
		double ans=0;
		//S1=M*A+2M^2*A+3M^3*A+...
		//M*S1=   M^2*A+2M^3*A+...
		//(I-M)*S1=(M+M^2+M^3+...)*A=S2
		//M*S2=    (  M^2+M^3+...)*A
		//(I-M)*S2=M*A
		Matrix S2=inv(I()-M)*M;
		Matrix S1=inv(I()-M)*S2;
		printf("Matrix S1:\n");S1.show();
		for(int i=0;i<L;i++)ans+=S1.s[L-1][i];
		printf("Case %d:\n%.0lf\n",++kase,ans);
	}
	return 0;
}

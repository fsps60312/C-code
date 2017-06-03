#include<cstdio>
#include<cstdlib>
#define LL long long
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
struct Fraction
{
	LL up,down;
	LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
	void reduce(){if(up==0){down=1;return;}LL a=gcd(up,down);up/=a;down/=a;}
	void operator=(int a){up=a,down=1;}
	Fraction(){}
	Fraction(int up):up(up){down=1;}
	Fraction operator*(Fraction a)
	{
		Fraction ans;
		ans.up=up*a.up;
		ans.down=down*a.down;
		ans.reduce();
		return ans;
	}
	Fraction operator*=(Fraction a){return (*this)=((*this)*a);}
	Fraction operator/(Fraction a)
	{
		Fraction ans;
		ans.up=up*a.down;
		ans.down=down*a.up;
		ans.reduce();
		return ans;
	}
	Fraction operator+(Fraction a)
	{
		Fraction ans;
		ans.down=down*a.down;
		ans.up=up*a.down+a.up*down;
		ans.reduce();
		return ans;
	}
	Fraction operator+=(Fraction a){return (*this)=((*this)+a);}
	Fraction operator-()
	{
		Fraction ans;
		ans.up=-up,ans.down=down;
		return ans;
	}
	Fraction operator-(Fraction a){return (*this)+(-a);}
	Fraction operator-=(Fraction a){return (*this)=((*this)-a);}
	double value(){return (double)up/down;}
};
struct Matrix
{
	Fraction s[12][12];
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
		Fraction a;a.up=1,a.down=N;
		for(int i=0;i<L;i++)
		{
			for(int c=0;c<N;c++)
			{
				int u=i;
				while(u&&S[u]!='A'+c)u=FAIL[u];
				if(S[u]=='A'+c)u++;
				if(u==L)continue;
				s[u][i]+=a;
			}
		}
	}
	void addto(int r1,int r2,Fraction addv)
	{
		for(int i=0;i<L;i++)
		{
			s[r2][i]+=(s[r1][i]*addv);
		}
	}
	void exchange(int r1,int r2)
	{
		Fraction a;
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
				ans.s[i][j]=(s[i][j]-a.s[i][j]);
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
				Fraction &d=ans.s[r][c];
				d=0;
				for(int i=0;i<L;i++)
				{
					d+=(s[r][i]*a.s[i][c]);
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
				printf(" %.3lf",s[r][c].value());
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
Matrix inv(Matrix a)
{
	Matrix ans=I();
	//printf("initial a:\n");a.show();
	for(int r=0;r<L;r++)
	{
		if(a.s[r][r].up==0)
		{
			for(int tr=r+1;tr<L;tr++)
			{
				if(a.s[tr][r].up!=0)
				{
					a.exchange(r,tr);
					ans.exchange(r,tr);
					break;
				}
			}
		}
		for(int tr=0;tr<L;tr++)
		{
			if(tr==r)continue;
			Fraction d=(-a.s[tr][r]/a.s[r][r]);
			a.addto(r,tr,d);
			ans.addto(r,tr,d);
			//printf(" d=%lf",d);
		}
	}
	//printf("Matrix a:\n");a.show();
	//printf("Matrix ans:\n");ans.show();
	for(int r=0;r<L;r++)
	{
		Fraction d=((Fraction)1/a.s[r][r]);
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
	//freopen("in.txt","r",stdin);
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
		Fraction ans=0;
		//ans=M*A-I*A+2(M^2*A-M*A)+...=S1-M^-1^S1
		//S1=M*A+2M^2*A+3M^3*A+...
		//M*S1=   M^2*A+2M^3*A+...
		//(I-M)*S1=(M+M^2+M^3+...)*A=S2
		//M*S2=    (  M^2+M^3+...)*A
		//(I-M)*S2=M*A
		Matrix S2=inv(I()-M)*M;
		Matrix S1=inv(I()-M)*S2;
		Matrix Ans=(I()-inv(M))*S1;
		//printf("Matrix Ans:\n");Ans.show();
		for(int r=0;r<L;r++)
		{
			ans-=Ans.s[r][0];
		}
		printf("Case %d:\n%.0lf\n",++kase,ans.value());
	}
	return 0;
}

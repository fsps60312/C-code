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
}M;
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
const double errorrate=1e-7;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	int kase=0;
	while(T--)
	{
		scanf("%d%s",&N,S);
		if(kase)printf("\n");
		L=-1;while(S[++L]);
		buildfail();
		//printf("FAIL:");for(int i=0;i<=L;i++)printf(" %d",FAIL[i]);printf("\n");
		M.init();
		M.build();
		double A[L];A[0]=1;
		for(int i=1;i<L;i++)A[i]=0;
		int path=1;
		double pred,nowd=1,ans=0;
		//for(int i=0;i<L;i++){for(int j=0;j<L;j++)printf(" %.3lf",M.s[i][j]);printf("\n");}
		printf("a\n");
		do
		{
			pred=nowd;
			nowd=mul(M,A);
			printf("now=%.10lf\n",nowd);
			//for(int i=0;i<L;i++)printf(" %.3lf",A[i]);printf("\n");
			ans+=(pred-nowd)*(path++);
		}while(pred-nowd<errorrate);
		printf("b\n");
		do
		{
			pred=nowd;
			nowd=mul(M,A);
			printf("now=%lf\n",nowd);
			//for(int i=0;i<L;i++)printf(" %.3lf",A[i]);printf("\n");
			ans+=(pred-nowd)*(path++);
		}while(pred-nowd>errorrate);
		//printf("c\n");
		//printf("b\n");
		/*do
		{
			nowd=mul(M,A);
			ans+=(pred-nowd)*(path++);
		}while(pred-nowd>errorrate);*/
		printf("Case %d:\n%.0lf\n",++kase,ans);
	}
	return 0;
}

#include<cstdio>
#define LL long long
void termin(char *c){puts(c);int a[9];for(int i=0;;i++)a[i]=9;}
int M,N,S;
double A,B;
double MAT[20][21],C[21][21];
double abs(double &a){return a>=0.0?a:-a;}
void initMAT()
{
	for(int i=0;i<S;i++)for(int j=0;j<=S;j++)MAT[i][j]=0.0;
	for(int d=S;d>=0;d--)//degree
	{
		for(int a=0;a<=d;a++)//pow of A 
		{
			//C(d,a)*A^a*B^(d-a)
			double r=1LL;
			for(int i=0;i<a/M;i++)r*=A;
			for(int i=0;i<(d-a)/N;i++)r*=B;
			if(d<S)MAT[a%M*N+(d-a)%N][d]+=r*C[d][a];//A^(a/M)*B^(b/N)
			else MAT[a%M*N+(d-a)%N][S]-=r*C[d][a];
		}
	}
}
void Exchange(int r1,int r2)
{
	double v;
	for(int i=0;i<=S;i++)v=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=v;
}
void Kill(int r1,int r2,double ratio){for(int i=0;i<=S;i++)MAT[r1][i]-=MAT[r2][i]*ratio;}
bool Zero(double a){double eps=1e-9;return a<eps&&a>-eps;}
void solve()
{
	for(int i=0;i<S;i++)
	{
		int j;for(j=i;j<S;j++)if(!Zero(MAT[j][i]))break;
		if(j==S)termin("j==N");
		Exchange(i,j);
		for(int k=0;k<S;k++)
		{
			if(k==i||Zero(MAT[k][i]))continue;
			Kill(k,i,MAT[k][i]/MAT[i][i]);
		}
	}
	for(int i=0;i<S;i++)
	{
//		if(MAT[i][S]%MAT[i][i])termin("not divisable");
		MAT[i][S]/=MAT[i][i];
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=0;i<=20;i++)
	{
		C[i][0]=C[i][i]=1.0L;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	while(scanf("%lf%d%lf%d",&A,&M,&B,&N)==4&&(A||M||B||N))
	{
		S=M*N;
		initMAT();
		solve();
		printf("1");
		for(int i=S-1;i>=0;i--)printf(" %d",(int)(MAT[i][S]+(MAT[i][S]>0.0?0.5:-0.5)));
		puts("");
	}
	return 0;
}

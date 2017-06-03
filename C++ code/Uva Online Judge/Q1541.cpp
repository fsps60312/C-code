#include<cstdio>
#include<cmath>
#include<cassert>
using namespace std;
const int INF=2147483647;
const double EPS=1e-9;
int N;
struct Matrix
{
	double s[52][52];
	Matrix(){}
	Matrix &operator*(const Matrix &a)const
	{
		static Matrix ans;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			double &v=ans.s[i][j]=0.0;
			for(int k=0;k<N;k++)v+=s[i][k]*a.s[k][j];
		}
		return ans;
	}
};
int T,BOARD[52];
Matrix &Pow(Matrix &a,int p)
{
	static Matrix ans;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)ans.s[i][j]=(i==j?1.0:0.0);
//	for(int i=0;i<p;i++)ans=ans*a;return ans;
	while(p)
	{
		if(p&1)ans=ans*a;
		a=a*a;
		p>>=1;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	static int casenumber;
	for(scanf("%d",&casenumber);casenumber--;)
	{
		scanf("%d%d",&N,&T);
		N+=2;
		BOARD[0]=0,BOARD[N-1]=INF;
		for(int i=1;i+1<N;i++)
		{
			static char elem[10];scanf("%s",elem);//element
			if(elem[0]=='L')BOARD[i]=INF;
			else assert(sscanf(elem,"%d",&BOARD[i])==1);
		}
		static Matrix a,result;
		for(int i=0;i<N*N;i++)a.s[i/N][i%N]=0.0;
		for(int i=0;i<N;i++)if(BOARD[i]!=INF)
		{
			if(i+1<N&&BOARD[i+1]!=INF)a.s[i+1+BOARD[i+1]][i]+=0.5,printf("(%d,%d)\n",i,i+1+BOARD[i+1]);
			if(i+2<N&&BOARD[i+2]!=INF)a.s[i+2+BOARD[i+2]][i]+=0.5,printf("(%d,%d)\n",i,i+2+BOARD[i+2]);
		}
		result=Pow(a,T);
		double ans=0.0;
		for(int i=0;i<N;i++)if(BOARD[i]!=INF)ans+=result.s[i][0];
		ans=1.0-ans;
		if(fabs(ans-0.5)<EPS)printf("Push");
		else if(ans<0.5)printf("Bet against");
		else printf("Bet for");
		printf(". %.4f\n",ans);
	}
	return 0;
}

#include<cstdio>
const double EPS=1e-9,INF=1e100;
struct Matrix
{
	double s[2][2];
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans;
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)
		{
			double &v=ans.s[i][j]=0.0;
			for(int k=0;k<2;k++)v+=s[i][k]*a.s[k][j];
		}
		return ans;
	}
	bool ReachINF(const double &v){return v<-INF||v>INF;}
	bool ReachINF()const{return ReachINF(s[0][0])||ReachINF(s[0][1])||ReachINF(s[1][0])||ReachINF(s[1][1]);}
	void Print()
	{
		printf("%.4f %.4f\n%.4f %.4f\n\n",s[0][0],s[0][1],s[1][0],s[1][1]);
	}
}M;
int T;
double A,B;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf%lf%lf%lf",&M.s[0][0],&M.s[0][1],&M.s[1][0],&M.s[1][1]);
		scanf("%lf%lf",&A,&B);
		M.s[0][1]*=-1.0;
		M.s[0][0]+=1.0,M.s[1][1]+=1.0;
		Matrix a=M;
		for(;!a.ReachINF();a=a*a);
		for(int i=0;i<10;i++)
		{
			printf("A=%.4f,B=%.4f\n",A*a.s[0][0]+B*a.s[0][1],A*a.s[1][0]+B*a.s[1][1]);
			a.Print();
			a=a*M;
		}
	}
	return 0;
}

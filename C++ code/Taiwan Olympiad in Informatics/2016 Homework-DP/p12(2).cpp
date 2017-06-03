#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
void getmax(double &a,const double b){}
struct Matrix
{
	pair<double,double>S[7][7];//S[i][j]: i dollars, j dollars, S[i][j].first: chance, S[i][j].second: cost
	double S[7][7];//max expect wc of money from i to j after n rounds
	//A[i][k]-B[k][j]->S[i][j]
	//S[i][j]=A[i][k]
};
Matrix operator*(const Matrix &a,const Matrix &b)
{
	Matrix ans;
	for(int i=0;i<R*G;i++)for(int j=0;j<R*G;j++)ans.S[i][j]=make_pair(0.0,0.0);
	for(int i=0;i<R*G;i++)for(int j=0;j<R*G;j++)
	{
		double &v=ans.S[i][j]=make_pair(0.0,0.0);
		for(int k=0;k<R*G;k++)
		{
			v.first+=a.S[i][k].first*b.S[k][j].first;
			getmax(v.second,a.S[i][k].second+b.S[k][j].second);
		}
	}
}
int N,R,G;
double P[1000],SUM;
pair<double,double>V[3][3];//when have i chances, chance warrior choose to refresh j times, get v win chance
double BuildWinChance()
{
	SUM=0.0;
	for(int i=0;i<N;i++)SUM+=P[i];
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)V[i][j]=make_pair(0.0,0.0);
	V[0][0]=make_pair(1.0,SUM/N);//chance, earn
	int cnt1=0,cnt2=0;
	for(int i=0;i<N;i++)//every condition has chance 1/N
	{
		if(P[i]<SUM/N)V[1][1].first+=1.0/N,V[1][1].second+=SUM,cnt1++;
		else 		  V[1][0].first+=1.0/N,V[1][0].second+=P[i],cnt2++;
	}
	if(cnt1)V[1][1].second/=cnt1;
	if(cnt2)V[1][0].second/=cnt2;
	cnt1=cnt2=0;
	for(int i=0;i<N;i++)
	{
		if(P[i]<V[1][0].first*V[1][0].second+V[1][1].first*V[1][1].second)
		{
			V[2][1].first+=1.0/N*V[1][0].first,V[2][1].second+=V[1][0].second,cnt1++;
			V[2][2].first+=1.0/N*V[1][1].first,V[2][2].second+=V[1][1].second,cnt2++;
		}
		else V[2][0].first+=1.0/N,V[2][0].second+=P[i];
	}
	V[2][0].second*=V[2][0].first;
	if(cnt1)V[2][1].second/=cnt1;
	if(cnt2)V[2][2].second/=cnt2;
}
double Solve()
{
	
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&R,&G)==3)
	{
		for(int i=0;i<N;i++)scanf("%lf",&P[i]);
		printf("%.9f\n",Solve());
	}
	return 0;
}

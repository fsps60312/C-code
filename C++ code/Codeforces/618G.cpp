#include<cstdio>
#include<cassert>
using namespace std;
const double EPS=1e-15;
/*
F[1][1]=p
F[1][2]=q
F[2][1,2]=pq
F[2][2,1]=qp+ppp
F[2][3,1]=ppqp+qqp
F[2][3,2]=ppqq+qqq
F[3][1,2,1]=pqp
F[3][1,3,1]=pqq
[]
F(N,"")=p*p*F'(N,""+2)+q*F(N,""+2)+p*q*F(N-1,""+2)
F': special when N==1
F(N,""+2)=p*p*F'(N,""+3)+q*F(N,""+3)+p*q*F(N-2,""+2)
F': special when N==2
F(N,""+3)=p*p*F'(N,""+3+2)+q*F(N,""+3+2)+p*q*F(N-2,""+2)
F': special when N==2
F(N)=p*p*F_211(N,1)+q*F_22(N,1)+p*q*(1+F_22(N-1,1))
F_211(N,i)=p*p*F_211(N,i+1)+q*F_22(N,i+1)+p*q*(Sum(i)+F_22(N-Len(i)-1,1))
F_22(N,i)=p*p*F_211(N,i+1)+q*F_22(N,i+1)+p*q*(Sum(i)+F_22(N-Len(i)-1,1))
Len(1)=1(2)		Sum(1)=2
Len(2)=1(3)		Sum(2)=3
Len(3)=2(3,2)	Sum(3)=5
Len(4)=1(4)		Sum(4)=4
Len(5)=2(4,2)	Sum(5)=6
Len(6)=2(4,3)	Sum(6)=7
Len(7)=3(4,3,2)	Sum(7)=9
Len(8)=1(5)		Sum(8)=5
*/
int N;
double P,Q;
int Sum(const int v)
{
	int ans=0; 
	for(int i=0;(1<<i)<=v;i++)if(v&(1<<i))ans+=i+2;
	return ans;
}
int Len(const int v)
{
	int ans=0;
	for(int i=0;(1<<i)<=v;i++)if(v&(1<<i))++ans;
	return ans;
}
double F_22[1000][1000];
double GetF_22(double zoom,const int n,const int i)
{
	if(zoom<EPS)return 0.0;
//	if(N-n>900||i>900)return 0.0;
	if(!(0<=N-n&&N-n<1000&&0<=i&&i<1000))
	{
		printf("(zoom=%.10f,%d,%d)\n",zoom,N-n,i);
		assert(0);
	}
//	assert(0<=N-n&&N-n<1000&&0<=i&&i<1000);
	double &ans=F_22[N-n][i];
	if(ans!=-1.0)return ans;
	ans=0.0;
	if(n==Len(i))return ans=Sum(i);
	else if(n>=Len(i)+2)
	{
		ans+=P*P*GetF_22(zoom*P*P,n,i+1);
		ans+=P*Q*(Sum(i)+GetF_22(zoom*P*Q,n-Len(i)-1,1));
		ans+=Q*GetF_22(zoom*Q,n,i+1);
		return ans;
	}
	else
	{
		assert(n==Len(i)+1);
		ans+=P*(Sum(i)+1.0);
		ans+=Q*(GetF_22(zoom*Q,n,i+1));
		return ans;
	}
}
//void Debug()
//{
//	long double p=999999999;
//	p/=1000000000;
//	long double v=1;
//	for(int i=0;;i++)
//	{
//		printf("i=%d,v=%.10f\n",i,(double)v);
//		v*=p;
//	}
//}
int main()
{
//	Debug();
	freopen("in.txt","r",stdin);
	while(scanf("%d%lf",&N,&P)==2)
	{
		P/=1e9;
		Q=1.0-P;
		assert(0.0<Q&&0.0<P);
		for(int i=0;i<1000;i++)for(int j=0;j<1000;j++)F_22[i][j]=-1.0;
		double ans=0.0;
		if(N==1)ans=P*1.0+Q*2.0;
		else ans=P*P*GetF_22(P*P,N,1)+Q*GetF_22(Q,N,1)+P*Q*(1.0+GetF_22(P*Q,N-1,1));
		printf("%.10f\n",ans);
	}
	return 0;
}

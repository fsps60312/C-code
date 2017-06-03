#include<cstdio>
int N,M,K;
double P1,P2,P3,P4,DP[2001][2001];
double solve()
{
	if(P4==0.0)return 0.0;
	//P1:Active failed
	//P2:Connect failed
	//P3:Active success
	//P4:Server down
	//each change require 1.0/(1.0-P1) times
	//chance of P4^(1.0/(1.0-P1)) down
	//F(i,j):i people, rank j. Chance of down in rank 1~K
	//F(i,1)=P1*F(i,1)+P2*F(i,i)+P4
	//F(i,1)=(P2*F(i,i)+P4)/(1-P1)
	//F(i,1)=P2/(1-P1)*F(i,i)+P4/(1-P1)
	//j<=K,F(i,j)=P1*F(i,j)+P2*F(i,j-1)+P3*F(i-1,j-1)+P4
	//F(i,j)=(P2*F(i,j-1)+P3*F(i-1,j-1)+P4)/(1-P1)
	//F(i,j)=P2/(1-P1)*F(i,j-1)+(P3*F(i-1,j-1)+P4)/(1-P1)
	//j>K,F(i,j(>K))=P1*F(i,j)+P2*F(i,j-1)+P3*F(i-1,j-1)
	//F(i,j)=(P2*F(i,j-1)+P3*F(i-1,j-1))/(1-P1)
	//F(i,j)=P2*F(i,j-1)/(1-P1)+P3*F(i-1,j-1)/(1-P1)
	DP[1][1]=P4/(1.0-P1-P2);//A=P1*A+P2*A+P4
	for(int len=2;len<=N;len++)
	{
		double a=1.0,b=0.0;
		for(int i=2;i<=len&&i<=K;i++)
		{
			a*=P2/(1.0-P1);
			b*=P2/(1.0-P1);
			b+=(P3*DP[len-1][i-1]+P4)/(1-P1);
		}
		for(int i=K+1;i<=len;i++)
		{
			a*=P2/(1.0-P1);
			b*=P2/(1.0-P1);
			b+=P3*DP[len-1][i-1]/(1-P1);
		}
		a*=P2/(1.0-P1);
		b*=P2/(1.0-P1);
		b+=P4/(1.0-P1);
		a-=1.0;
		DP[len][1]=-b/a;
		for(int i=2;i<=len&&i<=K;i++)DP[len][i]=(P2*DP[len][i-1]+P3*DP[len-1][i-1]+P4)/(1.0-P1);
		for(int i=K+1;i<=len;i++)DP[len][i]=(P2*DP[len][i-1]+P3*DP[len-1][i-1])/(1.0-P1);
	}
	return DP[N][M];
}
int main()
{
	while(scanf("%d%d%d%lf%lf%lf%lf",&N,&M,&K,&P1,&P2,&P3,&P4)==7)
	{
		printf("%.5f\n",solve());
	}
	return 0;
}

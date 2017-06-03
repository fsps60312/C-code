#include<cstdio>
int main()
{
	while(scanf("%d%d%d%lf%lf%lf%lf",&N,&M,&K,&P1,&P2,&P3,&P4)==7)
	{
		//P1:Active failed
		//P2:Connect failed
		//P3:Active success
		//P4:Server down
		//each change require 1.0/(1.0-P1) times
		//chance of P4^(1.0/(1.0-P1)) down
		//F(i,j):i people, rank j
		//F(i,1)=P1*F(i,1)+P2*F(i,i)+P3
		//F(i,j)=P1*F(i,j)+P2*F(i,j-1)+P3*F(i-1,j-1)
		double ans=0.0;
	}
	return 0;
}

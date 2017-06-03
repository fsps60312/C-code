#include<cstdio>
#define min(x,y) (x<y?x:y)
int N;
double Pl,Pr,DP[1001];
void getmin(double &a,double b){if(b<a)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%lf%lf",&Pl,&Pr);
		DP[0]=0.0;
		for(int l=1;l<=N;l++)
		{
			int i=1;
			DP[l]=(1.0+DP[i-1]+DP[l-i]-Pl*DP[l-i]-Pr*DP[i-1])/(1.0-Pl-Pr);
			for(i=2;i<=l;i++)
			{
				//DP[l]=1.0+Pl*(DP[i-1]+DP[l])+Pr*(DP[l-i]+DP[l])
				//DP[l]*(1.0-Pl-Pr)=1.0+Pl*DP[i-1]+Pr*DP[l-i]
				//DP[l]=1.0+DP[i-1]+DP[l-i]+Pl*(DP[l]-DP[l-i])+Pr*(DP[l]-DP[i-1])
				getmin(DP[l],(1.0+DP[i-1]+DP[l-i]-Pl*DP[l-i]-Pr*DP[i-1])/(1.0-Pl-Pr));
			}
		}
		printf("%.2f\n",DP[N]);
	}
	return 0;
}

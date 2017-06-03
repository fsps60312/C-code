#include<cstdio>
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int W,H,N;
int DP[601][601];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&W,&H,&N);
	for(int i=1;i<=W;i++)for(int j=0;j<=H;j++)DP[i][j]=i*j;
	for(int i=0,w,h;i<N;i++)scanf("%d%d",&w,&h),DP[w][h]=0;
	for(int h=1;h<=H;h++)
	{
		for(int w=1;w<=W;w++)
		{
			for(int i=1;i*2<=w;i++)getmin(DP[w][h],DP[i][h]+DP[w-i][h]);
			for(int i=1;i*2<=h;i++)getmin(DP[w][h],DP[w][i]+DP[w][h-i]);
		}
	}
	printf("%d\n",DP[W][H]);
	return 0;
}

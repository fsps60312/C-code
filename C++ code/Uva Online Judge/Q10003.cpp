#include<cstdio>
#include<vector>
using namespace std;
int L,N;
int DP[52][52];
int CUTP[52];
int getL(int a,int b){return CUTP[b]-CUTP[a];}
void getmin(int &a,int b){if(b<a)a=b;}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&L)==1&&L)
	{
		scanf("%d",&N);
		CUTP[0]=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&CUTP[i]);
		}
		N+=2;
		CUTP[N-1]=L;
		for(int i=0;i<N;i++)DP[i][i]=0;
		for(int i=0;i+1<N;i++)DP[i][i+1]=0;
		for(int l=2;l<N;l++)
		{
			for(int i=0;i+l<N;i++)
			{
				int len=getL(i,i+l);
				DP[i][i+l]=len+DP[i][i+1]+DP[i+1][i+l];
				for(int j=2;j<l;j++)getmin(DP[i][i+l],len+DP[i][i+j]+DP[i+j][i+l]);
			}
		}
		printf("The minimum cutting is %d.\n",DP[0][N-1]);
	}
	return 0;
}

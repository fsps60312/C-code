#include<cstdio>
#include<cstdlib>
#include<vector>
#define LL long long
using namespace std;
LL DP[100][100][100][2][2];//row,l,r,touch l,touch r
LL RANGEN[50][50];
LL SUM00[51][51],SUM01[51][51],SUM10[51][51],SUM11[51][51];
void cal_rangen(int R,int C)
{
	for(int i1=0;i1<R;i1++)
	{
		for(int i2=0;i2<C;i2++)
		{
			for(int i3=i2+1;i3<=C;i3++)
			{
				for(int i4=0;i4<4;i4++)
				{
					DP[i1][i2][i3][i4/2][i4%2]=0;
				}
			}
		}
	}
	for(int i1=1;i1<C;i1++)
	{
		for(int i2=i1+1;i2<C;i2++)
		{
			DP[0][i1][i2][0][0]=1;
		}
	}
	for(int i1=1;i1<C;i1++)DP[0][i1][C][0][1]=DP[0][0][i1][1][0]=1;
	DP[0][0][C][1][1]=1;
	RANGEN[1][C]=1;
	for(int r=1;r<R;r++)
	{
		//cal 0 0:complete
		for(int i1=0;i1<=C;i1++)
		{
			SUM00[i1][0]=DP[r-1][i1][0][0][0];
			SUM01[i1][0]=DP[r-1][i1][0][0][1];
			SUM10[i1][0]=DP[r-1][i1][0][1][0];
			SUM11[i1][0]=DP[r-1][i1][0][1][1];
			for(int i2=1;i2<=C;i2++)
			{
				SUM00[i1][i2]=SUM00[i1][i2-1]+DP[r-1][i1][i2][0][0];
				SUM01[i1][i2]=SUM01[i1][i2-1]+DP[r-1][i1][i2][0][1];
				SUM10[i1][i2]=SUM10[i1][i2-1]+DP[r-1][i1][i2][1][0];
				SUM11[i1][i2]=SUM11[i1][i2-1]+DP[r-1][i1][i2][1][1];
			}
		}
		for(int i1=1;i1<C;i1++)
		{
			for(int i2=i1+1;i2<C;i2++)
			{
				for(int i3=i1;i3<i2;i3++)
				{
					DP[r][i1][i2][0][0]+=SUM00[i3][i2]-SUM00[i3][i3];
					/*for(int i4=i3+1;i4<=i2;i4++)
					{
						DP[r][i1][i2][0][0]+=DP[r-1][i3][i4][0][0];
					}*/
				}
			}
		}
		//i1=0
		for(int i2=1;i2<C;i2++)
		{
			for(int i3=1;i3<i2;i3++)
			{
				DP[r][0][i2][1][0]+=SUM00[i3][i2]-SUM00[i3][i3];
				/*for(int i4=i3+1;i4<=i2;i4++)
				{
					DP[r][0][i2][1][0]+=DP[r-1][i3][i4][0][0];
				}*/
			}
		}
		//r,r
		for(int i1=0;i1<C;i1++)
		{
			for(int i2=i1+1;i2<C;i2++)
			{
				for(int i3=0;i3<=i1;i3++)
				{
					DP[r][i1][i2][1][0]+=SUM10[i3][i2]-SUM10[i3][i1];
					/*for(int i4=i1+1;i4<=i2;i4++)
					{
						DP[r][i1][i2][1][0]+=DP[r-1][i3][i4][1][0];
					}*/
				}
			}
		}
		for(int i1=1;i1<C;i1++)
		{//i2=C
			for(int i3=i1;i3<C;i3++)
			{
				DP[r][i1][C][0][1]+=SUM00[i3][C]-SUM00[i3][i3];
				/*for(int i4=i3+1;i4<=C;i4++)
				{
					DP[r][i1][C][0][1]+=DP[r-1][i3][i4][0][0];
				}*/
			}
		}
		for(int i1=1;i1<C;i1++)
		{
			for(int i2=i1+1;i2<=C;i2++)
			{
				for(int i3=i1;i3<i2;i3++)
				{
					DP[r][i1][i2][0][1]+=SUM01[i3][C]-SUM01[i3][i2-1];
					/*for(int i4=i2;i4<=C;i4++)
					{
						DP[r][i1][i2][0][1]+=DP[r-1][i3][i4][0][1];
					}*/
				}
			}
		}
		for(int i3=1;i3<C;i3++)
		{
			DP[r][0][C][1][1]+=SUM00[i3][C-1]-SUM00[i3][i3];
			/*for(int i4=i3+1;i4<C;i4++)
			{
				DP[r][0][C][1][1]+=DP[r-1][i3][i4][0][0];
			}*/
		}
		//i1=0
		for(int i2=1;i2<=C;i2++)
		{
			for(int i3=1;i3<i2;i3++)
			{
				DP[r][0][i2][1][1]+=SUM01[i3][C]-SUM01[i3][i2-1];
				/*for(int i4=i2;i4<=C;i4++)
				{
					DP[r][0][i2][1][1]+=DP[r-1][i3][i4][0][1];
				}*/
			}
		}
		for(int i1=0;i1<C;i1++)//r,r
		{//i2=C
			for(int i3=0;i3<=i1;i3++)
			{
				DP[r][i1][C][1][1]+=SUM10[i3][C-1]-SUM10[i3][i1];
				/*for(int i4=i1+1;i4<C;i4++)
				{
					DP[r][i1][C][1][1]+=DP[r-1][i3][i4][1][0];
				}*/
			}
		}
		for(int i1=0;i1<C;i1++)
		{
			for(int i2=i1+1;i2<=C;i2++)
			{
				for(int i3=0;i3<=i1;i3++)
				{
					DP[r][i1][i2][1][1]+=SUM11[i3][C]-SUM11[i3][i2-1];
					/*for(int i4=i2;i4<=C;i4++)
					{
						DP[r][i1][i2][1][1]+=DP[r-1][i3][i4][1][1];
					}*/
				}
			}
		}
		LL &ans=RANGEN[r+1][C];
		ans=0;
		for(int i1=0;i1<C;i1++)
		{
			for(int i2=i1+1;i2<=C;i2++)
			{
				ans+=DP[r][i1][i2][1][1];
			}
		}
		//printf(" %d %d\n",r+1,C);
	}
}
LL get_ans(int len)
{
	LL ans=0;
	if(len%2)return 0;
	len/=2;
	for(int i=1;i<len;i++)ans+=RANGEN[i][len-i];
	return ans;
}
int N;
int main()
{
	for(int r=1;r<50;r++)
	{
		cal_rangen(r,50-r);
		for(int c=1;c<=r;c++)
		{
			RANGEN[50-r][c]=RANGEN[c][50-r];
			//printf(" %d %d,",c,50-r);
		}
	}
	/*for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=5;j++)
		{
			printf(" %lld",RANGEN[i][j]);
		}
		printf("\n");
	}*/
	int kase=1;
	while(scanf("%d",&N)==1)
	{
		printf("Case #%d: %lld\n",kase++,get_ans(N));
	}
	return 0;
}

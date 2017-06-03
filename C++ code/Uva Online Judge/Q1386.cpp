#include<cstdio>
#define abs(x) (x>0?x:-(x))
int N,M,D,K,A[500];
struct Matrix
{
	int v[500][500];
	void init()
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(abs(i-j)<=D||N-abs(i-j)<=D)v[i][j]=1;
				else v[i][j]=0;
			}
		}
	}
}
int main()
{
	while(scanf("%d%d%d%d",&N,&M,&D,&K)==4)
	{
		for(int i=0;i<N;i++)scanf("%d",A+i);
	}
	return 0;
}

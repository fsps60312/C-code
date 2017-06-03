#include<cstdio>
int N,M,K,SUM[3][1001][1001];
int Sum(const int &k,const int &y1,const int &x1,const int &y2,const int &x2)
{
	return SUM[k][y2][x2]-SUM[k][y2][x1-1]-SUM[k][y1-1][x2]+SUM[k][y1-1][x1-1];
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&M,&N,&K);
	for(int k=0;k<3;k++)
	{
		for(int i=0;i<=M;i++)SUM[k][i][0]=0;
		for(int i=0;i<=N;i++)SUM[k][0][i]=0;
	}
	for(int i=1;i<=M;i++)
	{
		for(int j=1;j<=N;j++)
		{
			for(int k=0;k<3;k++)SUM[k][i][j]=0;
			static bool valid;valid=false;
			while(!valid)
			{
				valid=true;
				static char c;
				scanf("%c",&c);
				switch(c)
				{
					case'J':SUM[0][i][j]=1;break;
					case'O':SUM[1][i][j]=1;break;
					case'I':SUM[2][i][j]=1;break;
					default:valid=false;break;
				}
			}
		}
	}
	for(int i=1;i<=M;i++)for(int j=1;j<=N;j++)for(int k=0;k<3;k++)
	{
		SUM[k][i][j]=SUM[k][i-1][j]+SUM[k][i][j-1]-SUM[k][i-1][j-1]+SUM[k][i][j];
	}
//	for(int k=0;k<3;k++)
//	{
//		printf("k=%d\n",k);
//		for(int i=1;i<=M;i++)
//		{
//			for(int j=1;j<=N;j++)
//			{
//				printf("%4d",SUM[k][i][j]);
//			}
//			puts("");
//		}
//	}
	while(K--)
	{
		static int y1,x1,y2,x2;
		scanf("%d%d%d%d",&y1,&x1,&y2,&x2);
		printf("%d %d %d\n",Sum(0,y1,x1,y2,x2),Sum(1,y1,x1,y2,x2),Sum(2,y1,x1,y2,x2));
	}
	return 0;
}

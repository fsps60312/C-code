#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int SZ;
//vector<int> INTE[60];
int TMAT[3][60][60],ROAD[60][60];
void init(){SZ=0;}
void init(int sz)
{
	while(SZ<=sz)
	{
		//INTE[SZ].clear();
		for(int i=0;i<SZ;i++)
		{
			ROAD[i][SZ]=ROAD[SZ][i]=0;
		}
		SZ++;
	}
}
void copyto(int *x,int *y)
{
	for(int i1=0;i1<SZ;i1++)
	{
		for(int i2=0;i2<SZ;i2++)
		{
			y[i1*60+i2]=x[i1*60+i2];
		}
	}
}
void addto(int *x,int *y)
{
	for(int i1=0;i1<SZ;i1++)
	{
		for(int i2=0;i2<SZ;i2++)
		{
			y[i1*60+i2]+=x[i1*60+i2];
		}
	}
}
void calways(int *x,int *y)
{
	for(int i1=0;i1<SZ;i1++)
	{
		for(int i2=0;i2<SZ;i2++)
		{
			y[i1*60+i2]=0;
			for(int k=0;k<SZ;k++)
			{
				y[i1*60+i2]+=x[i1*60+k]*ROAD[k][i2];
			}
		}
	}
}
void *solve()
{
	int *x=&TMAT[0][0][0],*pre=&TMAT[1][0][0],*now=&TMAT[2][0][0];
	copyto(&ROAD[0][0],x);
	copyto(&ROAD[0][0],pre);
	for(int k=2;k<=SZ;k++)
	{
		calways(pre,now);
		addto(now,x);
		int *t=pre;
		pre=now,now=t;
	}
	for(int k=0;k<SZ;k++)
	{
		calways(pre,now);
		for(int i1=0;i1<SZ;i1++)
		{
			for(int i2=0;i2<SZ;i2++)
			{
				if(now[i1*60+i2])x[i1*60+i2]=-1;
			}
		}
		int *t=pre;
		pre=now,now=t;
	}
	return x;
}
int main()
{
	int kase=0,m;
	while(scanf("%d",&m)==1)
	{
		init();
		while(m--)
		{
			int a,b;scanf("%d%d",&a,&b);
			init(a);init(b);
			ROAD[a][b]=1;
		}
		solve();
		printf("matrix for city %d\n",kase++);
		for(int i1=0;i1<SZ;i1++)
		{
			printf("%d",TMAT[0][i1][0]);
			for(int i2=1;i2<SZ;i2++)
			{
				printf(" %d",TMAT[0][i1][i2]);
			}
			printf("\n");
		}
	}
	return 0;
}

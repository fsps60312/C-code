#include<cstdio>
#include<cstdlib>
#include<vector>
#define max(x,y) x>y?x:y
using namespace std;
int C,R,Q,FEAST[81];
struct Pair
{
	int x,y;
	Pair operator+(Pair a){return (Pair){x+a.x,max(y,a.y)};}
	bool operator<(Pair a){return x+y<a.x+a.y;}
};
Pair MAT[81][81];
void swap(int &a,int &b){a^=b^=a^=b;}
void setMAT(int i,int j,int dis)
{
	if(i>j)swap(i,j);
	MAT[i][j]=(Pair){dis,max(FEAST[i],FEAST[j])};
}
Pair getMAT(int i,int j)
{
	if(i>j)swap(i,j);
	return MAT[i][j];
}
void getmin(Pair &a,Pair b){if(b<a)a=b;}
void pre_cal()
{
	for(int k=1;k<=C;k++)
	{
		for(int i=1;i<=C;i++)
		{
			for(int j=i+1;j<=C;j++)
			{
				getmin(MAT[i][j],getMAT(i,k)+getMAT(k,j));
			}
		}
	}
}
int main()
{
	int kase=1;
	while(scanf("%d%d%d",&C,&R,&Q)==3&&(C||R||Q))
	{
		for(int i=1;i<=C;i++)
		{
			for(int j=i;j<=C;j++)MAT[i][j]=(Pair){1000000000,0};
			scanf("%d",&FEAST[i]);
		}
		while(R--)
		{
			int a,b,dis;scanf("%d%d%d",&a,&b,&dis);
			setMAT(a,b,dis);
		}
		pre_cal();
		if(kase>1)printf("\n");
		printf("Case #%d\n",kase++);
		while(Q--)
		{
			int a,b;scanf("%d%d",&a,&b);
			Pair p=getMAT(a,b);
			if(p.x==1000000000)printf("-1\n");
			else printf(":%d %d\n",p.x,p.y);
		}
	}
	return 0;
}

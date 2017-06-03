#include<cstdio>
#include<cstdlib>
int MAT[21][21];
bool readin()
{
	for(int i=1;i<=20;i++)for(int j=i+1;j<=20;j++)MAT[i][j]=1000000000;
	for(int i=1;i<20;i++)
	{
		int k;if(scanf("%d",&k)!=1)return false;
		while(k--)
		{
			int j;scanf("%d",&j);
			MAT[i][j]=1;
		}
	}
	return true;
}
void getmin(int &a,int b){if(b<a)a=b;}
int getMAT(int i,int j)
{
	if(i>j)i^=j^=i^=j;
	return MAT[i][j];
}
void solve()
{
	for(int k=1;k<=20;k++)
	{
		for(int i=1;i<=20;i++)
		{
			for(int j=i+1;j<=20;j++)
			{
				getmin(MAT[i][j],getMAT(i,k)+getMAT(k,j));
			}
		}
	}
}
int main()
{
	int kase=1;
	while(readin())
	{
		solve();
		printf("Test Set #%d\n",kase++);
		int q;scanf("%d",&q);
		while(q--)
		{
			int a,b;scanf("%d%d",&a,&b);
			printf("%2d to %2d: %d\n",a,b,getMAT(a,b));
		}
		printf("\n");
	}
	return 0;
}

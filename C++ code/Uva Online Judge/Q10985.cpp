#include<cstdio>
#include<cstdlib>
int N,MAT[120][120];
void setMAT(int i,int j){if(i>j)i^=j^=i^=j;MAT[i][j]=1;}
int getMAT(int i,int j){if(i>j)i^=j^=i^=j;return MAT[i][j];}
void getmin(int &a,int b){if(b<a)a=b;}
int solve()
{
	for(int k=0;k<N;k++)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=i;j<N;j++)
			{
				getmin(MAT[i][j],getMAT(i,k)+getMAT(k,j));
			}
		}
	}
	int ans=0;
	for(int i=0;i<N;i++)
	{
		for(int j=i;j<N;j++)
		{
			if(MAT[i][j]!=120&&MAT[i][j]>ans)ans=MAT[i][j];
			printf("\t%d",MAT[i][j]);
		}
		printf("\n");
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	int t,kase=1;scanf("%d",&t);
	while(t--)
	{
		int m;scanf("%d%d",&N,&m);
		for(int i=0;i<N;i++){for(int j=i;j<N;j++)MAT[i][j]=120;MAT[i][i]=0;}
		while(m--)
		{
			int a,b;scanf("%d%d",&a,&b);
			setMAT(a,b);
		}
		printf("Case #%d: %d\n",kase++,solve());
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
int N,ORI[120][120],MAT[120][120],CNT[120][120];
void setORI(int i,int j){if(i>j)i^=j^=i^=j;ORI[i][j]=1;}
int getORI(int i,int j){if(i>j)i^=j^=i^=j;return ORI[i][j];}
int getMAT(int i,int j){if(i>j)i^=j^=i^=j;return MAT[i][j];}
void getmax(int &a,int b){if(b>a)a=b;}
int solve()
{
	for(int i=0;i<N;i++)for(int j=i;j<N;j++)MAT[i][j]=ORI[i][j];
	for(int k=0;k<N;k++)
	{
		for(int i=0;i<N;i++)
		{
			if(i==k)continue;
			for(int j=i;j<N;j++)
			{
				if(j==k)continue;
				int a=getMAT(i,k)+getORI(k,j);
				if(a<MAT[i][j])
				{
					CNT[i][j]=1;
					MAT[i][j]=a;
				}
				else if(a==MAT[i][j])CNT[i][j]++;
			}
		}
	}
	int ans=0;//,now=0;
	for(int i=0;i<N;i++)
	{
		for(int k=0;k<i;k++)printf("\t");
		for(int j=i;j<N;j++)
		{
			//if(MAT[i][j]>now)now=MAT[i][j],ans=0;
			//if(MAT[i][j]==now)ans+=CNT[i][j];
			getmax(ans,MAT[i][j]*CNT[i][j]);
			printf("\t%d,%d",MAT[i][j],CNT[i][j]);
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
		for(int i=0;i<N;i++){for(int j=i;j<N;j++)ORI[i][j]=120,CNT[i][j]=0;ORI[i][i]=0;}
		while(m--)
		{
			int a,b;scanf("%d%d",&a,&b);
			setORI(a,b);
		}
		printf("Case #%d: %d\n",kase++,solve());
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
#define min(x,y) (x)<(y)?(x):(y)
int N,M;
char CASENAME[13];
int LAD[119][15][15],VIS[119][15];
int query(int f,int lad)
{
	int &ans=VIS[f][lad];
	if(f==N)return ans=0;
	if(ans!=-1)return ans;
	ans=2147483647;
	for(int i=0;i<M;i++)
	{
		ans=min(ans,query(f+1,i)+LAD[f][lad][i]);
	}
	ans+=2;
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%s%d%d",CASENAME,&N,&M)==3)
	{
		printf("%s\n",CASENAME);
		N--;
		for(int i=0;i<N;i++)
		{
			for(int s=0;s<M;s++)
			{
				VIS[i][s]=-1;
				for(int e=0;e<M;e++)
				{
					scanf("%d",&LAD[i][s][e]);
				}
			}
		}
		int ans=2147483647;
		for(int i=0;i<M;i++){ans=min(ans,query(0,i));}
		printf("%d\n",ans);
	}
	return 0;
}

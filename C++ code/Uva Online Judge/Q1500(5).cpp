#include<cstdio>
int T,N,A[50],DP[51][51][51];
int getDP(int a,int b,int c)
{
	if(a<0||b<0||c<0)return true;
//	printf("%d %d %d\n",a,b,c);
	int &dp=DP[a][b][c];
	if(dp!=-1)return dp;
	if(!getDP(a-1,b,c))return dp=true;
	if(!getDP(a+1,b-1,c))return dp=true;
//	if(b+2<=c&&!getDP(a,b-1,c+1))return dp=true;
	if(!getDP(a,b+1,c-1))return dp=true;
	if(!getDP(a-2,b+1,c))return dp=true;
	if(!getDP(a-1,b-1,c+1))return dp=true;
	if(!getDP(a-1,b+1,c-1))return dp=true;
	if(b>=2&&!getDP(a,b-2+1,c))return dp=true;
	if(b&&c&&!getDP(a,b-1,c-1+1))return dp=true;
	if(!getDP(a,b+1,c-2))return dp=true;
	return dp=false;
}
int main()
{
	for(int i=0;i<=50;i++)for(int j=0;j<=50;j++)for(int k=0;k<=50;k++)DP[i][j][k]=-1;
	DP[0][0][0]=false;
//	int a,b,c;while(scanf("%d%d%d",&a,&b,&c)==3)printf("%d\n",getDP(a,b,c));
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&N);
		int a=0,b=0,c=0;
		for(int i=0;i<N;i++)
		{
			int &v=A[i];
			scanf("%d",&v);
			if(v==1)a++;
			else if(v&1)c++;
			else b++;
		}
		printf("Case #%d: %s\n",kase++,getDP(a,b,c)?"Alice":"Bob");
	}
	return 0;
}

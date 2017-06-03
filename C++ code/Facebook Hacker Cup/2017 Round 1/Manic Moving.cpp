#include<cstdio>
#include<cassert>
using namespace std;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
const int INF=2147483647/2;
int S[5001],D[5001];
int EDGE[100][100];
int DP[5001][3][2];
int GetDP(const int i,const int j,const int k)
{
	int &dp=DP[i][j][k];
	if(dp!=-1)return dp;
	if(i==0&&j==0&&k==1)return dp=0;
	if(i==0)return dp=INF;
//	if(j==0&&k==0)//impossible!
	if(j==0&&k==1)
	{
		dp=INF;
		getmin(dp,GetDP(i,1,0)+EDGE[S[i]][D[i]]);
		getmin(dp,GetDP(i,1,1)+EDGE[D[i-1]][D[i]]);
		return dp;
	}
	if(j==1&&k==0)
	{
		dp=INF;
//		getmin(dp,GetDP(i-1,0,0)+EDGE[S[i-1]][S[i]]);//impossible!
		getmin(dp,GetDP(i-1,0,1)+EDGE[D[i-1]][S[i]]);
		return dp;
	}
	if(j==1&&k==1)
	{
		dp=INF;
		getmin(dp,GetDP(i,2,0)+EDGE[S[i]][D[i-1]]);
		//impossible!
		return dp;
	}
	if(j==2&&k==0)
	{
		dp=INF;
		getmin(dp,GetDP(i-1,1,0)+EDGE[S[i-1]][S[i]]);
		if(i-2>=0)getmin(dp,GetDP(i-1,1,1)+EDGE[D[i-2]][S[i]]);
		return dp;
	}
//	if(j==2&&k==1)//impossible!
	printf("(%d,%d,%d)\n",i,j,k);
	assert(0);return -1;
}
int N,M,K;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&M,&K);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)EDGE[i][j]=INF;
		for(int i=0;i<N;i++)EDGE[i][i]=0;
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),--a,--b;
			getmin(EDGE[a][b],c);
			getmin(EDGE[b][a],c);
		}
		for(int i=1;i<=K;i++)scanf("%d%d",&S[i],&D[i]),--S[i],--D[i];
		for(int m=0;m<N;m++)
		{
			for(int a=0;a<N;a++)
			{
				for(int b=0;b<N;b++)getmin(EDGE[a][b],EDGE[a][m]+EDGE[m][b]);
			}
		}
//		for(int i=0;i<N;i++)
//		{
//			for(int j=0;j<N;j++)printf("%d ",EDGE[i][j]);
//			printf("\n");
//		}
		D[0]=0;
		for(int i=0;i<=K;i++)for(int j=0;j<3;j++)for(int k=0;k<2;k++)DP[i][j][k]=-1;
		static int kase=0;
		const int ans=GetDP(K,0,1);//a_i loaded, b_(i-j) delivered, now at k=0?a_i:b_(i-j)
//		for(int i=0;i<=K;i++)for(int j=0;j<3;j++)for(int k=0;k<2;k++)printf("(%d,%d,%d)=%d\n",i,j,k,DP[i][j][k]);
		printf("Case #%d: %d\n",++kase,ans==INF?-1:ans);
	}
	return 0;
}

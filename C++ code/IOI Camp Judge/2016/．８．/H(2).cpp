#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,P[3001];
int DP[3001][3001],MN[3001][3001];
//int GetDP(const int a,const int b)
//{
//	int &ans=DP[a][b];
//	if(ans!=-1)return ans;
//	assert(a>0&&b>0);
//	ans=INF;
//	assert(a<b);
//	if(a<b-1)getmin(ans,GetDP(a,b-1)+abs(P[b]-P[a]));
//	else
//	{
//		getmin(ans,MN[b-2][b-1]+abs(P[b]-P[b-1]));
//	}
//	return ans;
//}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		P[0]=0;
		for(int i=1;i<=N;i++)scanf("%d",&P[i]);
		DP[0][0]=0;
		for(int j=1;j<=N;j++)
		{
			MN[0][j]=DP[0][j]=DP[0][j-1]+P[j];
			for(int i=1;i<j-1;i++)MN[i][j]=min(MN[i-1][j],DP[i][j]=DP[i][j-1]+abs(P[i]-P[j]));
			if(1<j)MN[j-1][j]=min(MN[j-2][j],DP[j-1][j]=MN[j-2][j-1]+abs(P[j]-P[j-1]));
		}
		int ans=INF;
		for(int i=0;i<N;i++)getmin(ans,DP[i][N]);
		printf("%d\n",ans);
	}
	return 0;
}

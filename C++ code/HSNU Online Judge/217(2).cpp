#include<cstdio>
#include<vector>
using namespace std;
bool getmax(int &a,const int &b){if(b>a){a=b;return true;}return false;}
const int INF=2147483647;
int T,N,K,A,B;
char LINE[5001];
int S[5000],DP[5000][500],PRE[5000][500];
int Get(const int &i,const int &k)
{
	if(i<0)return (i==-1&&k==-1)?0:-INF;
	if((i+1)/A<k+1)return -INF;
	if((i+1+B-1)/B>k+1)return -INF;
	int &dp=DP[i][k];
	if(dp!=-INF)return dp;
	int &pre=PRE[i][k];
	for(int j=A;j<=B;j++)if(getmax(dp,Get(i-j,k-1)))pre=i-j;
	if(dp!=-INF)dp+=(k+1)*S[i];
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&N,&K,&A,&B);
		scanf("%s",LINE);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)for(int j=0;j<K;j++)DP[i][j]=-INF;
		int ans=Get(N-1,K-1);
		static int kase=1;
		printf("Case #%d:\n",kase++);
		if(ans==-INF)puts("Sorry, you're milk cheese.");
		else
		{
			printf("%d\n",ans);
			vector<int>v;
			for(int i=K-1,pre=N-1;i>=0;i--)
			{
				v.push_back(pre);
				pre=PRE[pre][i];
			}
			for(int i=v.size()-1,idx=0;i>=0;i--)
			{
				int &vv=v[i];
				for(;idx<=vv;idx++)printf("%c",LINE[idx]);
				puts("");
			}
		}
	}
	return 0;
}

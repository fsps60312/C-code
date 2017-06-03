#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
inline bool getmax(int &a,const int b){if(a<b){a=b;return true;}return false;}
int N,K;
int S[601][601],SUM[601][601];
int Sum(const int s1,const int s2,const int t1,const int t2){return SUM[s2][t2]-SUM[s2][t1-1]-SUM[s1-1][t2]+SUM[s1-1][t1-1];}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("kon9b.in","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		assert(2<=N&&N<=600&&K<N&&1<=K&&K<=50);
		for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)S[i][j]=SUM[i][j]=0;
		for(int i=1;i<=N;i++)for(int j=i+1;j<=N;j++)scanf("%d",&S[i][j]);
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)SUM[i][j]=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1]+S[i][j];
		static int dp[51][601],pre[51][601];
		for(int i=0;i<=K;i++)for(int j=1;j<=N;j++)dp[i][j]=(i==0?0:-1);
		for(int i=1;i<N;i++)
		{
			for(int j=0;j<K;j++)
			{
				for(int k=1;k<=i;k++)
				{
					if(getmax(dp[j+1][i+1],dp[j][k]+Sum(k,i,i+1,N)))
					{
						pre[j+1][i+1]=k;
					}
				}
			}
		}
		vector<int>ans;
		int p=-1;
		for(int i=2,mx=-1;i<=N;i++)if(getmax(mx,dp[K][i]))p=i;
		assert(p!=-1);
		for(int i=K;i>=1;i--)
		{
			ans.push_back(p-1);
			p=pre[i][p];
		}
//		assert(p==1);
		for(int i=(int)ans.size()-1;i>=0;i--)
		{
			printf("%d",ans[i]);
			if(i)putchar(' ');
		}
		puts("");
	}
	return 0;
}

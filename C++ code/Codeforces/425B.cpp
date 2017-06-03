#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,M,K,S[100][100];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)scanf("%d",&S[i][j]);
		int ans=INF;
		if(N<=10)
		{
			for(int s=0;s<(1<<N);s++)
			{
				int sum=0;
				for(int i=0;i<M;i++)
				{
					int cnt=0;
					for(int j=0;j<N;j++)if(S[j][i]!=((s&(1<<j))>>j))cnt++;
					sum+=min(cnt,N-cnt);
				}
				getmin(ans,sum);
			}
		}
		else
		{
			for(int i=0;i<N;i++)
			{
				int sum=0;
				for(int j=0;j<N;j++)
				{
					int cnt=0;
					for(int k=0;k<M;k++)if(S[j][k]!=S[i][k])cnt++;
					sum+=min(cnt,M-cnt);
				}
				getmin(ans,sum);
			}
		}
		if(ans>K)ans=-1;
		printf("%d\n",ans);
	}
	return 0;
}

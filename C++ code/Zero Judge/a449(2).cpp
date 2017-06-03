#include<cstdio>
#include<queue>
#include<cassert>
#include<set>
using namespace std;
bool getmax(int &a,const int b){if(b>a){a=b;return true}return false;}
int N,K,M,S[2000];
int SUM[2000][2000];
int DP[12][2000][2000];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&K,&M);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=1;i<N;i++)SUM[i][i-1]=0;
	for(int i=0;i<N;i++)
	{
		priority_queue<int>pq;
		for(int j=i,sum=0,cnt=0;j<N;j++)
		{
			pq.push(S[j]),sum+=S[j],cnt++;
			if(sum>M)sum-=pq.top(),cnt--,pq.pop();
			assert(sum<=M);
			SUM[i][j]=cnt;
		}
	}
	for(int i=0;i<N;i++)DP[0][i]=SUM[0][i];
	for(int bus=1;bus<K;bus++)
	{
		for(int i=0;i<N;i++)
		{
			DP[bus][i]=DP[bus-1][i];
			for(int j=1;j<=i;j++)getmax(DP[bus][i],DP[bus-1][j-1]+SUM[j][i]);
		}
	}
	printf("%d\n",DP[K-1][N-1]);
	return 0;
}

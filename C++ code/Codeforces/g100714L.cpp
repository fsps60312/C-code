#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
const int INF=2147483647;
int N,S[400];
vector<vector<vector<int> > >DP;
void ResizeDP(int i,int j,int k)
{
	DP.clear();
	DP.resize(i);
	for(auto &a:DP)
	{
		a.resize(j);
		for(auto &b:a)b.resize(k,INF);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		int sum=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),sum+=S[i];
		if(N>=55)ResizeDP(N,56,max(56,sum));
		else ResizeDP(N,sum/N+N+10,max(sum,sum/N+N+10));
//		printf("sum=%d\n",sum);
		for(int i=0;i<(int)DP[0].size();i++)DP[0][i][sum]=abs(i-S[0]);
		for(int i=0;i+1<N;i++)
		{
			for(int j=0;j<(int)DP[i].size();j++)for(int k=j;k<=sum;k++)
			{
				const int &v=DP[i][j][k];
				if(v!=INF)
				{
					getmin(DP[i+1][j][k-j],v+abs(j-S[i+1]));
					if(j-1>=0)getmin(DP[i+1][j-1][k-j],v+abs((j-1)-S[i+1]));
					if(j+1<(int)DP[i].size())getmin(DP[i+1][j+1][k-j],v+abs((j+1)-S[i+1]));
				}
			}
		}
		int ans=INF;
		for(int i=0;i<(int)DP[N-1].size();i++)getmin(ans,DP[N-1][i][i]);
		assert(ans!=INF);
		assert(ans%2==0);
		printf("%d\n",ans/2);
	}
	return 0;
}

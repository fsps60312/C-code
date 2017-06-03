#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
int T,N,M;
vector<int>ET[80000],EE[80000];
int CNT[80001];
bool VIS[80000];
void Dfs(const int u,int *tmp,const int gender)
{
	if(VIS[u])return;
	VIS[u]=true;
	tmp[gender]++;
	for(int i=0;i<EE[u].size();i++)Dfs(EE[u][i],tmp,gender);
	for(int i=0;i<ET[u].size();i++)Dfs(ET[u][i],tmp,gender^1);
}
bool DP[2][160001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)ET[i].clear(),EE[i].clear(),VIS[i]=false;
		for(int i=1;i<=N;i++)CNT[i]=0;
		int breed=0;
		while(M--)
		{
			static int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			if(c==0)EE[a].push_back(b),EE[b].push_back(a);
			else if(c==1)ET[a].push_back(b),ET[b].push_back(a),breed++;
			else assert(0);
		}
		for(int i=0;i<N;i++)if(!VIS[i])
		{
			static int tmp[2];
			tmp[0]=tmp[1]=0;
			Dfs(i,tmp,0);
			CNT[abs(tmp[0]-tmp[1])]++;
		}
		for(int i=0;i<=N*2;i++)DP[0][i]=false;
		DP[0][N]=true;
		int d=0;
		for(int i=1;i<=N;i++)
		{
			const int cnt=CNT[i];
			if(cnt==0)continue;
			for(int k=0;k<=N*2;k++)DP[d^1][k]=false;
			for(int j=0;(1<<j)<=cnt;j++)if(cnt&(1<<j))
			{
				for(int k=0;k<=N*2;k++)
				{
					if(!DP[d][k])continue;
					if(k-(1<<j)*i>=0)DP[d^1][k-(1<<j)*i]=true;
					if(k+(1<<j)*i<=N*2)DP[d^1][k+(1<<j)*i]=true;
				}
				for(int k=0;k<=N*2;k++)DP[d][k]|=DP[d^1][k];
			}
			d^=1;
		}
		for(int i=N;;i++)
		{
			assert(i<=N*2);
			if(DP[d][i])
			{
				assert(i%2==0);
//				printf("i=%d\n",i);
				int a=i/2,b=N-a;
				printf("%d\n",a*b-breed);
				break;
			}
		}
	}
	return 0;
}

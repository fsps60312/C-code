#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int N,M;
vector<int>ET[100000];
int PRE[100000],PRE_CNT,LOW[100000];
LL ANS[100000];
LL Dfs(const int &u,const int &fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	ANS[u]=0LL;
	LL sum=1LL,scc=0LL,ta;
	for(int i=0;i<ET[u].size();i++)
	{
		const int &nxt=ET[u][i];
		if(nxt==fa)continue;
		if(!PRE[nxt])
		{
			sum+=(ta=Dfs(nxt,u));
			LOW[u]=min(LOW[u],LOW[nxt]);
			if(LOW[nxt]>=PRE[u])scc+=ta,ANS[u]+=ta*(N-1-ta);
		}
		else LOW[u]=min(LOW[u],PRE[nxt]);
	}
	ta=N-scc-1;
	ANS[u]+=ta*(N-1-ta);
	return sum;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear(),PRE[i]=0;
	PRE_CNT=0;
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b);
		a--,b--;
		ET[a].push_back(b);
		ET[b].push_back(a);
	}
	for(int i=0;i<N;i++)
	{
		vector<int>&e=ET[i];
		sort(e.begin(),e.end());
		e.resize(unique(e.begin(),e.end())-e.begin());
	}
	Dfs(0,-1);
	for(int i=0;i<N;i++)printf("%lld\n",ANS[i]+2LL*(N-1));
	return 0;
}

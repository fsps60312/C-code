#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<set>
using namespace std;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
void AddEdge(vector<int>*et,const int a,const int b){et[a].push_back(b),et[b].push_back(a);}
int N,M,L,PRE[100000];
bool IS_CUT[100000];
vector<int>ET[100000],EC[200000],SCC[100000],SZ[200000];
int SCC_CNT;
int Dfs(const int u,const int parent,int &pre_cnt,vector<int>&stk)
{
	int low=PRE[u]=++pre_cnt,ch_cnt=0;
	stk.push_back(u);
	IS_CUT[u]=false;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		const int nxt=ET[u][i];
		if(!PRE[nxt])
		{
			const int nxt_low=Dfs(nxt,u,pre_cnt,stk);
			getmin(low,nxt_low),++ch_cnt;
			if(nxt_low>=PRE[u])
			{
				IS_CUT[u]=true;
				for(;;)
				{
					const int v=stk.back();
					SCC[SCC_CNT].push_back(v);
					if(v==u)break;
					stk.pop_back();
				}
				++SCC_CNT;
			}
		}
		else getmin(low,PRE[nxt]);
	}
	if(parent==-1&&ch_cnt<=1)IS_CUT[u]=false;
	if(parent==-1)stk.pop_back();
//	printf("u=%d,pre=%d,low=%d,is_cut=%d\n",u+1,PRE[u],low,IS_CUT[u]);
	return low;
}
int GetSz(const int parent,const int parent_ch_id)
{
	int &ans=SZ[parent][parent_ch_id];
	if(ans!=-1)return ans;
	const int u=EC[parent][parent_ch_id];
	ans=(u<N?1:(int)(SCC[u-N].size()-EC[u].size()));
	for(int i=0;i<(int)EC[u].size();i++)if(EC[u][i]!=parent)ans+=GetSz(u,i);
	return ans;
}
long long Solve(const int u)
{
	long long ans=2LL*(N-1LL);
	if(!IS_CUT[u])return ans;
	long long sum=0LL;
	printf("u=%d\n",u+1);
	for(int i=0;i<(int)EC[u].size();i++)
	{
		const long long sz=GetSz(u,i);
		ans+=sum*sz*2LL;
		sum+=sz;
		printf(" sz=%lld\n",sz);
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EC[i].clear(),EC[N+i].clear(),SCC[i].clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),AddEdge(ET,--a,--b);
		{
			for(int i=0;i<N;i++)PRE[i]=0;
			SCC_CNT=0;
			int pre_cnt=0;
			vector<int>stk;
			Dfs(0,-1,pre_cnt,stk);
			assert(stk.empty());
		}
		for(int i=0;i<SCC_CNT;i++)
		{
			for(int j=0;j<(int)SCC[i].size();j++)
			{
				const int u=SCC[i][j];
				if(IS_CUT[u])EC[u].push_back(N+i),EC[N+i].push_back(u);
			}
		}
		for(int i=0;i<N+SCC_CNT;i++)SZ[i].clear(),SZ[i].resize(EC[i].size(),-1);
		for(int i=0;i<N;i++)printf("%lld\n",Solve(i));
	}
	return 0;
}
/*
5 6
2 1
2 3
1 3
2 4
2 5
4 5
*/

#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Bit
{
	int S[100001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)S[i]=0;}
	void Add(int i,const int val){for(;i<=N;i+=i&(-i))S[i]+=val;}
	int Query(int i){int ans=0;for(;i;i-=i&(-i))ans+=S[i];return ans;}
}BIT;
int N,S[100001],LOC[100001],L[100002],R[100002];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N*2;i++)scanf("%d",&S[i]),--S[i];
		for(int i=1;i<=N*2;i++)LOC[S[i]]=i;
		for(int i=0;i<=N*2;i++)R[i]=i+1,L[i+1]=i;
		BIT.Clear(N*2);
		for(int i=1;i<=N*2;i++)BIT.Add(i,1);
		vector<int>ans;
		for(int i=1;i<=N*2;i++)if(LOC[S[i]]==i)
		{
			int cur=i;
			for(;S[L[cur]]!=S[cur];)
			{
				ans.push_back(BIT.Query(L[cur]));
				swap(S[L[cur]],S[cur]),cur=L[cur];
			}
			BIT.Add(L[cur],-1),BIT.Add(cur,-1);
			R[L[L[cur]]]=R[cur];
			L[R[cur]]=L[L[cur]];
		}
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)printf("%d\n",ans[i]);
	}
	return 0;
}

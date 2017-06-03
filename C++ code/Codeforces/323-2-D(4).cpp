#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,T,S[100];
int Get(vector<int>&v,const int &mn,const int &mx)
{
	static int dp[10000];
	int ans=0;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]<mn||v[i]>mx)continue;
		int l=0,r=ans;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(v[i]>=dp[mid])l=mid+1;
			else r=mid;
		}
		dp[l]=v[i];
		if(l==ans)ans++;
	}
	return ans;
}
int Cnt(const int &v)
{
	int ans=0;
	for(int i=0;i<N;i++)if(S[i]==v)ans++;
	return ans;
}
int Solve()
{
	if(T<=N*2)
	{
		vector<int>v;
		for(int i=0;i<N*T;i++)v.push_back(S[i%N]);
		return Get(v,-INF,INF);
	}
	vector<int>e;
	for(int i=0;i<N;i++)e.push_back(S[i]);
	sort(e.begin(),e.end());
	e.resize(unique(e.begin(),e.end())-e.begin());
	vector<int>v;
	for(int i=0;i<N*N;i++)v.push_back(S[i%N]);
	int ans=0;
	for(int i=0;i<e.size();i++)
	{
		ans=max(ans,Get(v,-INF,e[i])+(T-2*N)*Cnt(e[i])+Get(v,e[i],INF));
	}
	return ans;
}
int main()
{
	while(scanf("%d%d",&N,&T)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		printf("%d\n",Solve());
	}
	return 0;
}

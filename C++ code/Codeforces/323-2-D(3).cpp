#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,T,MX,MN,S[100],DP[100],LEN[100][100];
vector<int>V;
int Get(int mn,int mx)
{
	vector<int>v;
	for(int i=0;i<N;i++)if(S[i]>=mn&&S[i]<=mx)v.push_back(S[i]);
	int ans=0;
	for(int i=0;i<v.size();i++)
	{
		int l=0,r=ans;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(v[i]>=DP[mid])l=mid+1;
			else r=mid;
		}
		DP[l]=v[i];
		if(l==ans)ans++;
	}
	return ans;
}
int Cnt(int v)
{
	int ans=0;
	for(int i=0;i<N;i++)if(S[i]==v)ans++;
	return ans;
}
int Solve()
{
	if(T==1)return Get(MN,MX);
	int dp[100][100][100];//dep,u,max
	map<int,int>idx;
	for(int i=0;i<V.size();i++)
	{
		idx[V[i]]=i;
		for(int j=i+1;j<V.size();j++)
		{
			LEN[i][j]=Get(V[i],V[j]);
			dp[i][j]=0;
		}
	}
	for(int u=0;u<V.size();u++)for(int mx=0;mx<V.size();mx++)dp[0][u][mx]=0;
	for(int dep=0;dep<V.size();dep++)
	{
		for(int u=1;u<V.size();u++)
		{
			
		}
	}
	for(int dep=0;dep<V.size()&&dep<T;dep++)ans=max(ans,dp[dep][V.size()-1]+(T-(dep+1))*);
	int ans=0;
	for(int i=0;i<N;i++)ans=max(ans,Get(MN,S[i])+(T-2)*Cnt(S[i])+Get(S[i],MX));
	return ans;
}
int main()
{
	while(scanf("%d%d",&N,&T)==2)
	{
		MX=-INF,MN=INF;
		V.clear();
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i]);
			MN=min(MN,S[i]),MX=max(MX,S[i]);
			V.push_back(S[i]);
		}
		sort(V.begin(),V.end());
		V.resize(unique(V.begin(),V.end())-V.begin());
		printf("%d\n",Solve());
		break;
	}
	return 0;
}

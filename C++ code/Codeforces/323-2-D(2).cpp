#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,T,MX,MN,S[20000001],DP[20000001];
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
	if(N*T<=20000000)
	{
		for(int i=N;i<N*T;i++)S[i]=S[i%N];
		N*=T;
		return Get(MN,MX);
	}
	int ans=0;
	for(int i=0;i<N;i++)ans=max(ans,Get(MN,S[i])+(T-2)*Cnt(S[i])+Get(S[i],MX));
	return ans;
}
int main()
{
	while(scanf("%d%d",&N,&T)==2)
	{
		MX=-INF,MN=INF;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i]);
			MN=min(MN,S[i]),MX=max(MX,S[i]);
		}
		printf("%d\n",Solve());
		break;
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=2147483647;
int N,T[1000001],W[1000001],A[1000001],B[1000001];
int VIS[1000001],MN;
vector<int>V;
LL Solve()
{
	static int kase=0;kase++;
	LL ans=0L;
	for(int i=1;i<=N;i++)
	{
		if(VIS[i]==kase)continue;
		V.clear();
		V.push_back(i);
		for(int u=B[i];u!=i;u=B[u])V.push_back(u);
		int mn=INF;LL sum=0L;
		for(int i=0;i<V.size();i++)
		{
			int &v=V[i];
			VIS[v]=kase;
			mn=min(mn,W[v]);
			sum+=W[v];
		}
		sum-=mn;
		ans+=sum+min(mn*(V.size()-1L),2L*(MN+mn)+MN*(V.size()-1L));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=1;i<=1000000;i++)VIS[i]=0;
	while(scanf("%d",&N)==1)
	{
		MN=INF;
		for(int i=1;i<=N;i++){scanf("%d",&W[i]);MN=min(MN,W[i]);}
		for(int i=1;i<=N;i++)scanf("%d",&A[i]);
		for(int i=1,v;i<=N;i++){scanf("%d",&v);B[v]=i;}
		for(int i=1;i<=N;i++)A[i]=B[A[i]],T[B[i]]=W[i];
		for(int i=1;i<=N;i++)W[i]=T[A[i]],B[A[i]]=i;
		printf("%lld\n",Solve());
	}
	return 0;
}

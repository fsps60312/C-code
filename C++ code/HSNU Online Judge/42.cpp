#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int N,MX,MN,A[100],B[100],DP_BASE[200001],VIS_BASE[200001];
int &DP(const int &i){assert(i>=MN&&i<=MX);return DP_BASE[i+100000];}
int &VIS(const int &i){assert(i>=MN&&i<=MX);return VIS_BASE[i+100000];}
vector<int>V,TMP;
int main()
{
	scanf("%d",&N);
	MX=0,MN=0;
	for(int i=0;i<N;i++)
	{
		scanf("%d%d",&A[i],&B[i]);
		if(A[i]>0)MX+=A[i];
		else MN+=A[i];
	}
	for(int i=MN;i<=MX;i++)DP(i)=-INF,VIS(i)=0;
	DP(0)=0,VIS(0)++;
	V.push_back(0);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<V.size();j++)
		{
			int &v=V[j];
			if(!VIS(v+A[i])++)TMP.push_back(v+A[i]);
			DP(v+A[i])=max(DP(v+A[i]),DP(v)+B[i]);
			printf("DP[%d]=%d\n",v+A[i],DP(v+A[i]));
		}
		for(int j=0;j<TMP.size();j++)V.push_back(TMP[j]);
		TMP.clear();
	}
	int ans=0;
	for(int i=0;i<V.size();i++)
	{
		int &v=V[i];
		if(v>=0&&DP(v)>=0)ans=max(ans,v+DP(v));
	}
	printf("%d\n",ans);
	return 0;
}

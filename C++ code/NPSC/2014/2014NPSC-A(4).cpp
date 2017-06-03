#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int T,N,M,A[1000],B[100000],DP[1001][1000];
map<int,vector<int> >S;
map<int,int>NOW;
void getmax(int &a,const int &b){if(b>a)a=b;}
int Solve()
{
	S.clear(),NOW.clear();
	for(int i=0;i<M;i++)S[B[i]].push_back(i);
	for(int i=0;i<N;i++)if(S.find(A[i])==S.end())return 0;
//	for(int i=0;i<N;i++){printf("i=%d:",i);for(int j=0;j<S[A[i]].size();j++)printf(" %d",S[A[i]][j]);puts("");}
	for(int i=0;i<N;i++)DP[1][i]=0;
	if(N==1)return 1;
	for(int ans=2;;ans++)
	{
//		for(int i=0;i<N;i++)printf(" %d",DP[ans-1][i]);puts("");
		int mx=-INF;
		for(int i=N-1;i>=0;i--)NOW[A[i]]=DP[ans-1][i];
		for(int i=0;i<ans-1;i++)getmax(mx,S[A[i]][DP[ans][i]=DP[ans-1][i]]);
		for(int i=ans-1;i<N;i++)
		{
			int &dp=DP[ans][i]=max(DP[ans-1][i],NOW[A[i]]);
//			printf("i=%d,dp=%d\n",i,dp);
			const vector<int>&s=S[A[i]];
			while(dp<s.size()&&s[dp]<=mx)dp++;
			if(dp==s.size())return ans-1;
			NOW[A[i]]=dp;
			getmax(mx,s[DP[ans-1][i]]);
		}
		if(ans==N)return N;
	}
}
int main()
{
//	freopen("pa.in","r",stdin);
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<M;i++)scanf("%d",&B[i]);
//		printf("N=%d,M=%d\n",N,M);
		int ans=Solve();
		printf("%d\n",N-ans);
	}
	return 0;
}

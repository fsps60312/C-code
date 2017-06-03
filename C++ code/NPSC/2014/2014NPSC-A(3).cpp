#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int T,N,M,A[1000],B[100000],DP[1001][1000];
map<int,vector<int> >S;
void getmin(int &a,const int &b){if(b<a)a=b;}
int &Last(vector<int>&v){return v[v.size()-1];}
int Solve()
{
	S.clear();
	for(int i=0;i<M;i++)S[B[i]].push_back(i);
	for(int i=0;i<N;i++)if(S.find(A[i])==S.end())return 0;
	map<int,int>NOW;
	for(int i=0;i<N;i++)DP[1][i]=NOW[A[i]]=S[A[i]].size()-1;
	for(int ans=2;;ans++)
	{
		int mn=INF;
		for(int i=0;i<=N-ans+1;i++)NOW[A[i]]=S[A[i]][DP[ans-1][i]];
		for(int i=N-ans+1;i<N;i++)getmin(mn,S[A[i]][DP[ans-1][i]]);
		for(int i=N-ans;i>=0;i--)
		{
			int &dp=DP[ans][i]=min(DP[ans-1][i],NOW[A[i]]);
			while(dp>=0&&S[A[i]][dp]>=mn)dp--;
			if(dp==-1)return ans-1;
			NOW[A[i]]=dp;
			getmin(mn,S[A[i]][DP[ans-1][i]]);
		}
	}
}
int main()
{
	freopen("pa.in","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<M;i++)scanf("%d",&B[i]);
		int ans=Solve();
		printf("%d\n",N-ans);
	}
	return 0;
}

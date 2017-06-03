#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int Q,M,K;
vector<int>N,R;
int DP[150001];
int Solve()
{
	if(Q==0)return 0;
	int loopsum=0;
	for(int i=0,a;i<M;i++)scanf("%d",&a),N.push_back(a),loopsum+=a;
	for(int i=0,a;i<K;i++)scanf("%d",&a),R.push_back(a);
	if(loopsum>=Q)
	{
		for(int i=0;i<=Q;i++)DP[i]=-1;
		DP[0]=0;
		for(int i=0;i<M;i++)
		{
			for(int j=Q;j>=N[i];j--)if(DP[j-N[i]]!=-1)getmax(DP[j],DP[j-N[i]]+N[i]);
		}
		if(DP[Q]!=-1)return Q;
		else return Q-1;
	}
	Q-=loopsum;
	for(int i=0;i<=Q;i++)DP[i]=-1;
	DP[0]=0;
	for(int i=0;i<K;i++)
	{
		for(int j=Q;j>=R[i];j--)if(DP[j-R[i]]!=-1)getmax(DP[j],DP[j-R[i]]+R[i]-1);
	}
	int last=-1;
	for(int i=0;i<Q;i++)if(DP[i]!=-1)last=i;
	int ans=DP[last]+Q-last+1;
	if(DP[Q]>ans)ans=DP[Q];
	return loopsum+ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&Q,&M,&K);
	printf("%d\n",Solve());
	return 0;
}

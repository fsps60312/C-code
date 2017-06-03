#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
//bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int Q,M,K;
vector<int>N,R;
int DP[150001];
int Solve()
{
	int loopsum=0;
	for(int i=0,a;i<M;i++)scanf("%d",&a),N.push_back(a),loopsum+=a;
	int tmp=0;
	for(int i=0,a;i<K;i++)scanf("%d",&a),R.push_back(a),tmp+=a;
	assert(loopsum+tmp>=Q);
	if(Q==0)return 0;
	if(loopsum>=Q)
	{
//		assert(0);
		for(int i=0;i<=Q;i++)DP[i]=0;
		DP[0]=1;
		for(int i=0;i<M;i++)
		{
			for(int j=Q;j>=N[i];j--)DP[j]|=DP[j-N[i]];
		}
		if(DP[Q])return Q;
		else return Q-1;
	}
//	assert(0);
	Q-=loopsum;
	for(int i=0;i<=Q;i++)DP[i]=INF;
	DP[0]=0;
	for(int i=0;i<K;i++)
	{
		for(int j=Q-1;j>=0;j--)if(DP[j]!=INF)getmin(DP[min(Q,j+R[i])],DP[j]+1);
	}
	assert(DP[Q]!=INF);
	assert(Q<=tmp);
	return loopsum+Q-DP[Q];
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&Q,&M,&K);
	printf("%d\n",Solve());
	return 0;
}

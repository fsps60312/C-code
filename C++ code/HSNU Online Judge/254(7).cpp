#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
//bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int Q,M,K;
vector<int>N,R;
int DP[150001];
bool ISANS[150001];
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
	for(int i=0;i<=Q;i++)DP[i]=INF,ISANS[i]=true;
	DP[0]=0;
	for(int i=0;i<K;i++)
	{
		for(int j=Q;j>=R[i];j--)if(DP[j-R[i]]!=INF)getmin(DP[j],DP[j-R[i]]+1),ISANS[j-R[i]]=false;
	}
	int ans=INF;
	for(int i=0;i<Q;i++)if(ISANS[i])
	{
		getmin(ans,DP[i]);
	}
	if(ans!=INF)ans++;
	getmin(ans,DP[Q]);
	assert(ans!=INF);
	assert(Q<=tmp);
	return loopsum+Q-ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&Q,&M,&K);
	printf("%d\n",Solve());
	return 0;
}

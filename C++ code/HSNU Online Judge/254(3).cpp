#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
bool getmax(int &a,const int b){if(b>a){a=b;return true;}return false;}
int Q,M,K;
vector<int>N,R;
int DP[150001];
bool ISANS[150001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&Q,&M,&K);
	for(int i=0,a;i<M;i++)scanf("%d",&a),N.push_back(a);
	for(int i=0,a;i<K;i++)scanf("%d",&a),R.push_back(a);
	for(int i=0;i<=Q;i++)DP[i]=-1,ISANS[i]=true;
	DP[0]=0;
	for(int i=0;i<M;i++)
	{
		for(int j=Q;j>=N[i];j--)if(DP[j-N[i]]!=-1&&getmax(DP[j],DP[j-N[i]]+N[i]))ISANS[j-N[i]]=false;
	}
	for(int i=0;i<K;i++)
	{
		for(int j=Q;j>=R[i];j--)if(DP[j-R[i]]!=-1&&getmax(DP[j],DP[j-R[i]]+R[i]-1))ISANS[j-R[i]]=false;
	}
	int last=-1;
	for(int i=0;i<Q;i++)if(DP[i]!=-1&&ISANS[i]&&(last==-1||DP[i]+Q-i-1>DP[last]+Q-last-1))last=i;
	assert(last!=-1);
	int ans=DP[last]+Q-last-1;
	if(DP[Q]>ans)ans=DP[Q];
	printf("%d\n",ans);
	return 0;
}

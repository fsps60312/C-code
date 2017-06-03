#include<cstdio>
#include<vector>
#define LL long long
using namespace std;
const LL MOD=1000000000;
int N;
LL DP[300][300];
char TAP[301];
LL getDP(int l,int r)
{
	LL &dp=DP[l][r];
	if(dp!=-1)return dp;
	if(l>r)return dp=0;
	if(l==r)return dp=1;
	if(TAP[l]!=TAP[r])return dp=0;
	dp=getDP(l+1,r-1);
	vector<int> idx;
	vector<LL> t;
	int tsz=-1;
	for(int i=l+1;i<r;i++)
	{
		if(TAP[i]!=TAP[l])continue;
		//t[i]:l~idx[i],cases
		tsz=t.size();
		idx.push_back(i);
		t.push_back(0LL);
		for(int j=0;j<tsz;j++)
		{
			t[tsz]+=t[j]*getDP(idx[j]+1,idx[tsz]-1);
			t[tsz]%=MOD;
		}
	}
	if(tsz>=0)dp+=t[tsz];
	return dp;
}
LL solve()
{
	return getDP(0,N-1);
	if(N==1)return 1LL;
	if(N==2)return 0LL;
	if(TAP[0]!=TAP[N-1])return 0LL;
	return getDP(1,N-2);
}
int main()
{
	while(scanf("%s",TAP)==1)
	{
		N=-1;while(TAP[++N]);
		printf("%lld\n",solve());
	}
	return 0;
}

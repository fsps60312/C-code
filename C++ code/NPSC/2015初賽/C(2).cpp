#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
LL N,M;
const LL MOD=1000000007LL;
vector<vector<LL> >P;//move K,K*2,K*4
vector<LL>Merge(const vector<LL>&a,const vector<LL>&b)
{
	assert(a.size()==M&&b.size()==M);
	vector<LL>ans;
	for(int i=0;i<M;i++)ans.push_back(a[0]*b[i]%MOD);
	for(int i=1;i<M;i++)
	{
		ans.push_back(0LL);
		for(int j=0;j<M;j++)(ans[i+j]+=a[i]*b[j])%=MOD;
	}
	for(int i=ans.size()-1;i>=M;i--)
	{
		for(int j=0;j<M;j++)(ans[i-M+j]+=ans[i])%=MOD;
		ans.pop_back();
	}
	return ans;
}
vector<LL>GetP(const int deg)
{
	vector<LL>ans;
	if(deg==0){for(int i=0;i<M;i++)ans.push_back(1LL);return ans;}
	return Merge(P[deg-1],P[deg-1]);
}
int main()
{
	while(scanf("%lld%lld",&N,&M)==2)
	{
		N--;
		P.clear();
		for(int i=0;(1LL<<i)*M<=N;i++)P.push_back(GetP(i)),assert(P[i].size()==M);
		vector<LL>ans;
		ans.push_back(1LL);
		while(ans.size()<M)ans.push_back(0LL);
		for(int i=P.size()-1;i>=0;i--)if(N>=M*(1LL<<i))
		{
			ans=Merge(ans,P[i]);
			N-=M*(1LL<<i);
		}
		assert(N<M);
		for(int i=0;i<N;i++)ans.push_back(0LL);
		for(int i=M-1;i>=0;i--)ans[i+N]=ans[i];
		for(int i=0;i<N;i++)ans[i]=0LL;
		for(int i=ans.size()-1;i>=M;i--)
		{
			for(int j=0;j<M;j++)(ans[i-M+j]+=ans[i])%=MOD;
			ans.pop_back();
		}
		LL result=0LL;
		assert(ans.size()==M);
		for(LL i=0,v=1LL;i<M;i++,(v*=2LL)%=MOD)(result+=ans[i]*v)%=MOD;
		printf("%lld\n",result);
	}
	return 0;
}

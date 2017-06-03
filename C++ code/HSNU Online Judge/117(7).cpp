#include<cstdio>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
int CntBits(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
LL ANS;
void Dfs(const int dep,const LL &a,const LL &b,const LL &c,const vector<LL>&sum)
{
//	LL tmp=0;for(int i=0;i<N;i++)tmp+=S[i];
//	assert(a+b+c+sum[dep]==tmp);
	if(a>b){Dfs(dep,b,a,c,sum);return;}
	assert(a<=b);
	if(a+sum[dep]<=b&&(c-(a+sum[dep])>=ANS||b-c>=ANS||b-(a+sum[dep])>=ANS))return;
	if(dep==0){getmin(ANS,max(b,c)-min(a,c));return;}
	assert(sum[dep]>sum[dep-1]);
	Dfs(dep-1,a,b+sum[dep]-sum[dep-1],c,sum);
	if(a!=b)Dfs(dep-1,a+sum[dep]-sum[dep-1],b,c,sum);
}
int N;
LL S[24];
int main()
{
	scanf(1,"%d",&N);
	for(int i=0;i<N;i++)scanf(1,"%lld",&S[i]);
	sort(S,S+N);
	ANS=INF/2LL;
	for(int i=0;i<(1<<N);i++)if(CntBits(i)<=N/3)
	{
		static vector<LL>sum;sum.clear(),sum.push_back(0LL);
		static LL c;c=0LL;
		for(int j=0;j<N;j++)
		{
			if(i&(1<<j))c+=S[j];
			else sum.push_back(S[j]);
		}
		const int sz=(int)sum.size();
		for(int j=1;j<sz;j++)sum[j]+=sum[j-1];
		if(abs(sum[sz-1]-c*2LL)<ANS+ANS)Dfs(sz-1,0LL,0LL,c,sum);
	}
	printf("%lld\n",ANS);
	return 0;
}

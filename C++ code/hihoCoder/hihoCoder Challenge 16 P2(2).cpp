#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
LL N,S[2000],SUM;
vector<LL>F,SEG;
void Cut(const LL n,const LL idx)
{
	SEG[idx]=0;
	if(SUM%n!=0)return;
	map<LL,LL>cnt;
	LL sum=0;
	for(LL i=0;i<N;i++)
	{
		sum+=S[i];
		LL m=sum%n;
		if(cnt.find(m)!=cnt.end())cnt[m]++;
		else cnt[m]=1;
	}
	for(auto it=cnt.begin();it!=cnt.end();it++)SEG[idx]=max(SEG[idx],it->second);
}
void GetF(const LL n)
{
	F.clear();
	for(LL i=1LL;i*i<=n;i++)
	{
		if(n%i==0LL)F.push_back(i),F.push_back(n/i);
	}
	sort(F.begin(),F.end());
	F.resize(unique(F.begin(),F.end())-F.begin());
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld",&N);
	SUM=0;
	for(LL i=0;i<N;i++)
	{
		scanf("%lld",&S[i]);
		SUM+=S[i];
	}
	GetF(SUM);
	SEG.resize(F.size());
	for(LL i=0;i<F.size();i++)
	{
		Cut(F[i],i);
//		printf("CUT[%lld]=%lld\n",F[i],SEG[i]);
	}
	printf("%lld\n",SUM);
	for(LL n=2;n<=N;n++)
	{
		bool found=false;
		for(LL i=(LL)F.size()-1;i>=0;i--)if(SEG[i]>=n){printf("%lld\n",F[i]);found=true;break;}
		if(!found)for(int i=0,j=0;;)i/=j;
	}
//	puts("");
	return 0;
}

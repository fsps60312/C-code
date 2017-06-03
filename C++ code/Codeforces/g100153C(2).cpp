#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
//const LL INF=9223372036854775807LL;
struct Set
{
	LL W,V,S;
	Set(){}
	Set(const LL _W,const LL _V,const LL _S):W(_W),V(_V),S(_S){}
};
bool operator<(const Set &a,const Set &b){return a.W<b.W;}
Set MaxValue(const Set &a,const Set &b){return a.V<b.V?b:a;}
Set SPARSE[17][1<<16];
void BuildSparse(const vector<Set>&s,const int n)
{
	assert(n<=(1<<16));
	for(int i=0;i<n;i++)SPARSE[0][i]=s[i];
	for(int d=1;(1<<d)<=n;d++)
	{
		for(int i=0;i+(1<<d)<=n;i++)SPARSE[d][i]=MaxValue(SPARSE[d-1][i],SPARSE[d-1][i+(1<<(d-1))]);
	}
}
Set QuerySparse(const int l,const int r,const int n)
{
	assert(0<=l&&l<=r&&r<n);
	int d=0;
	while((1<<(d+1))<=r-l+1)d++;
	return MaxValue(SPARSE[d][l],SPARSE[d][r-(1<<d)+1]);
}
int N,HALF;
LL L,R,W[32],V[32];
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("dowry.in","r",stdin);
	freopen("dowry.out","w",stdout);
	while(scanf("%d%lld%lld",&N,&L,&R)==3)
	{
		for(int i=0;i<N;i++)scanf("%lld%lld",&W[i],&V[i]);
		HALF=N/2;
		vector<Set>left;
		for(int s=0;s<(1<<HALF);s++)
		{
			Set p=Set(0,0,s);
			for(int i=0;i<HALF;i++)if(s&(1<<i))p.W+=W[i],p.V+=V[i];
			left.push_back(p);
//			printf("%lld %lld\n",p.W,p.V);
		}
		sort(left.begin(),left.end());
		BuildSparse(left,1<<HALF);
		Set ans=Set(0,-1,0);
		for(int s=0;s<(1<<(N-HALF));s++)
		{
			Set p=Set(0,0,(LL)s<<HALF);
			for(int i=HALF;i<N;i++)if(s&(1<<(i-HALF)))p.W+=W[i],p.V+=V[i];
			const auto &itl=lower_bound(left.begin(),left.end(),Set(L-p.W,0,0)),
					   &itr=upper_bound(left.begin(),left.end(),Set(R-p.W,0,0));
//			printf("(%lld,%lld)\n",L-p.W,R-p.W);
			if(itl!=itr)
			{
				const Set &result=QuerySparse((int)(itl-left.begin()),(int)(itr-left.begin())-1,1<<HALF);
//				printf(" %d %lld %lld\n",s,result.V,p.V);
				ans=MaxValue(ans,Set(result.W+p.W,result.V+p.V,result.S|p.S));
			}
		}
//		if(ans.V==-1){puts("0");continue;}
		vector<int>output;
		for(int i=0;i<N;i++)if(ans.S&(1LL<<i))output.push_back(i+1);
//		printf("%lld %lld %lld\n",ans.W,ans.V,ans.S);
		printf("%d\n",(int)output.size());
		for(int i=0;i<(int)output.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",output[i]);
		}
		puts("");
	}
	return 0;
}

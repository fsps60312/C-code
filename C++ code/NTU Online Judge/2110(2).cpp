#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
int N;
struct Bit
{
	int S[100002];
	vector<int>HIS;
	Bit(){for(int i=1;i<=100001;i++)S[i]=0;}
	inline void Clear()
	{
		for(const int v:HIS)S[v]=0;
		HIS.clear();
	}
	inline void Modify(int i,const int v)
	{
		if(!v)return;
//		assert(i>=0);
		++i;
		for(;i<=N;i+=(i&(-i)))
		{
			if(!S[i])HIS.push_back(i);
			getmax(S[i],v);
		}
	}
	inline int GetMax(int i)
	{
//		assert(i>=0);
		++i;
		int ans=0;
		for(;i;i-=(i&(-i)))getmax(ans,S[i]);
		return ans;
	}
}BIT;
int A[100001],DP[100001];
void Solve(const int l,const int r)
{
	if(l==r)return;
	const int mid=(l+r)/2;
	Solve(l,mid);
	map<int,vector<int> >left_s,rigt_s;
	for(int i=l;i<=r;i++)(i<=mid?left_s:rigt_s)[A[i]-i].push_back(i);
	auto itl=left_s.rbegin(),itr=rigt_s.rbegin();
	for(;itr!=rigt_s.rend();++itr)
	{
		for(;itl!=left_s.rend()&&itl->first>itr->first;++itl)
		{
			for(const int v:itl->second)if(A[v]>=0)BIT.Modify(A[v],DP[v]);
		}
		for(const int v:itr->second)
		{
			if(A[v]>=0)getmax(DP[v],BIT.GetMax(A[v])+1);
		}
	}
	BIT.Clear();
	Solve(mid+1,r);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<N;i++)DP[i]=1;
		for(int i=0;i<N;i++)A[i]=i+1-A[i];
		for(int i=0;i<N;i++)if(A[i]<0||i<A[i])DP[i]=0;
		Solve(0,N-1);
		int ans=0;
		for(int i=0;i<N;i++)getmax(ans,DP[i]);
		printf("%d\n",ans);
	}
	return 0;
}

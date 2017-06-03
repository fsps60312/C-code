#include<cstdio>
#include<cassert>
#include<set>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M;
int S[400002],LEN[400002];
set<int>ELE[400002];
int MAX_LEN;
void BuildLIS()
{
	int *dp=new int[400002];
	MAX_LEN=0;
	for(int i=0;i<=N+1;i++)
	{
		int l=0,r=MAX_LEN;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(dp[mid]>S[i])r=mid;
			else l=mid+1;
		}
		if(r==MAX_LEN)ELE[MAX_LEN++].clear();
		dp[LEN[i]=r]=S[i];
		ELE[LEN[i]].insert(i);
	}
	for(int i=MAX_LEN-2;i>=0;i--)
	{
		while(S[*ELE[i].begin()]>=S[*ELE[i+1].begin()])
		{
			ELE[i].erase(ELE[i].begin());
			assert(!ELE[i].empty());s
		}
	}
	delete[]dp;
}
bool InSequence(const int a,const int b,int l,int r)
{
	while(l<=r)
	{
		const int mid=(l+r)/2;
		auto itl=ELE[mid].lower_bound(a);
		auto itr=ELE[mid].upper_bound(a);
		if(itl!=ELE[mid].begin()&&S[*(--itl)]<b)l=mid+1;
		else if(itr!=ELE[mid].end()&&b<S[*itr])r=mid-1;
		else return true;
	}
	return false;
}
int Solve(const int a,const int b)
{
	if(b==S[a])return MAX_LEN;
	const int len=LEN[a];
	if((int)ELE[len].size()==1)
	{
		int l,r;
		if(b>S[a])l=len+1,r=MAX_LEN-1;
		else l=0,r=len-1;
		return InSequence(a,b,l,r)?MAX_LEN-1:MAX_LEN;
	}
	return InSequence(a,b,0,MAX_LEN-1)?MAX_LEN:MAX_LEN+1;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		S[0]=-INF,S[N+1]=INF;
		BuildLIS();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			printf("%d\n",Solve(a,b)-2);
		}
	}
	return 0;
}

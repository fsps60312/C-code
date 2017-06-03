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
		ELE[r].insert(i);
	}
	for(int i=MAX_LEN-2;i>=0;i--)
	{
		while(S[*ELE[i].begin()]>=S[*ELE[i+1].begin()])ELE[i].erase(ELE[i].begin());
		while(*ELE[i].rbegin()>=*ELE[i+1].rbegin())ELE[i].erase(prev(ELE[i].end()));
	}
	delete[]dp;
}
bool InSequence(const int a,const int b,const int left,const int right)
{
	int l=left,r=right;
	while(l<=r)
	{
		const int mid=(l+r)/2;
		auto itl=ELE[mid].lower_bound(a);
		auto itr=ELE[mid].upper_bound(a);
		if(b<=S[*prev(ELE[mid-1<left?0:mid-1].lower_bound(a))])r=mid-1;
		else if(b>=S[*ELE[mid+1>right?MAX_LEN-1:mid+1].upper_bound(a)])l=mid+1;
		else if(itl!=ELE[mid].begin()&&S[*(--itl)]<b)l=mid+1;
		else if(itr!=ELE[mid].end()&&b<S[*itr])r=mid-1;
		else return true;
	}
	return false;
}
bool StillIn(const int a,const int b)
{
	const int len=LEN[a];
	if(b<=S[*prev(ELE[len-1].lower_bound(a))])return false;
	if(b>=S[*ELE[len+1].upper_bound(a)])return false;
	auto itl=ELE[len].lower_bound(a),itr=ELE[len].upper_bound(a);
	if(itl!=ELE[len].begin()&&b>S[*(--itl)])return false;
	if(itr!=ELE[len].end()&&b<S[*itr])return false;
	return true;
}
int Solve(const int a,const int b)
{
	const int len=LEN[a];
	if(ELE[len].count(a))
	{
		if(StillIn(a,b))return MAX_LEN;
		int ans=(InSequence(a,b,1,len-1)||InSequence(a,b,len+1,MAX_LEN-2)?MAX_LEN:MAX_LEN+1);
		if((int)ELE[len].size()==1)ans--;
		return ans;
	}
	else
	{
		return InSequence(a,b,1,MAX_LEN-2)?MAX_LEN:MAX_LEN+1;
	}
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
		break;
	}
	return 0;
}

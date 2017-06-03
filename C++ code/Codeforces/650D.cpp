#include<cstdio>
#include<cassert>
#include<deque>
#include<algorithm>
using namespace std;
int N,M;
int S[400000],LEN[400000],DP[400000],ID[400000];
deque<int>ELE[400000];
int MAX_LEN;
int Solve(const int a,const int b)
{
	const int len=LEN[a];
	if(b==S[a])return MAX_LEN;
	if(ID[a]!=-1)
	{
		if(len-1>=0)
		{
			auto it=lower_bound(ELE[len-1].begin(),ELE[len-1].end(),a);
			if(it!=ELE[len-1].begin())
			{
				it--;
				if(ID[a]+1<(int)ELE[len].size()&&S[*it]<b&&b<S[ELE[len][ID[a]+1]])return MAX_LEN+1;
				if((int)ELE[len].size()==1&&S[*it]>=b)return MAX_LEN-1;
			}
		}
		if(len+1<MAX_LEN)
		{
			auto it=upper_bound(ELE[len+1].begin(),ELE[len+1].end(),a);
			if(it!=ELE[len+1].end())
			{
				if(ID[a]-1>=0&&S[ELE[len][ID[a]-1]]<b&&b<S[*it])return MAX_LEN+1;
				if((int)ELE[len].size()==1&&b>=S[*it])return MAX_LEN-1;
			}
		}
		return MAX_LEN;
	}
	else
	{
		
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i<N;i++)ELE[i].clear();
		MAX_LEN=0;
		for(int i=0;i<N;i++)
		{
			int l=0,r=MAX_LEN;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(DP[mid]>S[i])r=mid;
				else l=mid+1;
			}
			DP[LEN[i]=r]=S[i];
			ELE[LEN[i]].push_back(i);
			if(r==MAX_LEN)MAX_LEN++;
		}
		for(int i=MAX_LEN-2;i>=0;i--)
		{
			while(S[ELE[i].front()]>=S[ELE[i+1].front()])ELE[i].pop_front();
		}
		for(int i=0;i<N;i++)ID[i]=-1;
		for(int i=0;i<MAX_LEN;i++)for(int j=0;j<(int)ELE[i].size();j++)ID[ELE[i][j]]=j;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--;
			printf("%d\n",Solve(a,b));
		}
	}
	return 0;
}

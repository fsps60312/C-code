#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
void BuildLIS(const int n,const int *s,int *lens)
{
	static int dp[400000];
	int len=0;
	for(int i=0;i<n;i++)
	{
		int l=0,r=len;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(dp[mid]<s[i])l=mid+1;
			else r=mid;
		}
		if(len==r)len++;
		dp[r]=s[i];
		lens[i]=r+1;
	}
}
int N,M,S[400000];
void Solve(int *ans,const vector<pair<int,pair<int,int> > >&queries,const int *lens)
{
	map<int,int>deq;
	int bound=0;
	for(auto it=queries.begin();it!=queries.end();it++)
	{
		for(;bound<it->first;bound++)
		{
			auto iu=deq.lower_bound(S[bound]);
			if(iu!=deq.end()&&iu->first==S[bound]&&lens[bound]<iu->second)continue;
			while(iu!=deq.end()&&lens[bound]>=iu->second)deq.erase(iu++);
			deq[S[bound]]=lens[bound];
		}
		const auto &p=it->second;
		auto iu=deq.lower_bound(p.second);
		if(iu!=deq.begin())ans[p.first]+=(--iu)->second;
	}
}
int LENS[400000],BEST_ANS[400000];
int REMOVE[400000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		BuildLIS(N,S,LENS);
		vector<pair<int,pair<int,int> > >queries;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);a--;
			queries.push_back(make_pair(a,make_pair(i,b)));
			BEST_ANS[i]=REMOVE[a];
		}
		sort(queries.begin(),queries.end());
		int *ans=new int[M];
		for(int i=0;i<M;i++)ans[i]=1;
		Solve(ans,queries,LENS);
		reverse(S,S+N);
		reverse(queries.begin(),queries.end());
		for(auto &p:queries)p.first=N-1-p.first,p.second.second*=-1;
		for(int i=0;i<N;i++)S[i]*=-1;
		BuildLIS(N,S,LENS);
		Solve(ans,queries,LENS);
		for(int i=0;i<M;i++)printf("%d\n",max(BEST_ANS[i],ans[i]));
		delete[]ans;
	}
	return 0;
}

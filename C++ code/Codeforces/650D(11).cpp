#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
void getmin(int &a,const int b){if(b<a)a=b;}
int REMOVE[400000];
void BuildLIS(const int n,const int *s,int *lens)
{
	static int dp[400001];
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
		lens[i]=r;
	}
	static int cnt[400001],idx[400001];
	for(int i=0;i<len;i++)cnt[i]=0,dp[i]=-INF;
	cnt[len]=1,dp[len]=INF;
	for(int i=n-1;i>=0;i--)
	{
		if(!cnt[lens[i]+1]||s[i]>=dp[lens[i]+1])continue;
//		printf(" %d(%d,%d,%d)",i,s[i],lens[i],dp[lens[i]+1]);
		getmax(dp[lens[i]],s[i]);
		cnt[lens[i]]++,idx[lens[i]]=i;
	}
//	puts("");for(int i=0;i<n;i++)printf(" %d",lens[i]);puts("");
	for(int i=0;i<n;i++)REMOVE[i]=len;
	for(int i=0;i<len;i++)if(cnt[i]==1)REMOVE[idx[i]]--;
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
		if(iu!=deq.begin())ans[p.first]+=(--iu)->second+1;
	}
}
int LENS[400000],BEST_ANS[400000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		BuildLIS(N,S,LENS);
//		for(int i=0;i<N;i++)printf(" %d",REMOVE[i]);puts("");
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
		for(int i=0;i<M;i++)printf("%d\n",max(BEST_ANS[i],ans[i]));//,BEST_ANS[i],ans[i]);
		delete[]ans;
	}
	return 0;
}

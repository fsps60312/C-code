#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
void BuildLIS(const int n,const int *s,int *left,int *right,int *remove)
{
	static int dp[400000];
	int len=0;
	for(int i=n-1;i>=0;i--)
	{
		int l=0,r=len;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(dp[mid]>s[i])l=mid+1;
			else r=mid;
		}
		if(len==r)len++;
		dp[r]=s[i];
		right[i]=r;
	}
	len=0;
	static int low[399999];
	static vector<int>stks[400000];
	for(int i=0;i<n;i++)stks[i].clear();
	for(int i=0;i<n;i++)
	{
		if(i==n-1)remove[n-1]=len;
		else
		{
			int l=-1,r=len-1;
			while(l<r)
			{
				const int mid=(l+r+1)/2;
				if(dp[mid]<s[i+1])l=mid;
				else r=mid-1;
			}
			const int left_len=r+1;
			remove[i]=left_len+(right[i+1]+1);
			if(r==-1)low[i]=-1;
			else
			{
				const vector<int>&stk=stks[r];
				l=0,r=(int)stk.size()-1;
				while(l<r)
				{
					const int mid=(l+r)/2;
					if(s[stk[mid]]<s[i+1])r=mid;
					else l=mid+1;
				}
				assert(s[stk[r]]<s[i+1]);
				low[i]=stk[r];
			}
		}
		int l=0,r=len;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(dp[mid]<s[i])l=mid+1;
			else r=mid;
		}
		if(len==r)len++;
		dp[r]=s[i];
		left[i]=r;
//		if(!stk[r].empty()&&s[i]==s[stk[r][(int)stk[r].size()-1]])continue;
		stks[r].push_back(i);
	}
	int l=0,r=-1;
	for(int i=n-2;i>=0;i--)
	{
		while(r-l>=0&&low[dp[l]]>=i)l++;
		while(r-l>=0&&remove[i]>=remove[dp[r]])r--;
		dp[++r]=i;
		remove[i]=remove[dp[l]];
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
			deq[S[bound]]=lens[bound]+1;
		}
		const auto &p=it->second;
		auto iu=deq.lower_bound(p.second);
		if(iu!=deq.begin())ans[p.first]+=(--iu)->second;
	}
}
int LEFT[400000],RIGHT[400000],REMOVE[400000],ORIGIN[400000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		BuildLIS(N,S,LEFT,RIGHT,REMOVE);
		vector<pair<int,pair<int,int> > >queries;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);a--;
			queries.push_back(make_pair(a,make_pair(i,b)));
			ORIGIN[i]=REMOVE[a];
		}
		sort(queries.begin(),queries.end());
		int *ans=new int[M];
		for(int i=0;i<M;i++)ans[i]=1;
		map<int,int>deq;
		int bound=0;
		for(auto it=queries.begin();it!=queries.end();it++)
		{
			for(;bound<it->first;bound++)
			{
				auto iu=deq.lower_bound(S[bound]);
				if(iu!=deq.end()&&iu->first==S[bound]&&LEFT[bound]<iu->second)continue;
				while(iu!=deq.end()&&LEFT[bound]>=iu->second)deq.erase(iu++);
				deq[S[bound]]=LEFT[bound];
			}
			const auto &p=it->second;
			auto iu=deq.lower_bound(p.second);
			if(iu!=deq.begin())ans[p.first]+=(--iu)->second;
		}
		deq.clear();
		bound=N-1;
		for(auto it=queries.rbegin();it!=queries.rend();it++)
		{
			for(;bound>it->first;bound--)
			{
				auto iu=deq.upper_bound(S[bound]);
				if(iu!=deq.begin()&&(--iu)->first==S[bound]&&RIGHT[bound]<iu->second)continue;
				while(iu!=deq.end()&&RIGHT[bound]>=iu->second)deq.erase(iu++);
				deq[S[bound]]=RIGHT[bound];
			}
			const auto &p=it->second;
			auto iu=deq.lower_bound(p.second);
			if(iu!=deq.begin())ans[p.first]+=(--iu)->second;
		}
		for(int i=0;i<M;i++)printf("%d\n",max(ORIGIN[i],ans[i]));
		delete[]ans;
	}
	return 0;
}

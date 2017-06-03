#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
struct Deq
{
	int DATA[400000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){DATA[++R]=v;}
	void PopBack(){R--;}
	int Size()const{return R-L+1;}
	int Back()const{return DATA[R];}
	int operator[](const int i)const{return DATA[L+i];}
}DEQ;
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
		lens[i]=r;
	}
}
int N,M,S[400000];
void Solve(int *ans,const map<int,vector<pair<int,int> > >&queries,const int *lens,bool type)
{
	map<int,int>deq;
	int bound=(type?0:N-1);
	for(auto it=(type?queries.begin():queries.end());;)
	{
		if(!type)it--;
		for(;type?bound<it->first:bound>it->first;type?bound++:bound--)
		{
			auto it=deq.lower_bound(S[bound]);
			if(it!=deq.end()&&it->first==S[bound]&&it->second>=lens[bound])continue;
			while(it!=deq.end()&&it->second>=lens[bound])deq.erase(it++);
			deq[S[bound]]=lens[bound];
		}
		for(const auto &p:it->second)
		{
			auto it=deq.lower_bound(p.second);
			if(it!=deq.begin())ans[p.first]+=(--it)->second;
		}
		if(type)it++;
		if(type&&it==queries.end())break;
		if(!type&&it==queries.begin())break;
	}
}
int LEFT[400000],RIGHT[400000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		BuildLIS(N,S,LEFT);
		reverse(S,S+N);
		for(int i=0;i<N;i++)S[i]=-S[i];
		BuildLIS(N,S,RIGHT);
		for(int i=0;i<N;i++)S[i]=-S[i];
		reverse(S,S+N),reverse(RIGHT,RIGHT+N);
		map<int,vector<pair<int,int> > >queries;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);a--;
			queries[a].push_back(make_pair(i,b));
		}
		int *ans=new int[M];
		for(int i=0;i<M;i++)ans[i]=1;
		Solve(ans,queries,LEFT);
		Solve(ans,queries,RIGHT,false);
		for(int i=0;i<M;i++)printf("%d\n",ans[i]);
		delete[]ans;
	}
	return 0;
}

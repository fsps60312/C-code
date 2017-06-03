#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
struct Bit
{
	int n,data[100001];
	void Clear(const int _n){n=_n;for(int i=1;i<=n;i++)data[i]=0;}
	void Add(int i,const int v){while(i<=n)data[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=data[i],i-=(i&(-i));return ans;}
}BIT;
int N,M,S[100000],LOC[100001],LIFE[100001],QUERY[100000];
LL ANS[100000];
void Solve(const int l,const int r,const vector<int>&numbers,const vector<int>&queries)
{
//	printf("(%d,%d)\n",(int)numbers.size(),(int)queries.size());
//	for(int i=1;i<(int)numbers.size();i++)assert(LOC[numbers[i-1]]<LOC[numbers[i]]);
//	for(int i=1;i<(int)queries.size();i++)assert(LOC[QUERY[queries[i-1]]]<LOC[QUERY[queries[i]]]);
	if(l==r)return;
	vector<int>left_numbers,right_numbers,left_queries,right_queries;
	const int mid=(l+r)/2;
	for(int i=0;i<(int)numbers.size();i++)(LIFE[numbers[i]]<=mid?left_numbers:right_numbers).push_back(numbers[i]);
	for(int i=0;i<(int)queries.size();i++)(queries[i]<=mid?left_queries:right_queries).push_back(queries[i]);
	if(true)
	{
		vector<int>::const_iterator ni=right_numbers.begin();
		for(vector<int>::const_iterator qi=left_queries.begin();qi!=left_queries.end();qi++)
		{
			for(;ni!=right_numbers.end()&&LOC[*ni]<LOC[QUERY[*qi]];ni++)BIT.Add(*ni,1);
			ANS[*qi]+=BIT.Query(N)-BIT.Query(QUERY[*qi]);
		}
		while(ni!=right_numbers.begin())BIT.Add(*--ni,-1);
	}
	if(true)
	{
		vector<int>::const_reverse_iterator ni=right_numbers.rbegin();
		for(vector<int>::const_reverse_iterator qi=left_queries.rbegin();qi!=left_queries.rend();qi++)
		{
			for(;ni!=right_numbers.rend()&&LOC[*ni]>LOC[QUERY[*qi]];ni++)BIT.Add(*ni,1);
			ANS[*qi]+=BIT.Query(QUERY[*qi]);
		}
		while(ni!=right_numbers.rbegin())BIT.Add(*--ni,-1);
	}
	Solve(l,mid,left_numbers,left_queries);
	Solve(mid+1,r,right_numbers,right_queries);
	vector<int>().swap(left_numbers);
	vector<int>().swap(left_queries);
	vector<int>().swap(right_numbers);
	vector<int>().swap(right_queries);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]),LOC[S[i]]=i;
		BIT.Clear(N);
		LL ans=0;
		for(int i=0;i<N;i++)
		{
			ans+=BIT.Query(N)-BIT.Query(S[i]);
			BIT.Add(S[i],1);
		}
		for(int i=1;i<=N;i++)LIFE[i]=M;
		for(int i=0;i<M;i++)
		{
			int &v=QUERY[i];
			scanf("%d",&v);
			LIFE[v]=i;
		}
		vector<int>numbers,queries;
		for(int i=0;i<N;i++)numbers.push_back(S[i]);
		if(true)
		{
			static int sort_buffer[100000];
			for(int i=0;i<N;i++)sort_buffer[i]=-1;
			for(int i=0;i<M;i++)sort_buffer[LOC[QUERY[i]]]=i;
			for(int i=0;i<N;i++)if(sort_buffer[i]!=-1)queries.push_back(sort_buffer[i]);
		}
		for(int i=0;i<M;i++)ANS[i]=0;
		BIT.Clear(N);
		Solve(0,M-1,numbers,queries);
//		for(int i=0;i<M;i++)printf("%lld ",ANS[i]);puts("");
		for(int i=1;i<M;i++)ANS[i]+=ANS[i-1];
		for(int i=0;i<M;i++)printf("%lld\n",ans-(i?ANS[i-1]:0));
	}
	return 0;
}

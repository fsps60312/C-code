#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct QueryType
{
	int l,r,k,id,win;
};
vector<QueryType>QUERY;
struct Event
{
	int val,loc,moment,cnt;
	Event(const int _val,const int _loc,const int _moment,const int _cnt):val(_val),loc(_loc),moment(_moment),cnt(_cnt){}
	bool operator<(const Event &e)const{return moment<e.moment;}
};
vector<Event>EVENT;
struct Bit
{
	int data[100001],n;
	void Clear(const int _n){n=_n;for(int i=1;i<=n;i++)data[i]=0;}
	void Add(int i,const int val){while(i<=n)data[i]+=val,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=data[i],i-=(i&(-i));return ans;}
}BIT;
int ANS[100000];
void Solve(const int l,const int r,const vector<int>&events,const vector<int>&queries)
{
	if(l==r)
	{
		for(const int i:queries)ANS[i]=r;
		return;
	}
	const int mid=(l+r)/2;
	vector<int>left_events,right_events;
	for(const int i:events)(EVENT[i].val<=mid?left_events:right_events).push_back(i);
	static int change_query[100000];
	vector<int>::const_iterator ei=left_events.begin();
	for(vector<int>::const_iterator qi=queries.begin();qi!=queries.end();qi++)
	{
		for(;ei!=left_events.end()&&EVENT[*ei].moment<=(*qi);ei++)
		{
			const Event &e=EVENT[*ei];
			BIT.Add(e.loc,e.cnt);
		}
		QueryType &q=QUERY[*qi];
		change_query[*qi]=BIT.Query(q.r)-BIT.Query(q.l-1);
		q.win+=change_query[*qi];
	}
	while(ei!=left_events.begin())
	{
		const Event &e=EVENT[*--ei];
		BIT.Add(e.loc,-e.cnt);
	}
	vector<int>left_queries,right_queries;
	for(const int i:queries)
	{
		QueryType &q=QUERY[i];
		if(q.win<q.k)right_queries.push_back(i);
		else
		{
			q.win-=change_query[i];
			left_queries.push_back(i);
		}
	}
	Solve(l,mid,left_events,left_queries);
	Solve(mid+1,r,right_events,right_queries);
	vector<int>().swap(left_events);
	vector<int>().swap(left_queries);
	vector<int>().swap(right_events);
	vector<int>().swap(right_queries);
}
vector<int>RANGE;
int N,M,S[100001];
void Discretize()
{
	vector<int>&v=RANGE;v.clear();
	for(int i=1;i<=N;i++)v.push_back(S[i]);
	for(const QueryType &q:QUERY)if(q.l==-1)v.push_back(q.k);
	sort(v.begin(),v.end()),v.resize(M=unique(v.begin(),v.end())-v.begin());
	for(int i=1;i<=N;i++)S[i]=lower_bound(v.begin(),v.end(),S[i])-v.begin();
	for(QueryType &q:QUERY)if(q.l==-1)q.k=lower_bound(v.begin(),v.end(),q.k)-v.begin();
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		int querycount;scanf("%d",&querycount);
		QUERY.clear();
		for(int i=0,type;i<querycount;i++)
		{
			static QueryType q;
			q.id=i,q.win=0;
			scanf("%d",&type);
			if(type==1)q.l=-1,scanf("%d%d",&q.r,&q.k);
			else if(type==2)scanf("%d%d%d",&q.l,&q.r,&q.k);
			else assert(0);
			QUERY.push_back(q);
		}
		Discretize();
		if(true)
		{
			static vector<pair<int,int> >life[100001];
			for(int i=1;i<=N;i++)life[i].clear(),life[i].push_back(make_pair(S[i],0));
			for(const QueryType &q:QUERY)if(q.l==-1)life[q.r].push_back(make_pair(q.k,q.id));
			for(int i=1;i<=N;i++)life[i].push_back(make_pair(-1,querycount));
			EVENT.clear();
			for(int i=1;i<=N;i++)
			{
				for(int j=0;j+1<(int)life[i].size();j++)
				{
					const auto &p1=life[i][j],&p2=life[i][j+1];
					EVENT.push_back(Event(p1.first,i,p1.second,1));
					EVENT.push_back(Event(p1.first,i,p2.second,-1));
				}
			}
			sort(EVENT.begin(),EVENT.end());
		}
		vector<int>events,queries;
		for(int i=0;i<(int)EVENT.size();i++)events.push_back(i);
		for(int i=0;i<querycount;i++)if(QUERY[i].l!=-1)queries.push_back(i);
		BIT.Clear(N);
		Solve(0,M-1,events,queries);
		for(int i=0;i<querycount;i++)if(QUERY[i].l!=-1)printf("%d\n",RANGE[ANS[i]]);
	}
	return 0;
}

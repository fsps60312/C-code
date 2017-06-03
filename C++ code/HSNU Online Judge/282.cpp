#include<cstdio>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
int M,N,Q,FRONT,BACK;
int ANS[100000];
priority_queue<int,vector<int>,greater<int> >GAP;
struct Query
{
	int l,r,idx;
	Query(){}
	Query(const int _l,const int _r,const int _i):l(_l),r(_r),idx(_i){}
};
multimap<int,Query>QUERY;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&M,&N,&Q)==3)
	{
		if(true)
		{
			vector<int>s;
			for(int i=0,v;i<N;i++)scanf("%d",&v),s.push_back(v);
			sort(s.begin(),s.end());
			while(!GAP.empty())GAP.pop();
			for(int i=1;i<N;i++)GAP.push(s[i]-s[i-1]-1);
			FRONT=s[0]-1,BACK=M-s[N-1];
			s.clear(),vector<int>().swap(s);
		}
		QUERY.clear();
		for(int i=0,l,r;i<Q;i++)
		{
			scanf("%d%d",&l,&r);
			QUERY.insert(make_pair(l+r,Query(l,r,i)));
		}
		if(true)
		{
			int now=0;
			for(const auto &it:QUERY)
			{
				while(!GAP.empty()&&GAP.top()<=it.first)N+=GAP.top()-now,GAP.pop();
				N+=(int)GAP.size()*(it.first-now);
				now=it.first;
				const Query &q=it.second;
				ANS[q.idx]=N+min(FRONT,q.l)+min(BACK,q.r);
			}
		}
		for(int i=0;i<Q;i++)printf("%d\n",ANS[i]);
		break;
	}
	return 0;
}

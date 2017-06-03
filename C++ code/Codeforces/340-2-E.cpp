#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<cassert>
#define int long long
using namespace std;
struct Query
{
	int l,r,idx;
	Query(){}
	Query(const int _l,const int _r):l(_l),r(_r){}
	bool operator<(const Query &q)const{return l!=q.l?l<q.l:r<q.r;}
};
int N,K,SUM[100001],GAP,ANS[100000];
vector<Query>QUERY[318];
void Handle(const vector<Query>&queries)
{
	map<int,int>s;
	int now=0,l=0,r=-1;
	for(const Query &q:queries)
	{
		while(r<q.r)r++,now+=s[SUM[r]^K],s[SUM[r]]++;
		while(r>q.r)s[SUM[r]]--,now-=s[SUM[r]^K],r--;
		while(l<q.l-1)s[SUM[l]]--,now-=s[SUM[l]^K],l++;
		assert(l==q.l-1&&r==q.r);
//		printf("ANS[%I64d]=%I64d(%I64d,%I64d)\n",q.idx,now,q.l,q.r);
		ANS[q.idx]=now;
	}
	while(l<=r)s[SUM[l]]--,now-=s[SUM[l]^K],l++;
	assert(now==0);
	for(const auto &it:s)assert(it.second==0);
}
main()
{
//	freopen("in.txt","r",stdin);
	int querycount;
	while(scanf("%I64d%I64d%I64d",&N,&querycount,&K)==3)
	{
		for(int i=1;i<=N;i++)scanf("%I64d",&SUM[i]),SUM[i]^=SUM[i-1];
		GAP=min(N,(int)sqrt(N)+1);
		for(int i=0;i<=N/GAP;i++)QUERY[i].clear();
		for(int i=0;i<querycount;i++)
		{
			static Query q;
			q.idx=i;
			scanf("%I64d%I64d",&q.l,&q.r);
			QUERY[q.r/GAP].push_back(q);
		}
		for(int i=0;i<=N/GAP;i++)
		{
			sort(QUERY[i].begin(),QUERY[i].end());
			Handle(QUERY[i]);
		}
		for(int i=0;i<querycount;i++)printf("%I64d\n",ANS[i]);
	}
	return 0;
}

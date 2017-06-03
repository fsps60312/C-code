#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
struct ModifyType
{
	int l,r;
	LL cost;
	ModifyType(){}
	ModifyType(const int _l,const int _r,const int _cost):l(_l),r(_r),cost(_cost){}
	bool operator<(const ModifyType &m)const{return l<m.l;}
};
int N,M,MANAGER[100001],ANS[100000];
struct Bit
{
	LL data[100001];
	void clear(){for(int i=1;i<=M;i++)data[i]=0LL;}
	void Add(int i,const LL &v){while(i<=M)data[i]+=v,i+=(i&(-i));}
	LL Query(int i){LL a=0LL;while(i)a+=data[i],i-=(i&(-i));return a;} 
};
LL STD[100000],SCORE[100000];
vector<ModifyType>MODIFY;
set<int>FARMS[100000];
void AddScore(const int assistant,ModifyType &modify,LL sign)
{
	auto it=FARMS[assistant].upper_bound(modify.r);
	if(it==FARMS[assistant].begin()||(*--it)<modify.l)return;
	SCORE[assistant]+=sign*modify.cost;
}
void Query(const vector<int>&assistants,const int l,const int r,Bit &bit)
{
	if(l==r){for(const int a:assistants)ANS[a]=r;return;}
	vector<pair<int,int> >farms;
	for(const int p:assistants)
	{
		for(auto it=FARMS[p].begin();it!=FARMS[p].end();)
		{
			const int a=*it++;
			const int b=(it==FARMS[p].end()?M+1:*it);
			farms.push_back(make_pair(a,b));
		}
	}
	vector<ModifyType>modifys;
	const int mid=(l+r)/2;
	for(int i=l;i<=mid;i++)modifys.push_back(MODIFY[i]);
	sort(farms.begin(),farms.end());
	sort(modifys.begin(),modifys.end());
	vector<int>left_assist,right_assist;
	if(true)
	{
		int i=-1;
		vector<pair<int,LL> >changes;
		for(const auto farm:farms)
		{
			while(i+1<(int)modifys.size()&&modifys[i+1].l<=farm.first)i++,bit.Add(modifys[i].r,modifys[i].cost);
			const auto &change=make_pair(MANAGER[farm.first],bit.Query(farm.second-1)-bit.Query(farm.first-1));
			SCORE[change.first]+=change.second;
			changes.push_back(change);
		}
		set<int>except;
		for(const int p:assistants)
		{
			if(SCORE[p]>=STD[p])left_assist.push_back(p);
			else right_assist.push_back(p),except.insert(p);
		}
		while(i>=0)bit.Add(modifys[i].r,-modifys[i].cost),i--;
		for(const auto &change:changes)if(except.find(change.first)==except.end())SCORE[change.first]-=change.second;
	}
	Query(left_assist,l,mid,bit);
	Query(right_assist,mid+1,r,bit);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)FARMS[i].clear();
		for(int i=0;i<N;i++)scanf("%lld",&STD[i]);
		for(int i=1;i<=M;i++)scanf("%d",&MANAGER[i]),FARMS[--MANAGER[i]].insert(i);
		MODIFY.clear();
		int querycount;scanf("%d",&querycount);
		for(int l,r,cost;querycount--;)
		{
			scanf("%d%d%d",&l,&r,&cost);
			MODIFY.push_back(ModifyType(l,r,cost));
		}
		vector<int>assistants;
		for(int i=0;i<N;i++)assistants.push_back(i),SCORE[i]=0LL;
		static Bit bit;bit.clear();
		Query(assistants,0,MODIFY.size(),bit);
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]==(int)MODIFY.size()?-1:ANS[i]+1);
		}
		puts("");
	}
	return 0;
}

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
};
int N,M,MANAGER[100000],ANS[100000];
LL STD[100000],SCORE[100000];
vector<ModifyType>MODIFY;
set<int>FARMS[100000];
void AddScore(const int assistant,ModifyType &modify,LL sign)
{
	auto it=FARMS[assistant].upper_bound(modify.r);
	if(it==FARMS[assistant].begin()||(*--it)<modify.l)return;
	SCORE[assistant]+=sign*modify.cost;
}
void Query(const vector<int>&assistants,const int l,const int r)
{
	if(l==r){for(const int a:assistants)ANS[a]=r;return;}
	const int mid=(l+r)/2;
	vector<int>left_assist,right_assist;
	for(const int a:assistants)
	{
		for(int i=l;i<=mid;i++)AddScore(a,MODIFY[i],1LL);
		if(SCORE[a]>=STD[a])
		{
			for(int i=l;i<=mid;i++)AddScore(a,MODIFY[i],-1LL);
			left_assist.push_back(a);
		}
		else right_assist.push_back(a);
	}
	Query(left_assist,l,mid),Query(right_assist,mid+1,r);
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
		for(int i=0;i<M;i++)scanf("%d",&MANAGER[i]),FARMS[--MANAGER[i]].insert(i);
		MODIFY.clear();
		int querycount;scanf("%d",&querycount);
		for(int l,r,cost;querycount--;)
		{
			scanf("%d%d%d",&l,&r,&cost),l--,r--;
			MODIFY.push_back(ModifyType(l,r,cost));
		}
		vector<int>assistants;
		for(int i=0;i<N;i++)assistants.push_back(i),SCORE[i]=0LL;
		Query(assistants,0,MODIFY.size());
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]==(int)MODIFY.size()?-1:ANS[i]+1);
		}
		puts("");
	}
	return 0;
}

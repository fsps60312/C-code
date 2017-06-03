#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int RIVEREND=500000;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,U,D,HOME;
struct Show
{
	int time,locate,earn;
	Show(){}
	Show(const int _t,const int _l,const int _e):time(_t),locate(_l),earn(_e){}
	bool operator<(const Show &s)const{return time<s.time;}
};
vector<Show>SHOW;
struct CostType
{
	int s[2000000];
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		assert(l<=loc&&loc<=r);
		if(l==r){s[id]=val;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Modify(id*2,l,mid,loc,val);
		else Modify(id*2+1,mid+1,r,loc,val);
		s[id]=min(s[id*2],s[id*2+1]);
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return INF;
		if(bl<=l&&r<=br)return s[id];
		const int mid=(l+r)/2;
		return min(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
	void Set(const int i,const int val){Modify(1,0,RIVEREND,i,val);}
	int GetMin(const int l,const int r){return Query(1,0,RIVEREND,l,r);}
}COST[2];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(4,"%d%d%d%d",&N,&U,&D,&HOME);
	HOME--;
	SHOW.clear();
	for(int i=0;i<N;i++)
	{
		static int t,l,m;scanf(3,"%d%d%d",&t,&l,&m);
		SHOW.push_back(Show(t,--l,m));
	}
	sort(SHOW.begin(),SHOW.end());
	for(int loc=0;loc<=RIVEREND;loc++)
	{
		if(loc<=HOME)COST[0].Set(loc,HOME*U),COST[1].Set(loc,(HOME-loc)*U+(RIVEREND-loc)*D);
		else COST[0].Set(loc,(loc-HOME)*D+loc*U),COST[1].Set(loc,(RIVEREND-HOME)*D);
	}
	int ans=0;
	for(const Show &s:SHOW)
	{
		const int mincost=min(COST[1].GetMin(0,s.locate)-(RIVEREND-s.locate)*D,COST[0].GetMin(s.locate,RIVEREND)-s.locate*U)-s.earn;
		getmin(ans,mincost+(s.locate<HOME?(HOME-s.locate)*D:(s.locate-HOME)*U));
		COST[0].Set(s.locate,mincost+s.locate*U);
		COST[1].Set(s.locate,mincost+(RIVEREND-s.locate)*D);
	}
	printf("%d\n",-ans);
	return 0;
}

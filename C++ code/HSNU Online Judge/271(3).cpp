#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
#include<map>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int RIVEREND=500000;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N,U,D,HOME;
map<int,map<int,int> >SHOW;
struct Bst
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
}BST[2];
void SetUpCost(const int loc,const int cost){BST[0].Set(loc,cost+loc*U);}
void SetDownCost(const int loc,const int cost){BST[1].Set(loc,cost+(RIVEREND-loc)*D);}
void UpdateCost(const int loc,const int cost){SetUpCost(loc,cost),SetDownCost(loc,cost);}
int GetUpCost(const int now){return BST[0].GetMin(now,RIVEREND)-now*U;}
int GetDownCost(const int now){return BST[1].GetMin(0,now)-(RIVEREND-now)*D;}
int Cost(const int from,const int to){return to>from?(to-from)*D:(from-to)*U;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(4,"%d%d%d%d",&N,&U,&D,&HOME);
	HOME--;
	SHOW.clear();
	for(int i=0;i<N;i++)
	{
		static int t,l,m;scanf(3,"%d%d%d",&t,&l,&m);
		l--;
		auto it0=SHOW.find(t);
		if(it0!=SHOW.end())
		{
			auto it1=(it0->second).find(l);
			if(it1==(it0->second).end())(it0->second)[l]=m;
			else it1->second+=m;
		}
		else SHOW[t][l]=m;
	}
	for(int loc=0;loc<=RIVEREND;loc++)UpdateCost(loc,Cost(HOME,loc));
	int ans=0;
	for(const auto &it0:SHOW)
	{
//		if((int)it0.second.size()==1)
//		{
//			const auto it1=it0.second.begin();
//			const int loc=it1->first,earn=it1->second;
//			const int mincost=min(GetUpCost(loc),GetDownCost(loc))-earn;
//			getmin(ans,mincost+Cost(loc,HOME));
//			UpdateCost(loc,mincost);
//		}
//		else
//		{
			vector<int>loc,earn,turn_up_around,turn_down_around,min_up_cost,min_down_cost;
			#define tua turn_up_around
			#define tda turn_down_around
			#define muc min_up_cost
			#define mdc min_down_cost
			#define pb(x) push_back(x)
			for(const auto &it:it0.second)loc.pb(it.first),earn.pb(it.second),tua.pb(INF),tda.pb(INF),muc.pb(INF),mdc.pb(INF);
			#undef pb
			for(int i=1,anow=tua[i-1]=0,mnow=mdc[i-1]=GetDownCost(loc[i-1]);i<(int)tua.size();i++)
			{
				anow+=(loc[i]-loc[i-1])*(U+D)-earn[i-1];
				anow=tua[i]=min(anow,0);
				mnow+=Cost(loc[i-1],loc[i])-earn[i-1];
				mnow=mdc[i]=min(mnow,GetDownCost(loc[i]));
			}
			for(int i=(int)tda.size()-2,anow=tda[i+1]=0,mnow=muc[i+1]=GetUpCost(loc[i+1]);i>=0;i--)
			{
				anow+=(loc[i+1]-loc[i])*(U+D)-earn[i+1];
				anow=tda[i]=min(anow,0);
				mnow+=Cost(loc[i+1],loc[i])-earn[i+1];
				mnow=muc[i]=min(mnow,GetUpCost(loc[i]));
			}
			vector<int>updates;
			for(int i=0;i<(int)loc.size();i++)
			{
				const int mincost=min(muc[i]+tua[i],mdc[i]+tda[i])-earn[i];
				getmin(ans,mincost+Cost(loc[i],HOME));
				updates.push_back(mincost);
			}
			#undef tua
			#undef tda
			#undef muc
			#undef mdc
			for(int i=0;i<(int)updates.size();i++)UpdateCost(loc[i],updates[i]);
//		}
	}
	printf("%d\n",-ans);
	return 0;
}

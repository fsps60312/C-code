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
	int s[500001];
	int &operator[](const int i){return s[i];}
	int GetMin(const int l,const int r)
	{
		int ans=INF;
		for(int i=l;i<=r;i++)getmin(ans,s[i]);
		return ans;
	}
}COST[2];
int main()
{
	freopen("in.txt","r",stdin);
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
		if(loc<=HOME)COST[0][loc]=HOME*U,COST[1][loc]=(HOME-loc)*U+(RIVEREND-loc)*D;
		else COST[0][loc]=(loc-HOME)*D+loc*U,COST[1][loc]=(RIVEREND-HOME)*D;
	}
	int ans=0;
	for(const Show &s:SHOW)
	{
		const int mincost=min(COST[1].GetMin(0,s.locate)-(RIVEREND-s.locate)*D,COST[0].GetMin(s.locate,RIVEREND)-s.locate*U)-s.earn;
		getmin(ans,mincost+(s.locate<HOME?(HOME-s.locate)*D:(s.locate-HOME)*U));
		COST[0][s.locate]=mincost+s.locate*U;
		COST[1][s.locate]=mincost+(RIVEREND-s.locate)*D;
	}
	printf("%d\n",-ans);
	return 0;
}

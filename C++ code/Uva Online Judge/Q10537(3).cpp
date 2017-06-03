#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#define LL long long
using namespace std;
vector<LL> CITY[52];
LL idx(char *a){return a[0]>='a'?a[0]-'a'+26:a[0]-'A';}
LL VIS[52],PRE[52];
LL adtol(LL cargo,LL p)
{
	if(p>=26)return cargo+1;
	return cargo+(cargo+18)/19;
}
struct Trip
{
	LL x,y,pre;
	bool operator<(Trip a)const{return x>a.x||(x==a.x&&y>a.y);}
};
LL solve(LL cargo,LL sp,LL ep)
{
	priority_queue<Trip> pq;
	pq.push((Trip){cargo,ep,52});
	while(!pq.empty())
	{
		Trip t=pq.top();pq.pop();
		if(VIS[t.y])continue;
		VIS[t.y]=1;
		PRE[t.y]=t.pre;
		if(t.y==sp)return t.x;
		for(LL i=0;i<CITY[t.y].size();i++)
		{
			LL j=CITY[t.y][i];
			pq.push((Trip){adtol(t.x,t.y),j,t.y});
		}
	}
	return -1;
}
void putname(LL u)
{
	if(u>=26)printf("%c",'a'-26+u);
	else printf("%c",'A'+u);
}
void dfsprint(LL u)
{
	putname(u);
	if(PRE[u]==52)return;
	printf("-");
	dfsprint(PRE[u]);
}
void init()
{
	for(LL i=0;i<52;i++)
	{
		VIS[i]=0;
		CITY[i].clear();
	}
}
int main()
{
	LL m,kase=1;
	while(scanf("%lld",&m)==1&&m!=-1)
	{
		init();
		while(m--)
		{
			char c1[2],c2[2];scanf("%s%s",c1,c2);
			LL a=idx(c1),b=idx(c2);
			CITY[a].push_back(b);
			CITY[b].push_back(a);
		}
		LL a;char c1[2],c2[2];scanf("%lld%s%s",&a,c1,c2);
		LL sp=idx(c1),ep=idx(c2);
		printf("Case %lld:\n%lld\n",kase++,solve(a,sp,ep));
		dfsprint(sp);printf("\n");
	}
	return 0;
}

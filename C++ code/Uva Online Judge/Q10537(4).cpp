#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#define LL long long
using namespace std;
vector<LL> CITY[52];
LL idx(char *a){return a[0]>='a'?a[0]-'a'+26:a[0]-'A';}
LL PRE[52],ANS[52];
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
	pq.push((Trip){cargo,ep,-1});
	while(!pq.empty())
	{
		Trip t=pq.top();pq.pop();
		if(t.x>ANS[t.y])continue;
		if(t.pre>=PRE[t.y])continue;
		PRE[t.y]=t.pre;
		if(t.x<ANS[t.y])ANS[t.y]=t.x;
		for(LL i=0;i<CITY[t.y].size();i++)
		{
			LL j=CITY[t.y][i];
			pq.push((Trip){adtol(t.x,t.y),j,t.y});
		}
	}
	return ANS[sp];
}
void putname(LL u)
{
	if(u>=26)printf("%c",'a'-26+u);
	else printf("%c",'A'+u);
}
void dfsprint(LL u)
{
	putname(u);
	if(PRE[u]==-1)return;
	printf("-");
	dfsprint(PRE[u]);
}
void init()
{
	for(LL i=0;i<52;i++)
	{
		PRE[i]=52;
		CITY[i].clear();
		ANS[i]=9999999999LL;
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

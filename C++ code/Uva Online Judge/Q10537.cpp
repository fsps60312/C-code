#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
vector<int> CITY[52];
int idx(char *a){return a[0]>='a'?a[0]-'a':a[0]-'A'+26;}
int VIS[52],PRE[53];
int adtol(int cargo,int p)
{
	if(p<26)return cargo+1;
	return cargo+(cargo+18)/19;
}
struct Trip
{
	int x,y,pre;
	bool operator<(Trip a)const{return x>a.x;}
};
int solve(int cargo,int sp,int ep)
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
		for(int i=0;i<CITY[t.y].size();i++)
		{
			int j=CITY[t.y][i];
			pq.push((Trip){adtol(t.x,t.y),j,t.y});
		}
	}
	return -1;
}
void putname(int u)
{
	if(u<26)printf("%c",'a'+u);
	else printf("%c",'A'-26+u);
}
void dfsprint(int u)
{
	putname(u);
	if(PRE[u]==52)return;
	printf("-");
	dfsprint(PRE[u]);
}
void init()
{
	for(int i=0;i<52;i++)
	{
		VIS[i]=0;
		CITY[i].clear();
	}
}
int main()
{
	int m,kase=1;
	while(scanf("%d",&m)==1&&m!=-1)
	{
		init();
		while(m--)
		{
			char c1[2],c2[2];scanf("%s%s",c1,c2);
			int a=idx(c1),b=idx(c2);
			CITY[a].push_back(b);
			CITY[b].push_back(a);
		}
		int a;char c1[2],c2[2];scanf("%d%s%s",&a,c1,c2);
		int sp=idx(c1),ep=idx(c2);
		printf("Case %d:\n%d\n",kase++,solve(a,sp,ep));
		dfsprint(sp);printf("\n");
	}
	return 0;
}

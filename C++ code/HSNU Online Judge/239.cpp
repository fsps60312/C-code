#include<cstdio>
#include<vector>
#include<cassert>
#include<stack>
using namespace std;
typedef long long LL;
const LL MOD=1000000000LL;
int N,M,K;
vector<int>ET[200000];
int CX[100000],CY[100000];
struct Dot
{
	int x,y,c;
}DOT[100000];
int VIS[100000],KASE,COLOR[100000];
struct Change
{
	int u,c;
	Change(){}
	Change(const int _u,const int _c):u(_u),c(_c){}
};
stack<Change>CHANGE;
void Recovery(const int sz)
{
	while(CHANGE.size()>sz)
	{
		const Change c=CHANGE.top();CHANGE.pop();
		COLOR[c.u]=c.c;
	}
}
void MarkCOLOR(const int u,const int c)
{
	if(VIS[u]==KASE)return;
	VIS[u]=KASE;
	assert(COLOR[u]!=c);
	CHANGE.push(Change(u,COLOR[u]));
	COLOR[u]=c;
	for(int i=0;i<ET[u].size();i++)
	{
		const Dot &d=DOT[ET[u][i]];
		MarkCOLOR(d.x,c),MarkCOLOR(N+d.y,c);
	}
}
int OC;
bool Dfs(const int u,const int c)
{
	if(COLOR[u]==(c^1))return false;
	if(COLOR[u]==c)return true;
//	if(COLOR[u]!=-1)printf("COLOR[%d]=%d\n",u,COLOR[u]);
	assert(COLOR[u]==-1);
	CHANGE.push(Change(u,COLOR[u]));
	COLOR[u]=c;
	for(int i=0;i<ET[u].size();i++)
	{
		const Dot &d=DOT[ET[u][i]];
		const int expcolor=((d.x&1)&&(d.y&1)?OC^1:OC);
		const int nxt=(u<N?N+d.y:d.x);
		//expcolor^(OC^c)^(OC^nxtcolor)==0
		if(!Dfs(nxt,expcolor^c))return false;
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<N+M;i++)COLOR[i]=-1,ET[i].clear(),VIS[i]=0;
	KASE=0;
	for(int i=0;i<K;i++)
	{
		int &x=DOT[i].x,&y=DOT[i].y,&c=DOT[i].c;
		scanf("%d%d%d",&x,&y,&c);
//		printf("(%d,%d,%d)\n",x,y,c);
//		for(int j=0;j<N+M;j++)printf("%d",COLOR[j]);puts("");
		x--,y--;
//		printf("COLOR[%d]=%d,c=%d,c^1=%d\n",N+y,COLOR[N+y],c,c^1);
		if(x==0)assert(COLOR[N+y]!=(c^1)),COLOR[N+y]=c;
		if(y==0)assert(COLOR[x]!=(c^1)),COLOR[x]=c;
		if(x>=1&&y>=1)ET[x].push_back(i),ET[N+y].push_back(i);
	}
//	puts("pass");
	LL ans=0LL;
	for(int c=0;c<=1;c++)
	{
		if(COLOR[0]==(c^1))continue;
		OC=c;
		LL ta1=1LL;
		for(int i=1;i<N+M;i++)
		{
			if(i==N||COLOR[i]==-2)continue;
//			printf("i=%d\n",i);
//			if(i<N)printf("R%d\n",i+1);
//			else printf("C%d\n",i-N+1);
			LL ta2=0LL;
			int sz=CHANGE.size();
//			puts("1st");
			if(Dfs(i,0))ta2++;
			Recovery(sz);
//			puts("2st");
			if(Dfs(i,1))ta2++;
			KASE++;
			MarkCOLOR(i,-2);
//			printf("ta2=%lld\n",ta2);
			ta1*=ta2,ta1%=MOD;
		}
		ans+=ta1;
		Recovery(0);
	}
	printf("%lld\n",ans);
//000000
//010101
//000000
//010101
//000000
//010101
	return 0;
}

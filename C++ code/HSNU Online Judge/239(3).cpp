#include<cstdio>
#include<vector>
#include<cassert>
#include<stack>
using namespace std;
//void assert(bool valid){if(valid)return;for(;;)putchar('E');for(int a=0,b=0;;)a/=b;}
//void massert(bool valid){if(valid)return;for(;;)putchar('E');}
typedef long long LL;
const LL MOD=1000000000LL;
int N,M,K;
vector<int>ET[200000];
struct Dot
{
	int x,y,c;
}DOT[100000];
int VIS[200000],KASE,COLOR[200000];
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
	assert(COLOR[u]==-1);
	CHANGE.push(Change(u,COLOR[u]));
	COLOR[u]=c;
	for(int i=0;i<ET[u].size();i++)
	{
		const Dot &d=DOT[ET[u][i]];
		const int expcolor=((d.x&1)&&(d.y&1)?OC^1:OC);
//		printf("expcolor=%d\n",expcolor);
		if(u<N)assert(u==d.x);
		else assert(u==N+d.y);
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
	vector<int>didx;
	for(int i=0;i<K;i++)
	{
		int &x=DOT[i].x,&y=DOT[i].y,&c=DOT[i].c;
		scanf("%d%d%d",&x,&y,&c);
		x--,y--;
		assert(x>=0&&x<N&&y>=0&&y<M&&(c==0||c==1));
		if(x==0)assert(COLOR[N+y]!=(c^1)),COLOR[N+y]=c;
		if(y==0)assert(COLOR[x]!=(c^1)),COLOR[x]=c;
		if(x>=1&&y>=1)ET[x].push_back(i),ET[N+y].push_back(i),didx.push_back(i);
	}
	static int backup[200000];
	for(int i=0;i<N+M;i++)backup[i]=COLOR[i];
	LL ans=0LL;
	for(int c=0;c<=1;c++)
	{
		if(COLOR[0]==(c^1))continue;
		OC=c;
		LL ta1=1LL;
		bool valid=true;
		for(int i=0;i<didx.size();i++)
		{
			const Dot &d=DOT[didx[i]];
			if(COLOR[d.x]==-1||COLOR[N+d.y]==-1)continue;
			const int expcolor=((d.x&1)&&(d.y&1)?OC^1:OC);
			if((COLOR[d.x]^COLOR[N+d.y])!=(expcolor^d.c)){valid=false;break;}
		}
		if(!valid)continue;
		for(int i=1;i<N+M;i++)
		{
			if(i==N||COLOR[i]==-2)continue;
			LL ta2=0LL;
			int sz=CHANGE.size();
			if(Dfs(i,0))ta2++;
			Recovery(sz);
			if(Dfs(i,1))ta2++;
			Recovery(sz);
			KASE++;
			MarkCOLOR(i,-2);
			ta1*=ta2,ta1%=MOD;
		}
		ans+=ta1,ans%=MOD;
		Recovery(0);
	}
	printf("%lld\n",ans);
	for(int i=0;i<N+M;i++)assert(backup[i]==COLOR[i]);
//000000
//010101
//000000
//010101
//000000
//010101
	return 0;
}

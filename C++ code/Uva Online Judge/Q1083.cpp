#include<cstdio>
#include<cstdlib>
#include<vector>
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
int N,M,VIS[50001],IN[50001],OUT[50001],MAX;
struct Pair
{
	int x,y;
	Pair operator+(int a){return (Pair){x+a,y+a};}
};
struct Edge
{
	int from,to,val,lsum,ssum;
	Pair down,up;
	void init(int f,int t,int v){from=f,to=t,val=v;}
	bool allthesame(){return down.x+up.x==down.y+up.y;}
};
vector<Edge> EDGE;
vector<int> TO[50001],FROM[50001];
Pair dfsdown(int u,int val)
{
	Pair &ans=EDGE[u].down;
	if(VIS[u])return ans+val;
	VIS[u]=1;
	int to=EDGE[u].to;
	ans=(Pair){EDGE[u].val,EDGE[u].val};
	if(!TO[to].size())return ans+val;
	ans=dfsdown(TO[to][0],EDGE[u].val);
	for(int i=1;i<TO[to].size();i++)
	{
		int idx=TO[to][i];
		Pair p=dfsdown(idx,val+EDGE[u].val);
		ans.x=min(ans.x,p.x-val);
		ans.y=max(ans.y,p.y-val);
	}
	return ans+val;
}
Pair dfsup(int u,int val)
{
	Pair &ans=EDGE[u].up;
	if(VIS[u])return ans+val;
	VIS[u]=1;
	int from=EDGE[u].from;
	ans=(Pair){EDGE[u].val,EDGE[u].val};
	if(!FROM[from].size())return ans+val;
	ans=dfsup(FROM[from][0],EDGE[u].val);
	for(int i=0;i<FROM[from].size();i++)
	{
		int idx=FROM[from][i];
		Pair p=dfsup(idx,val+EDGE[u].val);
		ans.x=min(ans.x,p.x-val);
		ans.y=max(ans.y,p.y-val);
	}
	return ans+val;
}
vector<Pair> ANS;
bool dfsans(int u)
{
	//printf("u=%d,(%d,%d)\n",u,EDGE[u].ssum,EDGE[u].lsum);
	if(VIS[u])return true;
	VIS[u]=1;
	if(EDGE[u].ssum==EDGE[u].lsum)
	{
		if(MAX==EDGE[u].lsum)return true;
		ANS.push_back((Pair){u+1,MAX-EDGE[u].lsum});
		for(int i=ANS.size()-1;i>0;i--)
		{
			Pair &a=ANS[i],&b=ANS[i-1];
			if(a.x>b.x)break;
			Pair t=a;
			a=b;
			b=t;
		}
		return true;
	}
	int to=EDGE[u].to;
	if(!OUT[to])return false;
	for(int i=0;i<TO[to].size();i++)
	{
		int idx=TO[to][i];
		if(!dfsans(idx))return false;
	}
	return true;
}
void solve()
{
	ANS.clear();
	for(int i=0;i<M;i++)VIS[i]=0;
	for(int i=0;i<M;i++)
	{
		if(IN[EDGE[i].from])continue;
		if(!dfsans(i))
		{
			printf(" No solution\n");
			return;
		}
	}
	printf(" %d %d\n",ANS.size(),MAX);
	for(int i=0;i<ANS.size();i++)printf("%d %d\n",ANS[i].x,ANS[i].y);
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		EDGE.clear();
		for(int i=1;i<=N;i++)
		{
			TO[i].clear();
			FROM[i].clear();
			IN[i]=OUT[i]=0;
		}
		for(int i=0;i<M;i++)
		{
			int a,b,val;scanf("%d%d%d",&a,&b,&val);
			Edge e;
			e.init(a,b,val);
			EDGE.push_back(e);
			TO[a].push_back(i);
			FROM[b].push_back(i);
			IN[b]++,OUT[a]++;
		}
		for(int i=0;i<M;i++)VIS[i]=0;
		for(int i=0;i<M;i++)if(!IN[i])
		{
			for(int ti=0;ti<TO[i].size();ti++)
			dfsdown(TO[i][ti],0);
		}
		for(int i=0;i<M;i++)VIS[i]=0;
		for(int i=0;i<M;i++)if(!OUT[i])
		{
			for(int ti=0;ti<FROM[i].size();ti++)
			dfsup(FROM[i][ti],0);
		}
		MAX=0;
		for(int i=0;i<M;i++)
		{
			EDGE[i].ssum=EDGE[i].up.x+EDGE[i].down.x-EDGE[i].val;
			EDGE[i].lsum=EDGE[i].up.y+EDGE[i].down.y-EDGE[i].val;
			MAX=max(MAX,EDGE[i].lsum);
		}
		printf("Case %d:",kase++);
		/*for(int i=0;i<M;i++)
		{
			Pair down=EDGE[i].down,up=EDGE[i].up;
			printf("%d:%d->%d\t%d,%d\t%d,%d\n",i+1,EDGE[i].from,EDGE[i].to,down.x,down.y,up.x,up.y);
		}*/
		solve();
	}
	return 0;
}

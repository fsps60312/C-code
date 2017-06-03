#include<cstdio>
//#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
void bssert(bool valid){if(valid)return;for(;;);}
void getmin(int &a,const int b){if(b<a)a=b;}
struct Hungary
{
	bool VA[15],VB[15];
	int N,WA[15],WB[15],MATCH[15],LOW[15],EDGE[15][15];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)if(EDGE[u][nxt]!=INF)//Got AC after add this if
		{
			if(EDGE[u][nxt]==WA[u]+WB[nxt])
			{
				VB[nxt]=true;
				if(MATCH[nxt]==-1||Match(MATCH[nxt]))
				{
					MATCH[nxt]=u;
					return true;
				}
			}
			else assert(EDGE[u][nxt]>WA[u]+WB[nxt]),getmin(LOW[nxt],EDGE[u][nxt]-WA[u]-WB[nxt]);
		}
		return false;
	}
	void Update()
	{
		int low=INF;
		for(int i=0;i<N;i++)getmin(low,LOW[i]);
		bssert(low!=INF);
		for(int i=0;i<N;i++)if(VA[i])WA[i]+=low;
		for(int i=0;i<N;i++)if(VB[i])WB[i]-=low;
	}
	void Solve()
	{
		for(int i=0;i<N;i++)WA[i]=WB[i]=0,MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(;;)
			{
				for(int j=0;j<N;j++)VA[j]=VB[j]=false,LOW[j]=INF;
				if(Match(i))break;
				else Update();
			}
		}
	}
	int GetSum()
	{
		int ans=0;
		for(int i=0;i<N;i++)ans+=WA[i]+WB[i];
		return ans;
	}
}HUNGARY;
vector<int>BOX,TARGET;
int H,W;
char GRID[1600];
int Bfs(const int source,const int target)
{
	static int dist[1600];
	for(int i=0;i<W*H;i++)dist[i]=INF;
	queue<int>q;
	dist[source]=0,q.push(source);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(u==target)return dist[u];
		static int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		for(int i=0;i<4;i++)
		{
			int nxtr=u/W+d[i][0],nxtc=u%W+d[i][1];
			if(nxtr>=0&&nxtr<H&&nxtc>=0&&nxtc<W&&GRID[nxtr*W+nxtc]!='#')
			{
				const int nxtu=nxtr*W+nxtc;
				assert(GRID[nxtu]=='.');
				if(dist[nxtu]==INF)dist[nxtu]=dist[u]+1,q.push(nxtu);
			}
		}
	}
	return INF;
//	printf("source=%d,target=%d\n",source,target);
//	for(int i=0;i<H;i++)
//	{
//		for(int j=0;j<W;j++)putchar(GRID[i*W+j]);
//		puts("");
//	}
//	assert(0);
//	return -1;
}
int Solve()
{
	assert(BOX.size()==TARGET.size());
	const int &n=HUNGARY.N=BOX.size();
	assert(n<=15);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)HUNGARY.EDGE[i][j]=Bfs(BOX[i],TARGET[j]);
	HUNGARY.Solve();
	return HUNGARY.GetSum();
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&H,&W)==2);
		BOX.clear(),TARGET.clear();
		for(int i=0;i<W*H;i++)
		{
			char &c=GRID[i];
			bool found=false;
			for(;!found;)
			{
				c=getchar();
				assert(c!=-1);
				found=true;
				switch(c)
				{
					case'B':c='.',BOX.push_back(i);break;
					case'X':c='.',TARGET.push_back(i);break;
					case'#':
					case'.':break;
					default:found=false;break;
				}
			}
		}
		printf("%d\n",Solve());
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}

#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
#include<stack>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,M,A,B,D[4][2];
int GRID[900];
bool INQ[900];
stack<int>STK;
void Modify(const int u,const int v){assert(GRID[u]==0);STK.push(u);GRID[u]=v;}
void Recovery(const int sz){while((int)STK.size()>sz)GRID[STK.top()]=0,STK.pop();}
queue<int>Q;
void AddToQ(const int u){if(!INQ[u])Q.push(u);}
void Bfs()
{
	while(!Q.empty())
	{
		const int u=Q.front();Q.pop();
		INQ[u]=false;
		if(GRID[u]!=0)continue;
		const int r=u/M,c=u%M;
		int *cnt=new int[3]{0,0,0};
		vector<int>nxtus;
		for(int i=0;i<4;i++)
		{
			const int tr=r+D[i][0],tc=c+D[i][1],nxtu=tr*M+tc;
			if(tr<0||tc<0||tr>=N||tc>=M)continue;
			nxtus.push_back(nxtu);
			cnt[GRID[nxtu]+1]++;
		}
		const int sum=cnt[0]+cnt[1]+cnt[2];
		if(cnt[0]*2>=sum)Modify(u,1);
		else if(cnt[2]*2>=sum)Modify(u,-1);
		else{delete[]cnt;continue;}
		for(const int nxtu:nxtus)if(!INQ[nxtu])AddToQ(nxtu);
		delete[]cnt;
	}
}
int ANS;
void Dfs(const int u,const int color);
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(4,"%d%d%d%d",&N,&M,&A,&B);
		while(!STK.empty())STK.pop();
		while(!Q.empty())Q.pop();
		D[0][0]=D[1][0]=-A;
		D[2][0]=D[3][0]=A;
		D[0][1]=D[2][1]=-B;
		D[1][1]=D[3][1]=B;
		for(int i=0;i<N*M;i++)scanf(1,"%d",&GRID[i]),INQ[i]=false,AddToQ(i);
		Bfs();
		int ans=0;
		for(int i=0;i<A;i++)
		{
			for(int j=0;j<B;j++)
			{
				
			}
		}
		printf("%d\n",ans);
	}
	scanf(-1,"%d",&testcase);
	return 0;
}

#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
bool getmax(int &a,const int &b){if(b>a){a=b;return true;}return false;}
const int INF=2147483647;
int N,M;
char GRID[100][11];
struct State
{
	int s[10];
	State(){for(int i=0;i<M;i++)s[i]=0;}
	State(int v)
	{
		for(int i=0;i<M;i++,v/=3)s[i]=v%3;
	}
	int ToInt()
	{
		int ans=0;
		for(int i=0,now=1;i<M;i++,now*=3)ans+=now*s[i];
		return ans;
	}
	bool Move(const int &r,const int &c,State &t)
	{
		if(GRID[r][c]=='H')return false;
		assert(GRID[r][c]=='P');
		for(int i=c;i<=min(M-1,c+2);i++)if(s[i]>0)return false;
		for(int i=0;i<M;i++)t.s[i]=s[i];
		t.s[c]=2;
		for(int i=c+1;i<=min(M-1,c+2);i++)t.s[i]=1;
		return true;
	}
	bool Pass(const int &r,const int &c,State &t)
	{
		for(int i=0;i<M;i++)t.s[i]=s[i];
		if(t.s[c]>0)t.s[c]--;
		return true;
	}
};
int DP[2][59049];
int PRE[6][4][59049];
bool PUT[6][4][59049];
int main()
{
	freopen("in.txt","r",stdin);
//	M=10;
//	for(int i=0;i<59049;i++)assert(State(i).ToInt()==i);puts("pass");
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)scanf("%s",GRID[i]);
	int limit=1;for(int i=0;i<M;i++)limit*=3;
	for(int i=0;i<2;i++)for(int j=0;j<limit;j++)DP[i][j]=-INF;
	DP[0][0]=0;
	int d=0;
	for(int r=0;r<N;r++)
	{
		for(int c=0;c<M;c++,d^=1)
		{
//			printf("(%d,%d)\n",r,c);
			for(int i=0;i<limit;i++)
			{
				int &dp=DP[d][i];
				if(dp==-INF)continue;
				static State s,t;
				s=State(i);
				if(s.Move(r,c,t))if(getmax(DP[d^1][t.ToInt()],dp+1))
				{
					(c==M-1?PRE[r+1][0][t.ToInt()]:PRE[r][c+1][t.ToInt()])=i;
					(c==M-1?PUT[r+1][0][t.ToInt()]:PUT[r][c+1][t.ToInt()])=true;
				}
				if(s.Pass(r,c,t))if(getmax(DP[d^1][t.ToInt()],dp))
				{
					(c==M-1?PRE[r+1][0][t.ToInt()]:PRE[r][c+1][t.ToInt()])=i;
					(c==M-1?PUT[r+1][0][t.ToInt()]:PUT[r][c+1][t.ToInt()])=false;
				}
				dp=-INF;
			}
		}
	}
	int ans=0;
	for(int i=0;i<limit;i++)
	{
		if(DP[d][i]==7)printf("i=%d\n",i);
		if(i==55)
		{
			for(int j=0,u=i,r=N,c=0;j<N*M;j++)
			{
				int ans=u,put=PUT[r][c][u];
				u=PRE[r][c][u];
				c--;
				if(c<0)c+=M,r--;
				printf("(%d,%d):%d %d\n",r,c,ans,put);
			}
		}
	}//getmax(ans,DP[d][i]);
	printf("%d\n",ans);
	return 0;
}

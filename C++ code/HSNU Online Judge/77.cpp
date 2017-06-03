#include<cstdio>
#include<algorithm>
using namespace std;
void getmax(int &a,const int &b){if(b>a)a=b;}
const int INF=2147483647;
int N,M;
char GRID[100][11];
struct State
{
	int *s;
	State():s(new int[M]){for(int i=0;i<M;i++)s[i]=0;}
	State(int v):s(new int[M]){for(int i=0;i<M;i++,v/=3)s[i]=v%3;}
	int ToInt(){int ans=0;for(int i=0,now=1;i<M;i++,now*=3)ans+=now*s[i];return ans;}
	bool Move(const int &r,const int &c,State &t)
	{
		if(GRID[r][c]!='P')return false;
		for(int i=c;i<=min(M-1,c+2);i++)if(s[i])return false;
		for(int i=0;i<M;i++)t.s[i]=s[i];
		t.s[c]=2;
		for(int i=c+1;i<=min(M-1,c+2);i++)t.s[c]=1;
		return true;
	}
	bool Pass(const int &r,const int &c,State &t)
	{
		for(int i=0;i<M;i++)t.s[i]=s[i];
		if(t.s[c])t.s[c]--;
		return true;
	}
};
int DP[2][59049];
int main()
{
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
			State s,t;
			for(int i=0;i<limit;i++)
			{
				int &dp=DP[d][i];
				if(dp==-INF)continue;
				s=State(i);
				if(s.Move(r,c,t))getmax(DP[d^1][t.ToInt()],dp+1);
				if(s.Pass(r,c,t))getmax(DP[d^1][t.ToInt()],dp);
				dp=-INF;
			}
		}
	}
	printf("%d\n",DP[d][0]);
	return 0;
}

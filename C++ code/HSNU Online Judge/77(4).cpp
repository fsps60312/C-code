#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
void getmax(int &a,const int &b){if(b>a)a=b;}
const int INF=2147483647;
int N,M;
char GRID[100][11];
struct State
{
	int s[10];
	State(){for(int i=0;i<M;i++)s[i]=0;}
	State(int v){for(int i=0;i<M;i++,v/=3)s[i]=v%3;}
	int ToInt()
	{
		int ans=0;
		for(int i=M-1;i>=0;i--)ans*=3,ans+=s[i];
		return ans;
	}
	bool Move(const int &r,const int &c,State &t)
	{
		if(GRID[r][c]=='H')return false;
		assert(GRID[r][c]=='P');
		if(s[c]>0)return false;
		for(int i=0;i<M;i++)t.s[i]=s[i];
		getmax(t.s[c],2);
		for(int i=c;i<=min(M-1,c+2);i++)getmax(t.s[i],1);
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
int main()
{
//	freopen("in.txt","r",stdin);
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
			for(int i=0;i<limit;i++)
			{
				int &dp=DP[d][i];
				if(dp==-INF)continue;
				static State s,t;
				s=State(i);
				if(s.Move(r,c,t))getmax(DP[d^1][t.ToInt()],dp+1);
				if(s.Pass(r,c,t))getmax(DP[d^1][t.ToInt()],dp);
				dp=-INF;
			}
		}
	}
	int ans=0;
	for(int i=0;i<limit;i++)getmax(ans,DP[d][i]);
	printf("%d\n",ans);
	return 0;
}

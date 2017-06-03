#include<cstdio>
const int INF=2147483647-2;
int POW[11]={1,3,9,27,81,243,729,2187,6561,19683,59049};
int N,M,GRID[9][9];
int DP[9][9][59049];
struct State
{
	int *v,left;
	State():v(new int[9]),left(0){static int i;for(i=0;i<M;i++)v[i]=0;}
	int GetCode()
	{
		static int ans,i;
		ans=left;
		for(i=0;i<M;i++)ans*=3,ans+=v[i];
		return ans;
	}
	bool TryMove(int row,int col,int u,int d,int l,int r,State &t)
	{
		if((!col&&l)||(!row&&u))return false;
		if((col==M-1&&r)||(row==N-1&&d))return false;
		static bool hasl,hasu;
		hasl=(col&&left),hasu=(row&&v[col]);
		if((hasl&&left!=l)||(hasu&&v[col]!=u))return false;
		if((!hasl&&l)||(!hasu&&u))return false;
		static int i;
		for(i=0;i<M;i++)t.v[i]=v[i];
		t.v[col]=d;
		t.left=r;
		return true;
	}
}STATE[9][9];
void getmin(int &a,int b){if(b<a)a=b;}
int Solve(int r,int c,State &s)
{
	if(c==M)c=0,r++;
	if(r==N)return 0;
	int &dp=DP[r][c][s.GetCode()];
	if(dp!=-1)return dp;
	dp=INF;
	State &t=STATE[r][c];
	int &g=GRID[r][c];
	if(g<=1&&s.TryMove(r,c,0,0,0,0,t))getmin(dp,Solve(r,c+1,t));
	if(g==0)
	{
		for(int i=1;i<=2;i++)
		{
			if(s.TryMove(r,c,i,i,0,0,t))getmin(dp,Solve(r,c+1,t)+2);
			if(s.TryMove(r,c,i,0,i,0,t))getmin(dp,Solve(r,c+1,t)+2);
			if(s.TryMove(r,c,i,0,0,i,t))getmin(dp,Solve(r,c+1,t)+2);
			if(s.TryMove(r,c,0,i,i,0,t))getmin(dp,Solve(r,c+1,t)+2);
			if(s.TryMove(r,c,0,i,0,i,t))getmin(dp,Solve(r,c+1,t)+2);
			if(s.TryMove(r,c,0,0,i,i,t))getmin(dp,Solve(r,c+1,t)+2);
		}
	}
	else if(g>=1)
	{
		int i=g;i--;
		if(s.TryMove(r,c,i,0,0,0,t))getmin(dp,Solve(r,c+1,t)+1);
		if(s.TryMove(r,c,0,i,0,0,t))getmin(dp,Solve(r,c+1,t)+1);
		if(s.TryMove(r,c,0,0,i,0,t))getmin(dp,Solve(r,c+1,t)+1);
		if(s.TryMove(r,c,0,0,0,i,t))getmin(dp,Solve(r,c+1,t)+1);
	}
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		static int tmp[9][9];
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				scanf("%d",&tmp[i][j]);
			}
		}
		if(M<N)
		{
			for(int i=0,limit=POW[M+1];i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					GRID[i][j]=tmp[i][j];
					for(int k=0;k<limit;k++)DP[i][j][k]=-1;
				}
			}
		}
		else
		{
			static int t;t=M,M=N,N=t;
			for(int i=0,limit=POW[M+1];i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					GRID[i][j]=tmp[j][i];
					for(int k=0;k<limit;k++)DP[i][j][k]=-1;
				}
			}
		}
		State s=State();
		int ans=Solve(0,0,s);
		if(ans==INF)ans=0;
		printf("%d\n",ans/2);
	}
	return 0;
}

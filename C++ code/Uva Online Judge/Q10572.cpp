#include<cstdio>
int T,N,M,GRID[8][8];
int DP[8][8][1<<9];
struct State
{
	int v[8],ul;
	State(){for(int i=0;i<8;i++)v[i]=0;ul=0;}
	int GetCode(){int ans=ul;for(int i=0;i<N;i++)ans<<=1,ans+=v[i];return ans;}
	inline bool SameAs(int &a,int &b,int &c,int &v){return a==v&&b==v&&c==v;}
	bool TryMove(int row,int col,int c,State &t)
	{
		if(row&&col&&SameAs(v[col-1],v[col],ul,c))return false;
		for(int i=0;i<N;i++)t.v[i]=v[i];
		t.ul=t.v[col];t.v[col]=c;
		return true;
	}
}STATE[8][8];
int Solve(int r,int c,State &s)
{
	if(c==N)c=0,r++;
	if(r==M)return 1;
	int &dp=DP[r][c][s.GetCode()];
	if(dp!=-1)return dp;
	dp=0;
	State &t=STATE[r][c];
	if(GRID[r][c]!=1&&s.TryMove(r,c,0,t))dp+=Solve(r,c+1,t);
	if(GRID[r][c]!=0&&s.TryMove(r,c,1,t))dp+=Solve(r,c+1,t);
	return dp;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)while(T--)
	{
		scanf("%d%d",&M,&N);
		for(int i=0,limit=(1<<(N+1));i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				static char v;
				do
				{
					scanf("%c",&v);
				}while(v!='o'&&v!='#'&&v!='.');
				int &g=GRID[i][j];
				switch(v)
				{
					case'.':g=-1;break;
					case'o':g=0;break;
					default:g=1;break;
				}
				for(int k=0;k<limit;k++)DP[i][j][k]=-1;
			}
		}
//		for(int i=0;i<M;i++)
//		{
//			for(int j=0;j<N;j++)
//			{
//				printf("%d",GRID[i][j]+1);
//			}puts("");
//		}
		State s=State();
		printf("%d\n",Solve(0,0,s));
	}
	return 0;
}

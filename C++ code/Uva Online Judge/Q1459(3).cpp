#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
map<int,int>IDX;
bool BANROW[200];
int NOWSTEP[200];
struct Hungary
{
	int MA[200],MB[200];
	vector<int>EA[200];
	bool VA[200],VB[200];
	int LOWBOUND,N;
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(const int nxt:EA[u])if(!BANROW[nxt])
		{
			if(MB[nxt]!=-1&&MB[nxt]<LOWBOUND)MA[MB[nxt]]=-1,MB[nxt]=-1;
			VB[nxt]=true;
			if(MB[nxt]==-1||Match(MB[nxt]))
			{
				MB[nxt]=u;
				MA[u]=nxt;
				return true;
			}
		}
		return false;
	}
	bool Solve(const int lowbound)
	{
		LOWBOUND=lowbound;
		for(int i=LOWBOUND;i<N;i++)if(MA[i]!=-1&&BANROW[MA[i]])MB[MA[i]]=-1,MA[i]=-1;
		for(int now=LOWBOUND;now<N;now++)
		{
			if(MA[now]!=-1)continue;
			for(int i=LOWBOUND;i<N;i++)VA[i]=false;
			for(int i=0;i<N;i++)VB[i]=false;
			if(!Match(now))return false;
		}
		return true;
	}
}HUNGARY;
int ROW,COL,RANK,GRID[200][200],CNT;
bool Dfs(const int col,bool possible)
{
	if(col==COL)return ++CNT==RANK;
	if(!HUNGARY.Solve(col))return possible=false;
	for(const auto i:HUNGARY.EA[col])if(!BANROW[i])
	{
//		printf("col=%d,i=%d\n",col,i);
		NOWSTEP[col]=i;
		BANROW[i]=true;
		bool result=true;
		if(Dfs(col+1,result))return true;
		if(!result)return false;
		BANROW[i]=false;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d%d",&COL,&ROW,&RANK)==3);
		assert(RANK>=1);
		IDX.clear();
		for(int i=0;i<ROW;i++)for(int j=0;j<COL;j++)
		{
			int &v=GRID[i][j];
			assert(scanf("%d",&v)==1);
			IDX[v]=-1;
		}
		if(ROW==0)
		{
			assert(IDX.empty());
			for(int i=1;i<=COL;i++)IDX[i]=-1;
		}
		int cnt=0;
		for(auto &it:IDX)it.second=cnt++,assert(it.second==it.first-1);
		assert((int)IDX.size()==COL);
		for(int i=0;i<COL;i++)
		{
			static bool banned[200];
			for(int j=0;j<COL;j++)banned[j]=false;
			for(int j=0;j<ROW;j++)
			{
				bool &v=banned[GRID[j][i]=IDX[GRID[j][i]]];
				assert(v==false);
				v=true;
			}
			HUNGARY.MA[i]=HUNGARY.MB[i]=-1;
			HUNGARY.EA[i].clear();
			for(int j=0;j<COL;j++)if(!banned[j])HUNGARY.EA[i].push_back(j);
		}
		for(int i=0;i<COL;i++)BANROW[i]=false;
		static int kase=1;
		printf("Case #%d:",kase++);
		HUNGARY.N=COL;
		CNT=0;
		bool result=true;
		if(!Dfs(0,result))puts(" -1");
		else
		{
			for(int i=0;i<COL;i++)printf(" %d",NOWSTEP[i]+1);
			puts("");
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}

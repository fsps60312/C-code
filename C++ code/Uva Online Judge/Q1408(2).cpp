#include<cstdio>
//#include<cassert>
#include<vector>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int R,C,GRID[50][9],POW[10];
int DP[2][262144];
vector<int>ELE[2];
int GetBit(const int s,const int i){return s/POW[i]%4;}
bool Move(const int source,int &value,const int row,const int col,const int type)
{
	if(GRID[row][col]==0){value=0;return type==0;}
	if(type==0||type==2)
	{
		if(row==0){value=1;return true;}
		const int pretype=GetBit(source,col);
		if(pretype!=type||GRID[row-1][col]==0)value=1;
		else if(type==0)value=(GRID[row-1][col]<GRID[row][col]?0:1);
		else assert(type==2),value=(GRID[row-1][col]>GRID[row][col]?0:1);
		return true;
	}
	else if(type==1||type==3)
	{
		if(col==0){value=1;return true;}
		const int pretype=GetBit(source,col-1);
		if(pretype!=type||GRID[row][col-1]==0)value=1;
		else if(type==1)value=(GRID[row][col-1]>GRID[row][col]?0:1);
		else assert(type==3),value=(GRID[row][col-1]<GRID[row][col]?0:1);
		return true;
	}
	else assert(0);
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	POW[0]=1;
	for(int i=1;i<=9;i++)POW[i]=POW[i-1]*4;
	for(int i=0;i<262144;i++)DP[0][i]=DP[1][i]=INF;
	for(;;)
	{
		assert(scanf("%d%d",&R,&C)==2);
		if(R==0&&C==0)break;
		assert(C>=1&&C<=9);
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)assert(scanf("%d",&GRID[i][j])==1);
		assert(ELE[0].empty()&&ELE[1].empty());
//		for(int i=0;i<262144;i++)assert(DP[0][i]==INF&&DP[1][i]==INF);
		DP[0][0]=0,ELE[0].push_back(0);
		int d=0;
		for(int row=0,col=0;row<R;d^=1)
		{
			for(const auto now:ELE[d])
			{
//				printf("(%d,%d)now=%d\n",row,col,now);
				for(int type=0,value;type<4;type++)if(Move(now,value,row,col,type))
				{
					const int target=now/POW[col+1]*POW[col+1]+type*POW[col]+now%POW[col];
					if(DP[d^1][target]==INF)ELE[d^1].push_back(target);
					getmin(DP[d^1][target],DP[d][now]+value);
				}
				DP[d][now]=INF;
			}
			ELE[d].clear();
			if(++col==C)col=0,row++;
		}
		int ans=INF;
		for(const auto now:ELE[d])getmin(ans,DP[d][now]),DP[d][now]=INF;
		ELE[d].clear();
		static int kase=1;
		printf("Case %d: %d\n",kase++,ans);
	}
	assert(scanf("%d",&R)!=1);
	return 0;
}

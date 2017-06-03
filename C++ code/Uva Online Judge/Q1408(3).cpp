#include<cstdio>
//#include<cassert>
#include<vector>
#include<queue>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int R,C,GRID[50][9],POW[10];
int VIS[50][9][262144],VIS_CNT;
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
struct Pq
{
	int row,column,state,plane;
	Pq():row(0),column(0),state(0),plane(0){}
	Pq(const int _r,const int _c,const int _s,const int _p):row(_r),column(_c),state(_s),plane(_p){}
	bool operator<(const Pq &p)const
	{
		if(plane!=p.plane)return plane>p.plane;
		return false;
	}
};
int Solve()
{
	VIS_CNT++;
	priority_queue<Pq>pq;
	pq.push(Pq(0,0,0,0));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		const int row=p.row,col=p.column;
//		printf("(%d,%d,%d):%d\n",row,col,p.state,p.plane);
		if(row==R)return p.plane;
		if(VIS[row][col][p.state]==VIS_CNT)continue;
		VIS[row][col][p.state]=VIS_CNT;
		const int nxtr=(col+1==C?row+1:row),nxtc=(col+1)%C;
		for(int type=0,value;type<4;type++)if(Move(p.state,value,row,col,type))
		{
			const int target=p.state/POW[col+1]*POW[col+1]+type*POW[col]+p.state%POW[col];
			pq.push(Pq(nxtr,nxtc,target,p.plane+value));
		}
	}
	assert(0&&"No solution");
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	POW[0]=1;
	for(int i=1;i<=9;i++)POW[i]=POW[i-1]*4;
	for(int i=0;i<50;i++)for(int j=0;j<9;j++)for(int k=0;k<262144;k++)VIS[i][j][k]=0;
	VIS_CNT=0;
	for(;;)
	{
		assert(scanf("%d%d",&R,&C)==2);
		if(R==0&&C==0)break;
		assert(C>=1&&C<=9);
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)assert(scanf("%d",&GRID[i][j])==1);
		static int kase=1;
		printf("Case %d: %d\n",kase++,Solve());
	}
	assert(scanf("%d",&R)!=1);
	return 0;
}

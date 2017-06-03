#include<cstdio>
//#include<cassert>
//#define bssert(x) assert(x)
#include<vector>
using namespace std;
void assert(bool valid){if(valid)return;for(int a=0,b=0;;)a/=b,b/=a;}
void bssert(bool valid){if(valid)return;for(;;)putchar('E');}
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int R,C,GRID[50][9],POW[10];
int DP[2][19683];
vector<int>ELE[2];
int GetBit(const int s,const int i){return s/POW[i]%3;}
int MinTrace(const int row,const int c1,const int c2)
{
	if(c1-1==c2)return 0;
	if(c1==c2)return 1;
	assert(c1<c2);
	int *grid=GRID[row];
	for(int i=c1+1;i<=c2;i++)assert(grid[i-1]!=grid[i]);
	for(int i=c1;i<=c2;i++)assert(grid[i]);
	int ans=0;
	int idx=c1;
	while(idx<=c2)
	{
		int i;
		for(i=idx;i<c2&&(grid[i]>grid[i+1])==(grid[idx]>grid[idx+1]);i++);
		idx=i+1,ans++;
	}
//	printf("(%d,%d,%d):%d\n",row,c1,c2,ans);
	return ans;
}
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
	else if(type==1)
	{
		if(col==0){value=1;return true;}
		const int pretype=GetBit(source,col-1);
		if(pretype!=type)value=1;
		else
		{
			int l=col;
			while(l>0&&GetBit(source,l-1)==1&&GRID[row][l-1]!=GRID[row][l])l--;
			value=MinTrace(row,l,col)-MinTrace(row,l,col-1);
		}
		return true;
	}
	else assert(0);
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	POW[0]=1;
	for(int i=1;i<=9;i++)POW[i]=POW[i-1]*3;
	for(int i=0;i<19683;i++)DP[0][i]=DP[1][i]=INF;
	for(;;)
	{
		bssert(scanf("%d%d",&R,&C)==2);
		if(R==0&&C==0)break;
		bssert(C>=1&&C<=9);
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)bssert(scanf("%d",&GRID[i][j])==1);
		bssert(ELE[0].empty()&&ELE[1].empty());
		DP[0][0]=0,ELE[0].push_back(0);
		int d=0;
		for(int row=0,col=0;row<R;d^=1)
		{
			for(const auto now:ELE[d])
			{
//				printf("(%d,%d)now=%d\n",row,col,now);
				for(int type=0,value;type<3;type++)if(Move(now,value,row,col,type))
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
//	bssert(scanf("%d",&R)!=1);
	return 0;
}
/*
4 4
4 5 2 4
3 4 5 4
2 4 1 5
0 2 5 0

0 0
*/

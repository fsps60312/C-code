#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int R,C,GRID[50][9],POW[10];
int DP[2][19683];
vector<int>ELE[2];
int GetBit(const int s,const int i){return s/POW[i]%3;}
bool Move(const int source,int &value,const int row,const int col,const int type)
{
	if(GRID[row][col]==0){value=0;return type==0;}
	if(type==0)
	{
		if(col==0||GetBit(col-1)>0||GRID[row][col-1]==0||GRID[row][col-1]==GRID[row][col])value=1;
		else if(col==1||GetBit(col-2)>0||GRID[row][col-2]==0||GRID[row][col-2]==GRID[row][col-1]||(GRID[row][col-2]>GRID[row][col-1])==(GRID[row][col-1]>GRID[row][col]))value=0;
		else value=1;
	}
	else if(type==1)
	{
		
	}
}
int main()
{
	POW[0]=1;
	for(int i=1;i<=9;i++)POW[i]=POW[i-1]*3;
	for(int i=0;i<19683;i++)DP[0][i]=DP[1][i]=INF;
	for(;;)
	{
		assert(scanf("%d%d",&R,&C)==2);
		if(R==0&&C==0)break;
		assert(ELE[0].empty()&&ELE[1].empty());
		int d=0;
		for(int row=0,col=0;;,d^=1)
		{
			for(const auto now:ELE[d])
			{
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
			if(row==R)break;
		}
	}
	assert(scanf("%d",&R)!=1);
	return 0;
}

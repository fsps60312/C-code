#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct DisjointSets
{
	int DATA[150],SIZE[150];
	void Clear(const int n){for(int i=0;i<n;i++)DATA[i]=i,SIZE[i]=1;}
	int Find(const int a){return DATA[a]==a?a:(DATA[a]=Find(DATA[a]));}
	bool Merge(int a,int b)
	{
		if((a=Find(a))==(b=Find(b)))return false;
		SIZE[a]+=SIZE[b],SIZE[b]=0;
		DATA[b]=a;
		return true;
	}
	int Size(const int i){return SIZE[Find(i)];}
}DJ;
int R,C;
char GRID[10][16];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		R=10,C=15;
		for(int i=9;i>=0;i--)scanf("%s",GRID[i]);
		int final_score=0;
		static int kase=0;
		if(kase++)puts("");
		printf("Game %d:\n\n",kase);
		int movecount=1;
		for(;R||C;)
		{
			DJ.Clear(R*C);
			for(int i=1;i<R;i++)for(int j=0;j<C;j++)if(GRID[i][j]!='\0'&&GRID[i-1][j]==GRID[i][j])DJ.Merge((i-1)*C+j,i*C+j);
			for(int i=0;i<R;i++)for(int j=1;j<C;j++)if(GRID[i][j]!='\0'&&GRID[i][j-1]==GRID[i][j])DJ.Merge(i*C+(j-1),i*C+j);
			int loc=0;
			for(int j=0;j<C;j++)for(int i=0;i<R;i++)if(DJ.Size(i*C+j)>DJ.Size(loc))loc=i*C+j;
			const int count=DJ.Size(loc);
			if(count==1)break;
			printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",movecount++,loc/C+1,loc%C+1,count,GRID[loc/C][loc%C],(count-2)*(count-2));
			final_score+=(count-2)*(count-2);
			vector<vector<char> >grid;
			for(int x=0;x<C;x++)
			{
				vector<char>column;
				for(int i=0;i<R;i++)if(DJ.Find(i*C+x)!=DJ.Find(loc)&&GRID[i][x]!='\0')column.push_back(GRID[i][x]);
				if(column.empty())continue;
				grid.push_back(column);
			}
			R=0,C=grid.size();
			for(const vector<char>&column:grid)getmax(R,column.size());
			for(int x=0;x<C;x++)
			{
				const vector<char>&column=grid[x];
				for(int y=0;y<(int)column.size();y++)GRID[y][x]=column[y];
				for(int y=column.size();y<R;y++)GRID[y][x]='\0';
			}
		}
		int remain=0;
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)if(GRID[i][j]!='\0')remain++;
		if(remain==0)final_score+=1000;
		printf("Final score: %d, with %d balls remaining.\n",final_score,remain);
	}
	return 0;
}

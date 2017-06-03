#include<cstdio>
#include<cassert>
#include<utility>
#include<vector>
#include<set>
using namespace std;
bool VALID[9][9];
vector<pair<int,int> >LOCS;
int ID[9][9];
bool VIS[9][9];
int main()
{
	for(int i=0;i<=8;i++)for(int j=0;j<=8;j++)VALID[i][j]=false;
	for(int i=1;i<=2;i++)for(int j=3;j<=5;j++)VALID[i][j]=true,LOCS.push_back(make_pair(i,j));
	for(int i=3;i<=5;i++)for(int j=1;j<=7;j++)VALID[i][j]=true,LOCS.push_back(make_pair(i,j));
	for(int i=6;i<=7;i++)for(int j=3;j<=5;j++)VALID[i][j]=true,LOCS.push_back(make_pair(i,j));
	for(int i=0;i<(int)LOCS.size();i++)ID[LOCS[i].first][LOCS[i].second]=i;
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	puts("HI Q OUTPUT");
	while(testcount--)
	{
		for(int i=0;i<=8;i++)for(int j=0;j<=8;j++)VIS[i][j]=false;
		if(true)
		{
			int v;scanf("%d",&v),--v;
			for(;v!=-1;scanf("%d",&v),--v)VIS[LOCS[v].first][LOCS[v].second]=true;
		}
		for(;;)
		{
			set<int>dests;
			for(int i=0;i<=8;i++)for(int j=0;j<=8;j++)if(VALID[i][j]&&VIS[i][j])
			{
				if(VIS[i-1][j]&&!VIS[i-2][j]&&VALID[i-2][j])dests.insert(ID[i-2][j]);
				if(VIS[i+1][j]&&!VIS[i+2][j]&&VALID[i+2][j])dests.insert(ID[i+2][j]);
				if(VIS[i][j-1]&&!VIS[i][j-2]&&VALID[i][j-2])dests.insert(ID[i][j-2]);
				if(VIS[i][j+1]&&!VIS[i][j+2]&&VALID[i][j+2])dests.insert(ID[i][j+2]);
			}
			if(dests.empty())break;
			const int dest=*dests.rbegin();
//			printf("dest=%d\n",dest+1);
			const int y=LOCS[dest].first,x=LOCS[dest].second;
			VIS[y][x]=true;
			if(VIS[y+1][x]&&VIS[y+2][x])VIS[y+1][x]=VIS[y+2][x]=false;
			else if(VIS[y][x+1]&&VIS[y][x+2])VIS[y][x+1]=VIS[y][x+2]=false;
			else if(VIS[y][x-1]&&VIS[y][x-2])VIS[y][x-1]=VIS[y][x-2]=false;
			else if(VIS[y-1][x]&&VIS[y-2][x])VIS[y-1][x]=VIS[y-2][x]=false;
			else assert(0);
		}
		int ans=0;
		for(int i=0;i<=8;i++)for(int j=0;j<=8;j++)if(VIS[i][j])ans+=ID[i][j]+1;//,printf("ID[%d][%d]=%d\n",i,j,ID[i][j]+1);
		printf("%d\n",ans);
	}
	puts("END OF OUTPUT");
	return 0;
}

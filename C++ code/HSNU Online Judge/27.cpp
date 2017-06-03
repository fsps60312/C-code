#include<bits/stdc++.h>
using namespace std;
struct State
{
	int v[3][3],x,y;
	bool operator<(const State &s)const
	{
		static int i,j;
		for(i=0;i<3;i++)for(j=0;j<3;j++)if(v[i][j]!=s.v[i][j])return v[i][j]<s.v[i][j];
		return false;
	}
	bool operator==(const State &s)const
	{
		static int i,j;
		for(i=0;i<3;i++)for(j=0;j<3;j++)if(v[i][j]!=s.v[i][j])return false;
		return true;
	}
}GOAL,S;
set<State>VIS;
bool dfs1(State &s,int dep)
{
	if(VIS.find(s)!=VIS.end())return false;
	VIS.insert(s);
//for(int j=0;j<dep;j++)printf(" ");
//printf("%d\n",dep);
//for(int i=0;i<3;i++)
//{
//	for(int j=0;j<dep;j++)printf(" ");
//	for(int j=0;j<3;j++)printf(" %d",s.v[i][j]);
//	puts("");
//}
	if(s==GOAL)return true;
	if(dep==10)return false;
	if(s.x)
	{
		swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
		s.x--;
		if(dfs1(s,dep+1))return true;
		s.x++;
		swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
	}
	if(s.y)
	{
		swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
		s.y--;
		if(dfs1(s,dep+1))return true;
		s.y++;
		swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
	}
	if(s.x<2)
	{
		swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
		s.x++;
		if(dfs1(s,dep+1))return true;
		s.x--;
		swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
	}
	if(s.y<2)
	{
		swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
		s.y++;
		if(dfs1(s,dep+1))return true;
		s.y--;
		swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
	}
	return false;
}
bool dfs2(State &s,int dep)
{
	if(VIS.find(s)!=VIS.end())return true;
	if(dep==10)return false;
	if(s.x)
	{
		swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
		s.x--;
		if(dfs2(s,dep+1))return true;
		s.x++;
		swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
	}
	if(s.y)
	{
		swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
		s.y--;
		if(dfs2(s,dep+1))return true;
		s.y++;
		swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
	}
	if(s.x<2)
	{
		swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
		s.x++;
		if(dfs2(s,dep+1))return true;
		s.x--;
		swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
	}
	if(s.y<2)
	{
		swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
		s.y++;
		if(dfs2(s,dep+1))return true;
		s.y--;
		swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
	}
	return false;
}
bool Solve()
{
//	puts("dfs1");
	if(dfs1(S,0))return true;
//	puts("dfs2");
	return dfs2(GOAL,0);
}
int T;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		VIS.clear();
		for(int i=0;i<3;i++)for(int j=0;j<3;j++)GOAL.v[i][j]=i*3+j+1;
		GOAL.v[2][2]=0;
		GOAL.x=GOAL.y=2;
		for(int i=0;i<3;i++)for(int j=0;j<3;j++)
		{
			int &v=S.v[i][j];
			scanf("%d",&v);
			if(!v)S.x=i,S.y=j;
		}
		puts(Solve()?"Easy":"Hard");
//		break;
	}
	return 0;
}

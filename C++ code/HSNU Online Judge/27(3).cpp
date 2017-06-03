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
bool Bfs1(State &ini)
{
	queue<State>q;
	q.push(ini);
	for(int cnt=0;cnt<10;cnt++)
	{
		for(int i=q.size();i>0;i--)
		{
			State s=q.front();q.pop();
			if(VIS.find(s)!=VIS.end())continue;
			VIS.insert(s);
			if(s==GOAL)return true;
			if(s.x)
			{
				swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
				s.x--;
				q.push(s);
				s.x++;
				swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
			}
			if(s.y)
			{
				swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
				s.y--;
				q.push(s);
				s.y++;
				swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
			}
			if(s.x<2)
			{
				swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
				s.x++;
				q.push(s);
				s.x--;
				swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
			}
			if(s.y<2)
			{
				swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
				s.y++;
				q.push(s);
				s.y--;
				swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
			}
		}
	}
	return false;
}
bool Bfs2(State &ini)
{
	queue<State>q;
	q.push(ini);
	for(int cnt=0;cnt<10;cnt++)
	{
		for(int i=q.size();i>0;i--)
		{
			State s=q.front();q.pop();
			if(VIS.find(s)!=VIS.end())return true;
			if(s.x)
			{
				swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
				s.x--;
				q.push(s);
				s.x++;
				swap(s.v[s.x][s.y],s.v[s.x-1][s.y]);
			}
			if(s.y)
			{
				swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
				s.y--;
				q.push(s);
				s.y++;
				swap(s.v[s.x][s.y],s.v[s.x][s.y-1]);
			}
			if(s.x<2)
			{
				swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
				s.x++;
				q.push(s);
				s.x--;
				swap(s.v[s.x][s.y],s.v[s.x+1][s.y]);
			}
			if(s.y<2)
			{
				swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
				s.y++;
				q.push(s);
				s.y--;
				swap(s.v[s.x][s.y],s.v[s.x][s.y+1]);
			}
		}
	}
	return false;
}
bool Solve()
{
	if(Bfs1(S))return true;
	return Bfs2(GOAL);
}
int T;
int main()
{
//	freopen("in.txt","r",stdin);
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
//		for(int i=0;i<3;i++)for(int j=0;j<3;j++)printf(" %d",S.v[i][j]);puts("");
//		for(int i=0;i<3;i++)for(int j=0;j<3;j++)printf(" %d",GOAL.v[i][j]);puts("");
		puts(Solve()?"Easy":"Hard");
	}
	return 0;
}

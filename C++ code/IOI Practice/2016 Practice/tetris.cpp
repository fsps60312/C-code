#include "tetris.h"
#include<cstdio>
#include<cassert>
void PrintGrid(const int s)
{
//	return;
	for(int i=0,k=0;i<4;i++)
	{
		for(int j=0;j<3;j++,k++)
		{
			putchar('0'+((s>>k)&1));
		}
		puts(""); 
	}
	puts("");
}
bool Put(bool &a,bool &b)
{
	if(a||b)return false;
	a=b=true;return true;
}
bool Put(bool &a,bool &b,bool &c)
{
	if(a||b||c)return false;
	a=b=c=true;return true;
}
int PutFigure(const int s,const int type,const int pos,const int rot)
{
	static bool g[4][3];
	for(int i=0,k=0;i<4;i++)for(int j=0;j<3;j++,k++)g[i][j]=(s&(1<<k)?true:false);
	switch(type)
	{
		case 1:
		{
			switch(rot)
			{
				case 0:
				case 2:
				{
					if(pos>0)return -1;
					for(int i=3;i>=0;i--)if(Put(g[i][0],g[i][1],g[i][2]))goto return_answer;
					return -1;
				}break;
				case 1:
				case 3:
				{
					for(int i=3;i>=2;i--)if(Put(g[i][pos],g[i-1][pos],g[i-2][pos]))goto return_answer;
					return -1;
				}break;
				default:assert(0);return -1;
			}
		}break;
		case 2:
		{
			switch(rot)
			{
				case 0:
				case 2:
				{
					if(pos>1)return -1;
					for(int i=3;i>=0;i--)if(Put(g[i][pos],g[i][pos+1]))goto return_answer;
					return -1;
				}break;
				case 1:
				case 3:
				{
					for(int i=3;i>=1;i--)if(Put(g[i][pos],g[i-1][pos]))goto return_answer;
					return -1;
				}break;
				default:assert(0);return -1;
			}
		}break;
		case 3:
		{
			switch(rot)
			{
				case 0:
				{
					if(pos>1)return -1;
					for(int i=3;i>=1;i--)if(Put(g[i][pos],g[i-1][pos],/*g[i-1][pos+1],*/g[i][pos+1]))goto return_answer;
					return -1;
				}break;
				case 1:
				{
					if(pos>1)return -1;
					for(int i=3;i>=1;i--)if(Put(g[i][pos],/*g[i-1][pos],*/g[i-1][pos+1],g[i][pos+1]))goto return_answer;
					return -1;
				}break;
				case 2:
				{
					if(pos>1)return -1;
					for(int i=3;i>=1;i--)if(Put(/*g[i][pos],*/g[i-1][pos],g[i-1][pos+1],g[i][pos+1]))goto return_answer;
					return -1;
				}break;
				case 3:
				{
					if(pos>1)return -1;
					for(int i=3;i>=1;i--)if(Put(g[i][pos],g[i-1][pos],g[i-1][pos+1]/*,g[i][pos+1]*/))goto return_answer;
					return -1;
				}break;
				default:assert(0);return -1;
			}
		}break;
		default:assert(0);return -1;
	}
	assert(0);
	return_answer:;
	int ans=0;
	for(int i=0,k=0;i<4;i++)for(int j=0;j<3;j++,k++)if(g[i][j])ans|=1<<k;
	return ans;
}
int EliminateLines(int s)
{
	assert(s!=-1);
//	puts("before");
//	PrintGrid(s);
	for(int r=0;r<4;r++)if(((s&(7<<(3*r)))>>(3*r))==7)
	{
		s=(s>>(3*(r+1))<<(3*(r+1)))|((s&((1<<(3*r))-1))<<3);
	}
//	puts("after");
//	PrintGrid(s);
	return s;
}
bool DP[1<<12];
bool VIS[1<<12];
int POS[1<<12][3],ROT[1<<12][3];
bool GetDP(const int s)
{
	if(s==-1)return false;
	if(VIS[s])return DP[s];
	VIS[s]=true;
	bool &ans=DP[s]=true;
	if(true)
	{
		const int check=EliminateLines(s);
		if(check!=s)
		{
			return GetDP(check);
			if(GetDP(check))
			{
				for(int i=0;i<3;i++)if(GetDP(PutFigure(check,i+1,POS[s][i]=POS[check][i],ROT[s][i]=ROT[check][i])));
				else
				{
					assert(GetDP(check));
					for(int j=0;j<3;j++)printf("(%d,%d)",POS[check][j],ROT[check][j]);puts("");
					PrintGrid(s);
					PrintGrid(check);
					for(int j=0;j<3;j++)PrintGrid(PutFigure(check,i+1,POS[check][i],ROT[check][i])); 
					assert(0);
				}
				return ans=true;
			}
			else return ans=false;
		}
	}
	for(int type=1;type<=3;type++)
	{
		for(int rot=0;rot<4;rot++)for(int pos=0;pos<3;pos++)if(GetDP(PutFigure(s,type,pos,rot)))
		{
			POS[s][type-1]=pos,ROT[s][type-1]=rot;
			goto put_figure_success;
		}
		return ans=false;
		put_figure_success:;
		assert(GetDP(PutFigure(s,type,POS[s][type-1],ROT[s][type-1])));
	}
	return ans=true;
}
int GRID;
void init(int n)
{
	for(int i=0;i<(1<<12);i++)VIS[i]=false;
	GRID=0;
}
int position;
int rotation;
void new_figure(int figure_type)
{
	assert(GetDP(GRID));
	position=POS[GRID][figure_type-1];
	rotation=ROT[GRID][figure_type-1];
	GRID=EliminateLines(PutFigure(GRID,figure_type,position,rotation));
	PrintGrid(GRID);
}
int get_position()
{
	return position;
}
int get_rotation()
{
	return rotation;
}

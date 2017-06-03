#include<cstdio>
#include<queue>
#include<vector>
#include<cassert>
using namespace std;
void bssert(bool valid){if(valid)return;for(;;)putchar('E');}
struct State
{
	int r,c,d;
	State(){}
	State(const int _r,const int _c,const int _d):r(_r),c(_c),d(_d){}
	bool operator==(const State &s)const{return r==s.r&&c==s.c&&(d&1)==(s.d&1);}
};
int R,C;
char GRID[50][50];
vector<State>EXIT;
bool Dfs(const State &s)
{
//	printf("(%d,%d,%s)\n",s.r,s.c,s.d==0?"¡ô":s.d==1?"¡÷":s.d==2?"¡õ":s.d==3?"¡ö":"Error");
	if(s==EXIT[1])return true;
	if(s.d==0)//up
	{
		char &type=GRID[s.r][s.c];
		if(type=='*')return false;
		if(type=='.')return Dfs(State(s.r-1,s.c,0));
		bool IsM=(type=='M');
		if(IsM)type='/';
		if(type=='/')if(Dfs(State(s.r,s.c,1)))return true;
		if(IsM)type='\\';
		if(type=='\\')if(Dfs(State(s.r,s.c-1,3)))return true;
		if(IsM)type='M';
		return false;
	}
	else if(s.d==1)//right
	{
		char &type=GRID[s.r][s.c+1];
		if(type=='*')return false;
		if(type=='.')return Dfs(State(s.r,s.c+1,1));
		bool IsM=(type=='M');
		if(IsM)type='/';
		if(type=='/')if(Dfs(State(s.r-1,s.c+1,0)))return true;
		if(IsM)type='\\';
		if(type=='\\')if(Dfs(State(s.r,s.c+1,2)))return true;
		if(IsM)type='M';
		return false;
	}
	else if(s.d==2)//down
	{
		char &type=GRID[s.r+1][s.c];
		if(type=='*')return false;
		if(type=='.')return Dfs(State(s.r+1,s.c,2));
		bool IsM=(type=='M');
		if(IsM)type='/';
		if(type=='/')if(Dfs(State(s.r+1,s.c-1,3)))return true;
		if(IsM)type='\\';
		if(type=='\\')if(Dfs(State(s.r+1,s.c,1)))return true;
		if(IsM)type='M';
		return false;
	}
	else if(s.d==3)//left
	{
		char &type=GRID[s.r][s.c];
		if(type=='*')return false;
		if(type=='.')return Dfs(State(s.r,s.c-1,3));
		bool IsM=(type=='M');
		if(IsM)type='/';
		if(type=='/')if(Dfs(State(s.r,s.c,2)))return true;
		if(IsM)type='\\';
		if(type=='\\')if(Dfs(State(s.r-1,s.c,0)))return true;
		if(IsM)type='M';
		return false;
	}
	else bssert(0);
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&C,&R)==2);
		if(C==-1&&R==-1)break;
		EXIT.clear();
		for(int row=0;row<R;row++)
		{
			for(int column=0;column<C;column++)
			{
				char &c=GRID[row][column];
				bool found=false;
				while(!found)
				{
					assert((c=getchar())!=-1);
					switch(c)
					{
						case'\\':
						case'/':c='M',found=true;break;
						case'*':found=true;break;
						case'.':
						{
							found=true;
							if(row==0)EXIT.push_back(State(row,column,2));
							else if(row==R-1)EXIT.push_back(State(row-1,column,0));
							else if(column==0)EXIT.push_back(State(row,column,1));
							else if(column==C-1)EXIT.push_back(State(row,column-1,3));
						}break;
						default:break;
					}
				}
			}
		}
		assert(EXIT.size()==2);
//		EXIT[0].Print(),EXIT[1].Print();
		State tmp=EXIT[0];EXIT[0]=EXIT[1],EXIT[1]=tmp;
		bssert(Dfs(EXIT[0]));
		static int kase=0;
		if(kase++)puts("");
		for(int i=0;i<R;i++)
		{
			for(int j=0;j<C;j++)
			{
				if(GRID[i][j]=='M')GRID[i][j]='/';
				putchar(GRID[i][j]);
			}
			puts("");
		}
	}
	return 0;
}

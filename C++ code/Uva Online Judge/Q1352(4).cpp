#include<cstdio>
#include<string>
#include<vector>
#include<map>
void getmin(int &a,int b){if(b<a)a=b;}
using namespace std;
int N;
map<string,int> IDX;
int getIDX(char* name)
{
	if(IDX.find(name)==IDX.end())
	{
		int sz=IDX.size();
		IDX[name]=sz;
	}
	return IDX[name];
}
int CUBE[4][6];
int ORDER[6]={0,1,4,5,3,2};
int ROTATE[24][6]=
{
	{0,1,2,3,4,5},
	{1,2,3,0,4,5},
	{2,3,0,1,4,5},
	{3,0,1,2,4,5},
	{5,1,4,3,0,2},
	{1,4,3,5,0,2},
	{4,3,5,1,0,2},
	{3,5,1,4,0,2},
	{2,1,0,3,5,4},
	{1,0,3,2,5,4},
	{0,3,2,1,5,4},
	{3,2,1,0,5,4},
	{4,1,5,3,2,0},
	{1,5,3,4,2,0},
	{5,3,4,1,2,0},
	{3,4,1,5,2,0},
	{0,4,2,5,3,1},
	{4,2,5,0,3,1},
	{2,5,0,4,3,1},
	{5,0,4,2,3,1},
	{0,5,2,4,1,3},
	{5,2,4,0,1,3},
	{2,4,0,5,1,3},
	{4,0,5,2,1,3}
};
int R[4];
int COLOR[24];
int ANS;
void dfs(int dep)
{
	if(dep==4)
	{
		int ans=6*N;
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<IDX.size();j++)COLOR[j]=0;
			int mx=0;
			for(int j=0;j<N;j++)
			{
				int &c=COLOR[CUBE[j][ROTATE[R[j]][i]]];
				if(++c>mx)mx=c;
			}
			ans-=mx;
		}
		if(ans<ANS)ANS=ans;
		return;
	}
	for(int i=0;i<24;i++)
	{
		R[dep]=i;
		dfs(dep+1);
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	R[0]=0;
	while(scanf("%d",&N)==1&&N)
	{
		IDX.clear();
		char name[25];
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<6;j++)
			{
				scanf("%s",name);
				CUBE[i][ORDER[j]]=getIDX(name);
			}
		}
		ANS=2147483647;
		dfs(1);
		printf("%d\n",ANS);
	}
	return 0;
}

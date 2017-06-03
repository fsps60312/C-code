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
int RepeatColor(int *a,int *b)
{
	int color=0,ans=0;
	for(int i=0,j;i<6;i++)
	{
		j=(1<<a[i]);
		if(color&j)ans++;
		color|=j;
		j=(1<<b[i]);
		if(color&j)ans++;
		color|=j;
	}
	return ans;
}
int differ(int *a,int *b)
{
	int v=RepeatColor(a,b);
	if(v<=1)return 6-v;
	int ans=6;
	for(int i=0,k,j;i<24;i++)
	{
		k=0;
		for(j=0;j<6;j++)
		{
			if(a[j]!=b[ROTATE[i][j]])k++;
		}
		if(k<ans)ans=k;
	}
	return ans;
}
int CNT[7][4][24];
int COLOR[6];
int ANS;
void dfs(int dep)
{
	if(dep==7)
	{
		int t=0;
		for(int n=0,m=6;n<N;n++,m=6)
		{
			for(int r=0;r<24;r++)//rotate status
			{
				if(CNT[6][n][r]<m)m=CNT[6][n][r];
			}
			t+=m;
		}
		if(t<ANS)ANS=t;
	}
	for(int c=0;c<IDX.size();c++)
	{
		for(int n=0;n<N;n++)
			for(int r=0;r<24;r++)//rotate status
			{
				int &cnt=CNT[dep][n][r]=(dep==0?0:CNT[dep-1][n][r]);
				if(CUBE[n][ROTATE[r][dep]]!=c)cnt++;
			}
		dfs(dep+1);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
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
		int n=IDX.size();
		int ans=2147483647;
		int a[6];
		for(a[0]=0,v0,v1,v2,v3,v4,v5;a[0]<n;a[0]++)
		{
			v0=6;
			for(int j=0;j<24;j++)
			{
				if(a[0]!=b[ROTATE[i][j]])k++;
			}
			for(a[1]=0;a[1]<n;a[1]++)
			{
				int v=a[0]>a[1]?a[0]:a[1];
				for(a[2]=v;a[2]<n;a[2]++)
				for(a[3]=v;a[3]<n;a[3]++)
				for(a[4]=v;a[4]<n;a[4]++)
				for(a[5]=v;a[5]<n;a[5]++)
				{
					int k=0;
					for(int j=0;j<N;j++)k+=differ(i,CUBE[j]);
					if(k<ans)ans=k;
					int t=a[1];a[1]=a[2],a[2]=t;
					k=0;
					for(int j=0;j<N;j++)k+=differ(i,CUBE[j]);
					if(k<ans)ans=k;
					t=a[1];a[1]=a[2],a[2]=t;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

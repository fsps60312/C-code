#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,COLOR[5000],DEGREE[5000];
bool EDGE[5000][5000];
vector<int>STK;
bool SetColor(const int u,const int color)
{
	if(COLOR[u]!=-1)return COLOR[u]==color;
	COLOR[u]=color,STK.push_back(u);
	if(color)
	{
		for(int i=0;i<N;i++)if(i!=u&&!EDGE[u][i]&&!SetColor(i,0))return false;
	}
	else
	{
		for(int i=0;i<N;i++)if(i!=u&&EDGE[u][i]&&!SetColor(i,1))return false;
	}
	return true;
}
bool SetColor()
{
	int root=-1;
	for(int i=0;i<N;i++)if(COLOR[i]==-1){root=i;break;}
	if(root==-1)return true;
	for(int color=0,sz=STK.size();color<=1;color++)
	{
		if(SetColor(root,color)&&SetColor())return true;
		while((int)STK.size()>sz)COLOR[STK.back()]=-1,STK.pop_back();
	}
	return false;
}
int Solve()
{
	for(int i=0;i<N;i++)COLOR[i]=-1;
	if(!SetColor())return 0;
//	return 1;
	int sz=0;
	for(int i=0;i<N;i++)if(COLOR[i])sz++;//,printf("i=%d\n",i+1);
//	printf("%d %d\n",sz[0],sz[1]);
	int ans=(sz&&N-sz?1:0);
	for(int i=0;i<N;i++)
	{
		if(COLOR[i])
		{
			if(DEGREE[i]==sz-1)
			{
				if(sz>1)ans++;
				if(N-sz)for(int j=0;j<N;j++)if(!COLOR[j]&&DEGREE[j]==sz-1)ans++;
			}
//			if(DEGREE[i]==sz[1])
//			{
//				for(int j=0;j<N;j++)if(!COLOR[j]&&DEGREE[j]==sz[1]){ans++;break;}
//			}
		}
		else
		{
			if(DEGREE[i]==sz)
			{
				if(N-sz>1)ans++;
				if(sz)for(int j=0;j<N;j++)if(COLOR[j]&&DEGREE[j]==sz)ans++;
			}
//			if(DEGREE[i]==sz[1]-1)
//			{
//				for(int j=0;j<N;j++)if(COLOR[j]&&DEGREE[j]==sz[1]-1){ans++;break;}
//			}
		}
	}
	assert(ans);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)EDGE[i][j]=false;
		int &cnt=DEGREE[i];
		scanf("%d",&cnt);
		for(int j=0,v;j<cnt;j++)scanf("%d",&v),EDGE[i][--v]=true;
	}
	printf("%d\n",Solve());
	return 0;
}

#include<cstdio>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;
int T,N,MAT[120][120],ORI[120][120],ANS[120][120],VIS[120];
vector<int> CNT[120][120];
void update(int i,int k,int j)//require MAT[i][k]
{
	if(!ORI[k][j])continue;
	int a=MAT[i][k]+1;
	if(a<MAT[i][j])
	{
		MAT[i][j]=a;
		CNT[i][j].clear();
	}
	if(a==MAT[i][j])CNT[i][j].push_back(k);
}
void cal_MC()
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<=i;j++)
		{
			for(int k=0;k<j;k++)
			{
				update(i,k,j);
			}
		}
		for(int j=0;j<=i;j++)
		{
			for(int k=j;k<=i;k++)
			{
				if(!ORI[k][j])continue;
				int a=MAT[i][k]+1;
				if(a<MAT[i][j])
				{
					MAT[i][j]=a;
					CNT[i][j].clear();
				}
				if(a==MAT[i][j])CNT[i][j].push_back(k);
			}
		}
	}
}
int cal_ANS()
{
	int ans=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			for(int k=0;k<N;k++)VIS[k]=0;
			queue<int> q;
			q.push(i);
			while(!q.empty())
			{
				int u=q.front();q.pop();
				if(VIS[u])continue;
				VIS[u]=1,ANS[i][j]+=CNT[u][j].size();
				for(int ti=0;ti<CNT[u][j].size();ti++)
				{
					int tj=CNT[u][j][ti];
					q.push(tj);
				}
			}
			if(ANS[i][j]>ans)ans=ANS[i][j];
		}
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		int m;scanf("%d%d",&N,&m);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				CNT[i][j].clear();
				ORI[i][j]=ANS[i][j]=0;
				MAT[i][j]=120;
			}
			MAT[i][i]=0;
		}
		while(m--)
		{
			int a,b;scanf("%d%d",&a,&b);
			ORI[a][b]=ORI[b][a]=MAT[a][b]=MAT[b][a]=1;
		}
		cal_MC();
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				printf("\t%d:",MAT[i][j]);
				for(int k=0;k<CNT[i][j].size();k++)printf(" %d",CNT[i][j][k]);
			}
			printf("\n");
		}
		printf("Case #%d: %d\n",kase++,cal_ANS());
	}
	return 0;
}

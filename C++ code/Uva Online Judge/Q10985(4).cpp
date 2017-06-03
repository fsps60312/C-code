#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int T,N,ORI[120][120],MAT[120][120],ANS[120][120],VIS[120];
vector<int> CNT[120][120];
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
void cal_ORI()
{
	for(int k=0;k<N;k++)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				getmin(MAT[i][j],MAT[i][k]+MAT[k][j]);
			}
		}
	}
}
void cal_CNT()
{
	for(int k=0;k<N;k++)
	{
		for(int i=0;i<N;i++)
		{
			if(!ORI[i][k])continue;
			for(int j=0;j<N;j++)
			{
				if(1+MAT[k][j]==MAT[i][j])CNT[i][j].push_back(k);
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
			ANS[i][j]=0;
			for(int ti=0;ti<N;ti++)VIS[ti]=0;
			queue<int> q;
			q.push(i);
			while(!q.empty())
			{
				int u=q.front();q.pop();
				ANS[i][j]++;
				if(VIS[u])continue;
				VIS[u]=1;
				for(int ti=0;ti<CNT[u][j].size();ti++)
				{
					int tj=CNT[u][j][ti];
					q.push(tj);
				}
			}
			getmax(ans,ANS[i][j]);
		}
	}
	return ans-1;
}
int main()
{
	int kase=1;
    scanf("%d",&T);
    while(T--)
    {
        int m;scanf("%d%d",&N,&m);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                MAT[i][j]=120;
                ORI[i][j]=0;
                CNT[i][j].clear();
            }
            ORI[i][i]=1;
            MAT[i][i]=0;
        }
        while(m--)
        {
            int a,b;scanf("%d%d",&a,&b);
            ORI[a][b]=ORI[b][a]=MAT[a][b]=MAT[b][a]=1;
        }
        cal_ORI();
        cal_CNT();
        /*for(int i=0;i<N;i++)
        {
        	for(int j=0;j<N;j++)
        	{
        		printf("\t");
        		for(int ti=0;ti<CNT[i][j].size();ti++)
        		{
        			int tj=CNT[i][j][ti];
        			printf(",%d",tj);
				}
			}
			printf("\n");
		}*/
        printf("Case #%d: %d\n",kase++,cal_ANS());
    }
    return 0;
}


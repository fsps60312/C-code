#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
void getmax(int &a,const int &b){if(b>a)a=b;}
int N,W;
vector<int>ET[2][500];
int IN[2][500],DIST[2][500];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&W)==2)
	{
		for(int i=0;i<2;i++)for(int j=0;j<N;j++)IN[i][j]=0,ET[i][j].clear();
		for(int i=0;i<N*(N-1)/2;i++)
		{
			static int a,b,t;
			scanf("%d%d%d",&a,&b,&t);
			a--,b--;
			ET[t][a].push_back(b);
			IN[t][b]++;
		}
		int ans=W*W;
		for(int t=0;t<2;t++)
		{
			queue<int>q;
			for(int i=0;i<N;i++)
			{
				if(!IN[t][i])q.push(i);
				DIST[t][i]=1;
			}
			while(!q.empty())
			{
				const int u=q.front();q.pop();
				for(int i=0;i<ET[t][u].size();i++)
				{
					const int &nxt=ET[t][u][i];
					getmax(DIST[t][nxt],DIST[t][u]+1);
					if(!--IN[t][nxt])q.push(nxt);
				}
			}
			int ta=0;
			for(int i=0;i<N;i++)getmax(ta,DIST[t][i]);
//			printf("ta=%d\n",ta);
			ans*=ta;
		}
		printf("%d\n",ans);
	}
	return 0;
}

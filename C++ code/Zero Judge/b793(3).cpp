#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,S[1000][1000];
int COST[1000][1000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		assert(1<=N&&N<=1000);
		for(int i=0;i<N;i++)
		{
			static bool vis[1000];
			for(int j=0;j<N;j++)vis[j]=false;
			for(int j=0;j<N;j++)
			{
				int &v=S[i][j];
				scanf("%d",&v);
				assert(1<=v&&v<=N);
				v--;
				assert(!vis[v]);
				vis[v]=true;
				v=(v-i+N)%N;
	//			printf("v=%d\n",v);
			}
		}
		for(int i=0;i<N;i++)
		{
			int initial_cost=0;
			for(int j=1;j<N;j++)initial_cost+=(S[i][j]-S[i][j-1]+N)%N;
			for(int j=0;j<N;j++)COST[i][j]=initial_cost+(S[i][0]-j+N)%N;
		}
		int ans=INF;
		for(int i=0;i<N;i++)
		{
			int ta=0;
			for(int p=0;p<N;p++)getmax(ta,COST[p][i]);
			getmin(ans,ta);
		}
		printf("%d\n",ans);
	}
	return 0;
}

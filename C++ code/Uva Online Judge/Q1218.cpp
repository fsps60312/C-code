#include<cstdio>
#include<cstdlib>
#include<vector>
const int INF=2147483647;
using namespace std;
int N;
vector<int> GETO[10001];
int DP[10001][3];//put, ch put, ch not put(fa must put)
void getmin(int &a,int b){if(b<a)a=b;}
int get_ANS(int u,int t,int fa)
{
	int &ans=DP[u][t];
	if(ans!=-1)return ans;
	if(fa!=-1&&GETO[u].size()==1)
	{
		if(t==0)ans=1;
		else if(t==1)ans=0;
		else ans=0;
	}
	else if(t==0)//u is put
	{
		ans=1;
		for(int i=0;i<GETO[u].size();i++)
		{
			int &j=GETO[u][i];
			if(j==fa)continue;
			int a0=get_ANS(j,0,u);
			int a2=get_ANS(j,2,u);
			ans+=(a0<a2?a0:a2);
		}
	}
	else if(t==1)//u not put, 1 ch put
	{
		ans=0;
		int low=INF;
		for(int i=0;i<GETO[u].size();i++)
		{
			int &j=GETO[u][i];
			if(j==fa)continue;
			ans+=get_ANS(j,1,u);
			getmin(low,get_ANS(j,0,u)-get_ANS(j,1,u));
		}
		ans+=low;
	}
	else//u not put, no ch put
	{
		ans=0;
		for(int i=0;i<GETO[u].size();i++)
		{
			int &j=GETO[u][i];
			if(j==fa)continue;
			ans+=get_ANS(j,1,u);
		}
	}
	printf("(%d,%d,%d)=%d\n",u,t,fa,ans);
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)
		{
			GETO[i].clear();
			for(int j=0;j<3;j++)
			{
				DP[i][j]=-1;
			}
		}
		for(int i=1;i<N;i++)
		{
			int a,b;scanf("%d%d",&a,&b);
			GETO[a].push_back(b);
			GETO[b].push_back(a);
		}
		int ans=INF;
		getmin(ans,get_ANS(1,0,-1));
		getmin(ans,get_ANS(1,1,-1));
		printf("%d\n",ans);
		scanf("%d",&ans);
		if(ans==-1)break;
	}
	return 0;
}

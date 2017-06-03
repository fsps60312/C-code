#include<cstdio>
#include<cstdlib>
#include<vector>
const int INF=2147483647;
using namespace std;
int N;
vector<int> GETO[10001];
int DP[10001][3];//put, ch put, ch not put(fa must put)
int DEP[10001];
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
int get_DEP(int u,int fa)
{
	int &ans=DEP[u];
	if(fa!=-1&&GETO[u].size()==1)
	{
		return ans=0;
	}
	ans=INF;
	for(int i=0;i<GETO[u].size();i++)
	{
		int &j=GETO[u][i];
		if(j==fa)continue;
		getmax(ans,get_DEP(j,u)+1);
	}
	return ans;
}
int get_ANS(int u,int t)
{
	int &ans=DP[u][t];
	if(ans!=-1)return ans;
	if(DEP[u]==0)
	{
		if(t==0)ans=1;
		else if(t==1)ans=0;
		else ans=0;
	}
	else if(DEP[u]==1)
	{
		if(t==0)ans=1;
		else if(t==1)ans=(GETO[u].size()<=2?1:INF);
		else ans=INF;
	}
	else if(t==0)//u is put
	{
		ans=1;
		for(int i=0;i<GETO[u].size();i++)
		{
			int &j=GETO[u][i];
			if(DEP[j]!=DEP[u]-1)continue;
			int a0=get_ANS(j,0);
			int a2=get_ANS(j,2);
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
			if(DEP[j]!=DEP[u]-1)continue;
			int a=get_ANS(j,1);
			if(a==INF)continue;
			ans+=a;
			getmin(low,get_ANS(j,0)-a);
		}
		ans+=low;
	}
	else//u not put, no ch put
	{
		ans=0;
		for(int i=0;i<GETO[u].size();i++)
		{
			int &j=GETO[u][i];
			if(DEP[j]!=DEP[u]-1)continue;
			int a=get_ANS(j,1);
			if(a==INF)
			{
				ans=INF;
				break;
			}
			ans+=a;
		}
	}
	printf("(%d,%d)=%d\n",u,t,ans);
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
		get_DEP(1,-1);
		int ans=INF;
		getmin(ans,get_ANS(1,0));
		getmin(ans,get_ANS(1,1));
		printf("%d\n",ans);
		scanf("%d",&ans);
		if(ans==-1)break;
	}
	return 0;
}

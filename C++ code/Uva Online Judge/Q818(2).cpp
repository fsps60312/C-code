#include<cstdio>
#include<vector>
using namespace std;
int max(int a,int b){return a>b?a:b;}
int N,DEG[15],ADJ[15][15];
bool VIS[15];
void dfs(int u,vector<int>&ans)
{
	if(VIS[u])return;
	VIS[u]=true;
	ans.push_back(u);
	for(int i=0;i<N;i++)
	{
		if(!ADJ[u][i])continue;
		dfs(i);
	}
}
int solve()
{
	for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==-1&&b==-1);)
	{
		a--,b--;
		EDGE[a][b]++,EDGE[b][a]++;
		DEG[a]++,DEG[b]++;
	}
	int ans=0,cnt_tree=0,cnt_0=0,cnt_1=0;
	for(int i=0;i<N;i++)
	{
		if(VIS[i])continue;
		static vector<int>v;
		cnt_tree++;
		dfs(i,v);
		int pre_cnt=cnt_1;
		for(int i=0;i<v.size();i++)
		{
			int &d=DEG[v[i]];
			if(d==0)cnt_0++;
			else if(d==1)cnt_1++;
			else if(d>2)
			{
				int n=d-2;
				ans+=n/2;
				if(n&1)cnt_1++;
			}
		}
		if(cnt_1==pre_cnt)cnt_1++;
	}
	if(cnt_0>cnt_1)ans+=cnt_0-cnt_1;
	ans+=cnt_1;
	if(cnt_tree<=1)ans--;
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			VIS[i]=false;
			DEG[i]=0;
			for(int j=0;j<N;j++)ADJ[i][j]=false;
		}
		static int kase=1;
		printf("Set %d: Minimum links to open is %d\n",kase++,solve());
	}
	return 0;
}

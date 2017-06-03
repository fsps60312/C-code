#include<cstdio>
#include<vector>
#include<algorithm>
#include<stack>
#include<cassert>
using namespace std;
void OLE(){while(1)printf("E");}
int N,P,VIS[60];
vector<int>TO[60];
void AddEdge(int a,int b){TO[a].push_back(b);TO[b].push_back(a);}
stack<int>STK;
int dfs(int u,int c)
{
	if(VIS[u])
	{
		if(VIS[u]!=c)return 0;
		return VIS[u];
	}
	VIS[u]=c;
	STK.push(u);
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(!dfs(j,3-c)&&!(c==1&&(j>>1)!=(u>>1)&&dfs(j,c)))
		{
			while(STK.top()!=u)
			{
				VIS[STK.top()]=0;
				STK.pop();
			}
			VIS[u]=0;
			STK.pop();
			return 0;
		}
	}
	return VIS[u];
}
int solve()
{
	VIS[0]=1,VIS[1]=2;
	for(int i=2;i<N*2;i++)
	{
		if(VIS[i])continue;
		if(!dfs(i,1)&&!dfs(i,2))return 0;
		STK=stack<int>();
	}
	return VIS[0];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&P)==2&&(N||P))
	{
		for(int i=0;i<N*2;i++)
		{
			TO[i].clear();
			VIS[i]=0;
		}
		for(int i=0;i<N;i++)AddEdge(i*2,i*2+1);
		for(int i=0,a,b;i<P;i++)
		{
			static char c1,c2;
			scanf("%d%c%d%c",&a,&c1,&b,&c2);
			a<<=1,b<<=1;
			if(c1=='w')a++;
			if(c2=='w')b++;
			AddEdge(a,b);
		}
		int result=solve();
		if(!result)printf("bad luck\n");
		else
		{
			vector<int>ans;
			for(int i=0;i<N*2;i++)if(VIS[i]==result)ans.push_back(i);
			sort(ans.begin(),ans.end());
			for(int i=0;i<ans.size();i++)
			{
				if((ans[i]>>1)!=i)assert(0);
			}
			for(int i=0;i<N*2;i++)
			{
				if(VIS[i]==1)continue;
				for(int j=0;j<TO[i].size();j++)
				{
					int &k=TO[i][j];
					if(VIS[k]==VIS[i])OLE();
				}
			}
			for(int i=1;i<N;i++)printf("%d%c%c",ans[i]>>1,(ans[i]&1)?'w':'h',i==N-1?'\n':' ');
		}
	}
	return 0;
}

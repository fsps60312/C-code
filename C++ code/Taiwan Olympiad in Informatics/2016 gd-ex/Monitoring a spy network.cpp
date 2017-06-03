#include<bits/stdc++.h>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N;
vector<int>ET[10000];
int DP[10000][2];
int Dfs(const int u,const int color)
{
	int &ans=DP[u][color];
	if(ans!=-1)return ans;
	ans=color;
	for(const int nxt:ET[u])
	{
		if(!color)ans+=Dfs(nxt,1);
		else ans+=min(Dfs(nxt,0),Dfs(nxt,1));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)ET[i].clear(),DP[i][0]=DP[i][1]=-1;
		for(int i=1,v;i<N;i++)scanf("%d",&v),ET[v].push_back(i);
		printf("%d\n",min(Dfs(0,0),Dfs(0,1)));
	}
	return 0;
}

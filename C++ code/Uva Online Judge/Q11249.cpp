#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,K,Q,A,B,MX,SG[199999];
int getSG(int u)
{
	int &sg=SG[u];
	if(sg!=-1)return sg;
	vector<int> vis;
	for(int i=1;i<=u&&i<=K;i++)vis.push_back(getSG(u-i));
	sort(vis.begin(),vis.end());
	sg=0;
	for(int i=0;i<vis.size();i++)
	{
		if(vis[i]==sg)sg++;
		else if(vis[i]>sg)break;
	}
	return sg;
}
bool solve()
{
	int n=A+B-2;
	while(MX<n)SG[++MX]=-1;
	if(getSG(n))return true;
	for(int i=)
}
int main()
{
//	int sg[101];sg[0]=0;
//	for(int i=1;i<=100;i++)
//	{
//		vector<int> vis;
//		for(int j=0)
//	}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&K,&Q);
		SG[0]=MX=0;
		while(Q--)
		{
			scanf("%d%d",&A,&B);
			printf(solve()?"WINNING\n":"LOSING\n");
		}
		puts("");
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int N,S[50][50];
vector<pair<int,int> >EDGE[1001];
int main()
{
	for(int i=-100;i<=100;i++)
	for(int j=-100;j<=100;j++)
	for(int k=-100;k<=100;k++)
	if(i+min(j,k)==12&&j+min(i,k)==24&&k+min(i,j)==36)
	{
		printf("%d %d %d\n",i,j,k);
		return 0;
	}
	assert(0);
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)scanf("%d",&S[i][j]);
		for(int i=0;i<=1000;i++)EDGE[i].clear();
		for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)
		{
			EDGE[S[i][j]].push_back(make_pair(i,j));
		}
		
	}
	return 0;
}

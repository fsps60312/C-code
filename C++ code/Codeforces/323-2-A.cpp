#include<bits/stdc++.h>
using namespace std;
int N,X[2500],Y[2500],VX[51],VY[51];
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)VX[i]=VY[i]=0;
		for(int i=0;i<N*N;i++)
		{
			scanf("%d%d",&X[i],&Y[i]);
		}
		vector<int>ans;
		for(int i=0;i<N*N;i++)
		{
			if(!VX[X[i]]&&!VY[Y[i]])
			{
				ans.push_back(i+1);
				VX[X[i]]=VY[Y[i]]=1;
			}
		}
		printf("%d",ans[0]);
		for(int i=1;i<ans.size();i++)printf(" %d",ans[i]);puts("");
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
int N,M,DP[2505][25],PLATESZ[2505]; // [previous i-th size plate][tail plate from stack]
int HAS[2505][55];
vector<pair<int,int> >D;
int main()
{
	freopen("inn.txt","r",stdin);
//	freopen("new.txt","w",stdout);
	int cases=0,h,x;
	while(scanf("%d",&N)==1)
	{
		D.clear();
		for(int i=0;i<N;i++)
		{
			scanf("%d",&h);
			for(int j=0;j<h;j++)
			{
				scanf("%d",&x);
				D.push_back(make_pair(x,i));
			}
		}
		memset(HAS,0,sizeof(HAS));
		memset(DP,63,sizeof(DP));
		sort(D.begin(),D.end());
		D.resize(unique(D.begin(),D.end())-D.begin());
		M = 0;
		for(int i=0;i<D.size();)
		{
			int cnt=0,j=i;
			while(j<D.size()&&D[i].first==D[j].first)
			{
				HAS[M][D[j].second]=1;
				j++,cnt++;
			}
			PLATESZ[M]=cnt;
			M++,i=j;
		}
		for(int i=0;i<N;i++)if(HAS[0][i])DP[0][i]=PLATESZ[0];
		for(int i=1;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				if(!HAS[i][j])continue;
				for(int k=0;k<N;k++)
				{
					if (HAS[i][k]&&(j!=k||PLATESZ[i]==1)) // merge tail ...k-k..j
						DP[i][j]=min(DP[i][j],DP[i-1][k]+PLATESZ[i]-1);
					else DP[i][j]=min(DP[i][j],DP[i-1][k]+PLATESZ[i]);
				}
			}
		}
		int ret=0x3f3f3f3f;
		for(int i=0;i<N;i++)ret=min(ret,DP[M-1][i]);
		printf("Case %d: %d\n",++cases,ret*2-N-1);
	}
	return 0;
}
/*
 2
 3 1 2 4
 2 3 5
 3
 4 1 1 1 1
 4 1 1 1 1
 4 1 1 1 1
 2
 3 1 2 4
 3 1 3 4
*/


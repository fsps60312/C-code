#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,DP[100002];
vector<pair<int,int> >ET[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		for(int i=0;i<=100000;i++)ET[i].clear(),DP[i]=-1;
		scanf("%d",&N);
		for(int i=0,s,t,v;i<N;i++)
		{
			scanf("%d%d%d",&s,&t,&v);
			ET[s].push_back(make_pair(t,v));
		}
		DP[100001]=0;
		for(int u=100000;u>=0;u--)
		{
			int &dp=DP[u];
			for(const auto &p:ET[u])
			{
				assert(p.first>u);
				getmax(dp,DP[p.first]+p.second);
			}
			getmax(dp,DP[u+1]);
		}
		printf("%d\n",DP[0]);
	}
	return 0;
}

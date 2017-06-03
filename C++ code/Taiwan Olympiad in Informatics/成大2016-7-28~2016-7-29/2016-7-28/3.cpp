#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
int N,DP[100001];
vector<pair<int,int> >ET[100001];
int GetDP(const int u)
{
	if(u==100001)return 0;
//	printf("u=%d\n",u);
	int &dp=DP[u];
	if(dp!=-1)return dp;
	for(const auto &p:ET[u])
	{
		assert(p.first>u);
		getmax(dp,GetDP(p.first)+p.second);
	}
	getmax(dp,GetDP(u+1));
	return dp;
}
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
		printf("%d\n",GetDP(0));
	}
	return 0;
}

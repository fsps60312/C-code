#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,M;
struct DisjointSets
{
	int S[2501];
	double W[2501];
	void Clear()
	{
		scanf("%d%d",&N,&M);
		for(int i=0,v;i<N;i++)
		{
			scanf("%d%lf",&v,&W[i]);
			S[i]=i;
		}
	}
	int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;S[a]=b,W[b]+=W[a],W[a]=0;return true;}
}DJ;
vector<int>ET[2501];
bool VIS[2501];
int main()
{
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),--a,--b;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	vector<int>order;
	for(int i=0;i<N;i++)order.push_back(i),VIS[i]=false;
	sort(order.begin(),order.end(),[](const int a,const int b)->bool{return DJ.W[a]>DJ.W[b];});
	for(const int i:order)
	{
		VIS[i]=true;
		for(const int nxt:ET[i])
		{
			
		}
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(const int _t,const int _c):to(_t),cost(_c){}
	bool operator<(const Edge &e)const{return cost<e.cost;}
};
vector<Edge>ET[100000];
int N,M,K,S;
bool Dfs(const int u,const int remain,int &counter)
{
	if(++counter==K)return true;
	for(const Edge &e:ET[u])
	{
		if(e.cost>remain)break;
		if(Dfs(e.to,remain-e.cost,counter))return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&K,&S)==4)
	{
		S--;
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),a--,b--;
			ET[a].push_back(Edge(b,c));
		}
		for(int i=0;i<N;i++)sort(ET[i].begin(),ET[i].end());
		int l=0,r=100000000;
		while(l<r)
		{
			const int mid=(l+r)/2;
			int tmp=0;
			if(Dfs(S,mid,tmp))r=mid;
			else l=mid+1;
		}
		printf("%d\n",r);
	}
	return 0;
}

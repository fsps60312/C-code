#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
const int INF=2147483647;
struct Edge
{
	int a,b,l;
	Edge(){}
	Edge(const int _a,const int _b,const int _l):a(_a),b(_b),l(_l){}
};
vector<Edge>EDGE;
struct DjSet
{
	map<int,int>data[100000];
	void clear(const int n){for(int i=0;i<n;i++)data[i].clear(),data[i][-1]=i;}
	int GetData(const int i,const int mxlen)
	{
		auto it=data[i].upper_bound(mxlen);
		assert(it!=data[i].begin());
		it--;
		return it->second;
	}
	int find(const int i,const int mxlen)
	{
		const int parent=GetData(i,mxlen);
		return parent==i?i:(data[i][mxlen]=find(parent,mxlen));
	}
	bool merge(int a,int b,const int mxlen)
	{
		if((a=find(a))==(b=find(b)))return false;
//		if(sz[a]>sz[b])swap(a,b);
		data[a]=b;
		return true;
	}
};
int N,M;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		EDGE.clear();
		for(int i=0,a,b,l;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&l),a--,b--;
			EDGE.push_back(Edge(a,b,l));
		}
	}
	return 0;
}

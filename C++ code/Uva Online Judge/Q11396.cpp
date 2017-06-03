#include<cstdio>
#include<vector>
using namespace std;
struct Edge
{
	int from,to;
	Edge(int f,int t):from(f),to(t){}
};
int N;
vector<Edge> EDGE;
bool add_EDGE()
{
	int a,b;scanf("%d%d",&a,&b);
	if(!a&&!b)return false;
	EDGE.push_back(Edge(a,b));
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		
	}
	return 0;
}

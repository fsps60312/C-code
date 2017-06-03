#include<cstdio>
#include<vector>
#include<map>
#include<queue>
using namespace std;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE;
vector<vector<int> >ET;
int SPACE,N,M;
map<int,int>IDX;
bool VIS[28<<14];
int SOURCE,TARGET;
int CntBits(int v)
{
	v=((v&0xaaaaaaaa)>>1)+(v&0x55555555);
	v=((v&0xcccccccc)>>2)+(v&0x33333333);
	v=((v&0xf0f0f0f0)>>4)+(v&0x0f0f0f0f);
	v=((v&0xff00ff00)>>8)+(v&0x00ff00ff);
	v=((v&0xffff0000)>>16)+(v&0x0000ffff);
	return v;
}
bool Solve()
{
	auto it=IDX.find(SOURCE);
	if(it==IDX.end())return false;
	else SOURCE=it->second;
	it=IDX.find(TARGET);
	if(it==IDX.end())return false;
	else TARGET=it->second;
	queue<int>q;
	q.push(SOURCE<<M);
	const int all=(1<<M)-1;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(CntBits(u&all)>SPACE||VIS[u])continue;
		VIS[u]=true;
		if(CntBits(u&all)==SPACE&&(u>>M)==TARGET)return true;
		for(const auto i:ET[u>>M])if(!(u&(1<<i)))
		{
			const Edge &e=EDGE[i];
			const int nxt=((u>>M)==e.a?e.b:e.a);
			q.push((nxt<<M)+((u&all)|(1<<i)));
		}
	}
	return false;
}
int main()
{
	while(scanf("%d",&SPACE)==1&&SPACE)
	{
		EDGE.clear();
		scanf("%d",&M);
		int tmp;scanf("%d%d%d%d",&tmp,&SOURCE,&TARGET,&tmp);
		IDX.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b);
			EDGE.push_back(Edge(a,b));
			IDX[a]=IDX[b]=-1;
		}
		N=0;
		for(auto &it:IDX)it.second=N++;
		ET.clear(),ET.resize(N);
		for(int i=0;i<M;i++)
		{
			int &a=EDGE[i].a,&b=EDGE[i].b;
			a=IDX[a],b=IDX[b];
			ET[a].push_back(i),ET[b].push_back(i);
		}
		for(int i=0;i<(N<<M);i++)VIS[i]=false;
		puts(Solve()?"YES":"NO");
	}
	return 0;
}

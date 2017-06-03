#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
int N;
struct Edge
{
	int a,b;
	LL l;
	Edge(){}
	Edge(const int _a,const int _b,const LL _l):a(_a),b(_b),l(_l){}
	int Nxt(const int from)const{assert(from==a||from==b);return a==from?b:a;}
};
vector<Edge>EDGE;
vector<int>ET[1000000];
int NXT[1000000];
bool FindCycle(const int u,const int fa,vector<int>&ucycle,vector<int>&ecycle)
{
	if(NXT[u]!=-1)
	{
		ucycle.clear(),ecycle.clear();
		ucycle.push_back(u),ecycle.push_back(NXT[u]);
		for(int i=EDGE[NXT[u]].Nxt(u);i!=u;i=EDGE[NXT[i]].Nxt(i))ucycle.push_back(i),ecycle.push_back(NXT[i]);
		return true;
	}
	for(int i=0;i<ET[u].size();i++)
	{
		if(ET[u][i]==fa)continue;
		NXT[u]=ET[u][i];
		if(FindCycle(EDGE[ET[u][i]].Nxt(u),ET[u][i],ucycle,ecycle))return true;
	}
	return false;
}
struct Deq
{
	int s[2000000],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int front(){return s[l];}
	int back(){return s[r];}
	bool empty(){return r<l;}
}DEQ;
bool VIS[1000000];
void FindRemote(const int u,const int fa,int &p,LL &dist,const LL dnow)
{
	if(VIS[u])return;
	if(dnow>dist)dist=dnow,p=u;
	for(int i=0;i<ET[u].size();i++)
	{
		if(ET[u][i]==fa)continue;
		const Edge &e=EDGE[ET[u][i]];
		FindRemote(e.Nxt(u),ET[u][i],p,dist,dnow+e.l);
	}
}
LL GetDiameter(const int source)
{
	LL ta=0LL;
	static vector<int>ucycle,ecycle;
	assert(FindCycle(source,-1,ucycle,ecycle));
	for(int i=0;i<ucycle.size();i++)VIS[ucycle[i]]=true;
	vector<LL>h,gap;
	gap.push_back(0LL);
	for(int i=0;i<ucycle.size();i++)
	{
		const int s=ucycle[i];
		int p=-1;
		LL dist=-1LL;
		VIS[s]=false;
		FindRemote(s,-1,p,dist,0LL);
		h.push_back(dist);gap.push_back(EDGE[ecycle[i]].l);
		FindRemote(p,-1,p,dist,0LL);
		getmax(ta,dist);
		VIS[s]=true;
	}
	for(int i=0;i<ucycle.size();i++)h.push_back(h[i]),gap.push_back(gap[i+1]);
	for(int i=1;i<gap.size();i++)gap[i]+=gap[i-1];
	DEQ.clear();
	for(int i=0;i<h.size();i++)
	{
		while(!DEQ.empty()&&h[i]>=h[DEQ.back()]+gap[i]-gap[DEQ.back()])DEQ.pop_back();
		while(!DEQ.empty()&&i-DEQ.front()>=ucycle.size())DEQ.pop_front();
		if(!DEQ.empty())getmax(ta,h[DEQ.front()]+gap[i]-gap[DEQ.front()]+h[i]);
		DEQ.push_back(i);
	}
	for(int i=0;i<ucycle.size();i++)VIS[ucycle[i]]=false;
//	printf("u:");for(int i=0;i<ucycle.size();i++)printf(" %d",ucycle[i]+1);puts("");
//	printf("e:");for(int i=0;i<ecycle.size();i++)
//	{
//		Edge &e=EDGE[ecycle[i]];
//		printf("(%d,%d,%lld)",e.a+1,e.b+1,e.l);
//	}puts("");
//	printf("h:");for(int i=0;i<h.size();i++)printf(" %lld",h[i]);puts("");
//	printf("gap:");for(int i=0;i<gap.size();i++)printf(" %lld",gap[i]);puts("");
//	printf("ta=%lld\n",ta);
	return ta;
}
void MarkVIS(const int u)
{
	if(VIS[u])return;
	VIS[u]=true;
	for(int i=0;i<ET[u].size();i++)MarkVIS(EDGE[ET[u][i]].Nxt(u));
}
LL Solve()
{
	for(int i=0;i<N;i++)NXT[i]=-1,VIS[i]=false;
	LL ans=0LL;
	for(int u=0;u<N;u++)if(!VIS[u])
	{
		ans+=GetDiameter(u);
		MarkVIS(u);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)ET[i].clear();
	EDGE.clear();
	for(int i=0,b;i<N;i++)
	{
		static LL l;
		scanf("%d%lld",&b,&l);
		b--;
		EDGE.push_back(Edge(i,b,l));
		ET[i].push_back(i),ET[b].push_back(i);
	}
	printf("%lld\n",Solve());
	return 0;
}

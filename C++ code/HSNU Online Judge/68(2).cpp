#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int N,M;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int &_a,const int &_b):a(_a),b(_b){}
};
vector<Edge>EDGE;
vector<int>ET[200000];
int PRE[100000],PRE_CNT,LOW[100000],SCC[500000],SCC_CNT;
vector<int>CNT[100000];
int VIS[100000],KASE;
int CUT[100000];
stack<int>STK;
void SetSCC(const int &until)
{
	KASE++;
	vector<int>&cnt=CNT[SCC_CNT];
	cnt.clear();
	while(STK.top()!=until)
	{
		int t=STK.top();STK.pop();
		SCC[t]=SCC_CNT;
		const Edge &e=EDGE[t];
		if(VIS[e.a]!=KASE)VIS[e.a]=KASE,cnt.push_back(e.a);
		if(VIS[e.b]!=KASE)VIS[e.b]=KASE,cnt.push_back(e.b);
	}
	const Edge &e=EDGE[until];
	if(VIS[e.a]!=KASE)VIS[e.a]=KASE,cnt.push_back(e.a);
	if(VIS[e.b]!=KASE)VIS[e.b]=KASE,cnt.push_back(e.b);
	sort(cnt.begin(),cnt.end());
	for(int i=1;i<cnt.size();i++)assert(cnt[i-1]!=cnt[i]);
	for(int i=0;i<cnt.size();i++)CUT[cnt[i]]++;
	SCC[until]=SCC_CNT++,STK.pop();
}
void DfsSCC(const int &u,const int &fa)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=EDGE[ET[u][i]];
		const int &nxt=(u==e.b?e.a:e.b);
		if(nxt==fa)continue;
		STK.push(ET[u][i]);
		if(!PRE[nxt])
		{
			DfsSCC(nxt,u);
			LOW[u]=min(LOW[u],LOW[nxt]);
			if(LOW[nxt]>=PRE[u])SetSCC(ET[u][i]);
		}
		else LOW[u]=min(LOW[u],PRE[nxt]);
	}
}
int W[200000],SUM[200000],FA[200000];
int DfsSUM(const int &u,const int &fa)
{
	FA[u]=fa;
	SUM[u]=W[u];
	for(int i=0;i<ET[u].size();i++)
	{
		const int &j=ET[u][i];
		if(j==fa)continue;
		SUM[u]+=DfsSUM(j,u);
	}
//printf("SUM[%d]=%d\n",u,SUM[u]);
	return SUM[u];
}
void Rebuild()
{
	EDGE.clear();
	for(int i=0;i<N+SCC_CNT;i++)ET[i].clear(),W[i]=0;
	for(int i=0;i<SCC_CNT;i++)
	{
		for(int j=0;j<CNT[i].size();j++)
		{
			const int &u=CNT[i][j];
			if(CUT[u]==1)W[N+i]++;
			else
			{
				assert(CUT[u]>1);
				W[u]=1;
				ET[N+i].push_back(u);
				ET[u].push_back(N+i);
			}
		}
	}
	DfsSUM(N,-1);
	assert(SUM[N]==N);
}
LL GetSum(const int &a,const int &b)//a is vertex, b is scc
{
	if(FA[b]==a)return SUM[b];
	assert(FA[a]==b);
	return N-SUM[a];
}
LL GetAns(const int &u)
{
	if(CUT[u]<=1)return 2*(N-1);
	LL ans=2*(N-1);
	static vector<LL>s;s.clear();
	for(int i=0;i<ET[u].size();i++)s.push_back(GetSum(u,ET[u][i]));
	for(int i=0;i<s.size();i++)ans+=s[i]*(N-1-s[i]);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)ET[i].clear(),PRE[i]=0,VIS[i]=0,CUT[i]=0;
	EDGE.clear();
	PRE_CNT=SCC_CNT=KASE=0;
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b);
		a--,b--;
		EDGE.push_back(Edge(a,b));
		ET[a].push_back(i);
		ET[b].push_back(i);
	}
	DfsSCC(0,-1);
	if(N==1){puts("0");return 0;}
	Rebuild();
	for(int i=0;i<N;i++)printf("%lld\n",GetAns(i));
	return 0;
}

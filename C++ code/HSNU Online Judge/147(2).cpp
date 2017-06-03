#include<cstdio>
#include<vector>
#include<cassert>
#include<stack>
#include<algorithm>
#include<queue>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
void Unique(vector<int>&s){sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());}
vector<int>ET[16000],E1[16000],BCC_S[16000];
int N,M,PRE[16000],LOW[16000],PRE_CNT,BCC[16000],BCC_CNT;
bool TAG[16000];
stack<int>STK;
void Dfs(const int u)
{
	PRE[u]=LOW[u]=++PRE_CNT;
	STK.push(u);
	for(const int nxt:ET[u])
	{
		if(!PRE[nxt])Dfs(nxt),getmin(LOW[u],LOW[nxt]);
		else if(BCC[nxt]==-1)getmin(LOW[u],PRE[nxt]);
	}
	if(LOW[u]==PRE[u])
	{
		BCC_S[BCC_CNT].clear();
		for(;;)
		{
			const int v=STK.top();STK.pop();
			BCC[v]=BCC_CNT;
			BCC_S[BCC_CNT].push_back(v);
			if(v==u)break;
		}
		BCC_CNT++;
	}
}
void Rebuild()
{
	for(int i=0;i<BCC_CNT;i++)E1[i].clear();
	for(int i=0;i<N*2;i++)for(const int j:ET[i])if(BCC[i]!=BCC[j])E1[BCC[i]].push_back(BCC[j]);
	for(int i=0;i<BCC_CNT;i++)Unique(E1[i]);
}
void GetTopu(vector<int>&seq)
{
	static int deg[16000];
	for(int i=0;i<BCC_CNT;i++)deg[i]=0;
	for(int i=0;i<BCC_CNT;i++)for(const int j:E1[i])deg[j]++;
	queue<int>q;
	for(int i=0;i<BCC_CNT;i++)if(deg[i]==0)q.push(i);
	seq.clear();
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		seq.push_back(u);
		for(const int nxt:E1[u])if(!--deg[nxt])q.push(nxt);
	}
	assert((int)seq.size()==BCC_CNT);
}
void SetAllTrue(const int bcc)
{
	for(const int u:BCC_S[bcc])if(TAG[u^1])return;
	for(const int u:BCC_S[bcc])TAG[u]=true;
}
bool Solve()
{
	for(int i=0;i<N*2;i++)PRE[i]=0,BCC[i]=-1;
	PRE_CNT=BCC_CNT=0;
	for(int i=0;i<N*2;i++)if(!PRE[i])Dfs(i),assert(STK.empty());
	for(int i=0;i<N;i++)if(BCC[i*2]==BCC[i*2+1])return false;
	Rebuild();
	vector<int>seq;
	GetTopu(seq);
	for(int i=0;i<N*2;i++)TAG[i]=false;
	for(int i=BCC_CNT-1;i>=0;i--)SetAllTrue(seq[i]);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N*2;i++)ET[i].clear();
		vector<int>tmp1,tmp2; 
		for(int i=0;i<M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b^1),ET[b].push_back(a^1);
			tmp1.push_back(a),tmp2.push_back(b);
		}
		if(!Solve())puts("-1");
		else
		{
			int cnt=0;
			for(int i=0;i<M;i++)assert(!TAG[tmp1[i]]||!TAG[tmp2[i]]);
			for(int i=0;i<N*2;i++)if(TAG[i])printf("%d\n",i+1),cnt++;
			assert(cnt==N);
		}
	}
	return 0;
}

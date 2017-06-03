#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct MyArray
{
	int S[1<<10];
	vector<int>HIS;
	MyArray(){for(int i=0;i<(1<<10);i++)S[i]=INF;}
	void Update(const int i,const int val)
	{
		if(S[i]==INF)HIS.push_back(i);
		getmin(S[i],val);
	}
	void Clear()
	{
		for(int i=0;i<(int)HIS.size();i++)S[HIS[i]]=INF;
		HIS.clear();
//		for(int i=0;i<(1<<10);i++)assert(S[i]==INF);
	}
	int operator[](const int i)const{return S[i];}
};
int N,M,C[20000],DEPTH[20000];
vector<int>ET[20000];
void BuildDepth(const int u,const int depth)
{
	if(DEPTH[u]!=-1)return;
	DEPTH[u]=depth;
	for(int i=0;i<(int)ET[u].size();i++)BuildDepth(ET[u][i],depth+1);
}
int D;
void Dfs(const int u,MyArray *dp)
{
	vector<int>parents;
	for(int i=0;i<(int)ET[u].size();i++)if(DEPTH[ET[u][i]]<DEPTH[u])parents.push_back(ET[u][i]);
	dp[D^1].Clear();
	for(int i=0;i<(int)dp[D].HIS.size();i++)
	{
		const int s=dp[D].HIS[i];
		const int val=dp[D][s];
		if(true)//not put
		{
			const int nxts=s,nxtc=val;
			dp[D^1].Update(nxts,nxtc);
		}
		if(true)//put
		{
			int nxts=s|(1<<DEPTH[u]),nxtc=val+C[u];
			for(int j=0;j<(int)parents.size();j++)nxts|=1<<DEPTH[parents[j]];
			dp[D^1].Update(nxts,nxtc);
		}
	}
	D^=1;
	for(int i=0;i<(int)ET[u].size();i++)if(DEPTH[ET[u][i]]==DEPTH[u]+1)
	{
		Dfs(ET[u][i],dp);
	}
	dp[D^1].Clear();
	for(int i=0;i<(int)dp[D].HIS.size();i++)
	{
		const int s=dp[D].HIS[i];
		const int val=dp[D][s];
		bool valid=((s&(1<<DEPTH[u]))>0);
		if(!valid)
		{
			for(int j=0;j<(int)parents.size();j++)if(s&(1<<DEPTH[parents[j]])){valid=true;break;}
		}
		if(valid)dp[D^1].Update(s&((1<<DEPTH[u])-1),val);
	}
	D^=1;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		for(int i=0;i<N;i++)DEPTH[i]=-1;
		static MyArray dp[2];
		int ans=0;
		for(int u=0;u<N;u++)if(DEPTH[u]==-1)
		{
			BuildDepth(u,0);
			D=0;
			dp[0].Clear();
			dp[0].Update(0,0);
			Dfs(u,dp);
			const MyArray &s=dp[D];
//			assert(!s.HIS.empty());
			assert(s.HIS[0]==0&&(int)s.HIS.size()==1);
			ans+=s[0];
//			printf("s[0]=%d\n",s[0]);
		}
		printf("%d\n",ans);
	}
	return 0;
}

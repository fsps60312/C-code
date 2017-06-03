#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
const int POW3[12]={1,3,9,27,81,243,729,2187,6561,19683,59049,177147};
void getmin(int &a,const int b){if(b<a)a=b;}
inline int Digit(const int s,const int i){return s/POW3[i]%3;}
struct MyArray
{
	int S[59049];
	vector<int>HIS;
	MyArray(){for(int i=0;i<59049;i++)S[i]=INF;}
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
//	printf("u=%d\n",u+1);
	vector<int>parents;
	for(int i=0;i<(int)ET[u].size();i++)if(DEPTH[ET[u][i]]<DEPTH[u])parents.push_back(ET[u][i]);
	dp[D^1].Clear();
	for(int i=0;i<(int)dp[D].HIS.size();i++)
	{
		const int s=dp[D].HIS[i];
		const int val=dp[D][s];
		assert(Digit(s,DEPTH[u])==0);
		if(true)//not put
		{
			const int nxts=s,nxtc=val;
			dp[D^1].Update(nxts,nxtc);
		}
		if(true)//put
		{
			int nxts=s+2*POW3[DEPTH[u]],nxtc=val+C[u];
			for(int j=0;j<(int)parents.size();j++)
			{
				const int k=DEPTH[parents[j]];
				if(Digit(nxts,k)==0)nxts+=POW3[k];
			}
			dp[D^1].Update(nxts,nxtc);
		}
	}
	D^=1;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		if(DEPTH[ET[u][i]]==DEPTH[u]+1)Dfs(ET[u][i],dp);
	}
	dp[D^1].Clear();
	for(int i=0;i<(int)dp[D].HIS.size();i++)
	{
		const int s=dp[D].HIS[i];
		const int val=dp[D][s];
		const int nxts=s-Digit(s,DEPTH[u])*POW3[DEPTH[u]];
		assert(Digit(nxts,DEPTH[u])==0);
		if(Digit(s,DEPTH[u])>0)
		{
			dp[D^1].Update(nxts,val);
		}
		else
		{
			bool valid=false;
			for(int j=0;j<(int)parents.size();j++)if(Digit(s,DEPTH[parents[j]])==2){valid=true;break;}
			if(valid)dp[D^1].Update(nxts,val);
		}
	}
	D^=1;
}
int main()
{
//	freopen("in.txt","r",stdin);
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

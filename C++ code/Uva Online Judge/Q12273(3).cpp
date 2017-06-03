#include<cstdio>
#include<vector>
#include<cassert>
#include<map>
#include<stack>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Djset
{
	int s[10000];
	bool reindexed;
	void clear(const int n){reindexed=false;for(int i=0;i<n;i++)s[i]=i;}
	int Find(const int a){assert(!reindexed);return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){assert(!reindexed);if((a=Find(a))==(b=Find(b)))return false;s[a]=b;return true;}
	void ReIndex(const int n,vector<vector<int> >&result)
	{
		result.clear();
		map<int,int>idx;
		for(int i=0;i<n;i++)
		{
			const int v=Find(i);
			auto it=idx.find(v);
			if(it==idx.end())
			{
				const int sz=idx.size();
				result.push_back(vector<int>());
				idx[v]=sz;
				it=idx.find(v);
			}
			assert(it!=idx.end());
			result[it->second].push_back(i);
		}
		for(int i=0;i<n;i++)s[i]=idx[s[i]];
		reindexed=true;
	}
}DJ;
struct SolverSCC
{
	bool MOVE[20000];
	vector<int>ET[20000],EF[20000];
	int PRE[20000],LOW[20000],PRE_CNT,SCC[20000],SCC_CNT;
	void clear(const int n){for(int i=0;i<n*2;i++)MOVE[i]=false,ET[i].clear(),EF[i].clear(),PRE[i]=SCC[i]=0;PRE_CNT=SCC_CNT=0;}
	vector<int>REC;
	bool SetTrue(const int u)
	{            
		if(MOVE[u])return true;
		if(MOVE[u^1])return false;
		MOVE[u]=true;
		REC.push_back(u);
		for(const auto nxt:ET[u])if(!SetTrue(nxt))return false;
		for(const auto nxt:EF[u^1])if(!SetTrue(nxt^1))return false;
		return true;
	}            
	void AddEdge(const int a,const int b){ET[a].push_back(b),EF[b].push_back(a);}
	stack<int>STK;
	void Dfs(const int u,const int fa)
	{
		PRE[u]=LOW[u]=++PRE_CNT;
		STK.push(u);
		for(const auto nxt:ET[u])if(nxt!=fa)
		{
			if(PRE[nxt])getmin(LOW[u],PRE[nxt]);
			else if(!SCC[nxt])
			{
				Dfs(nxt,u);
				getmin(LOW[u],LOW[nxt]);
			}
		}
		if(LOW[u]==PRE[u])
		{
			SCC_CNT++;
			for(;;)
			{
				const int v=STK.top();STK.pop();
				SCC[v]=SCC_CNT;
//				printf("(%d,%d) is %d\n",v/2,v&1,SCC_CNT);
				if(v==u)break;
			}
		}
	}
	bool Solvable(const int n)
	{
		for(int i=0;i<n;i++)if(!MOVE[i*2+0]&&!MOVE[i*2+1])
		{
			REC.clear();
			if(!SetTrue(i*2+0))
			{
				for(const auto v:REC)MOVE[v]=false;
				if(!SetTrue(i*2+1))return false;
			}
		}
		return true;
	}
//	bool Solvable(const int n)
//	{
//		for(int i=0;i<n;i++)if(!MOVE[i*2+0]&&!MOVE[i*2+1])
//		{
//			if(!PRE[i*2+0])Dfs(i*2+0,-1);
//			if(!PRE[i*2+1])Dfs(i*2+1,-1);
//		}
//		for(int i=0;i<n;i++)if(SCC[i*2]||SCC[i*2+1])
//		{
////			assert(SCC[i*2]!=-1&&SCC[i*2+1]!=-1);
////			assert(!MOVE[i*2+0]&&!MOVE[i*2+1]);
//			if(SCC[i*2]==SCC[i*2+1])return false;
//		}
//		return true;
//	}
}SCC;
int N,T;
int S[10000];
vector<vector<int> >SAME;
bool Solve()
{
//	for(int i=0;i<N;i++)printf(" %d",DJ.s[i]);puts("");
	SCC.clear(N);
	for(int i=1;i<N;i++)SCC.AddEdge((i-1)*2+1,i*2+0),SCC.AddEdge(i*2+1,(i-1)*2+0);
	vector<int>settrue;
	for(int idx_same=0;idx_same<(int)SAME.size();idx_same++)
	{
		const auto &same=SAME[idx_same]; 
		static bool contain[4];
		for(int i=0;i<4;i++)contain[i]=false;
		int cnt=0;
		for(const auto v:same)if(!contain[S[v]])contain[S[v]]=true,cnt++;
		if(cnt==4)return false;
		else if(cnt==3)for(int c=0;;c++)
		{
			assert(c<4);
			if(!contain[c^2]){for(const auto v:same)
			{
				if(S[v]==c)settrue.push_back(v*2+0);
				else settrue.push_back(v*2+1);
			}break;}
		}
		else if(cnt==2)
		{
			vector<int>tmp;
			for(int i=0;i<4;i++)if(contain[i])tmp.push_back(i);
			if((tmp[0]-tmp[1])%2==0)for(const auto v:same)settrue.push_back(v*2+1);
			else
			{
				const int first=same[0];
				for(const auto v:same)
				{
					SCC.AddEdge(first*2,v*2+(S[first]==S[v]?0:1));
					SCC.AddEdge(first*2+1,v*2+(S[first]==S[v]?1:0));
				}
			}
		}
		else assert(cnt==1);
	}
//	for(const auto u:settrue)printf("u=%d, %d is %s\n",u,u/2,u&1?"true":"false");
	for(const auto u:settrue)if(!SCC.SetTrue(u))return false;
	return SCC.Solvable(N);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(;;)
	{
		assert(scanf("%d%d",&N,&T)==2);
		if(N==0&&T==0)break;
		static char tmp[10001];assert(scanf("%s",tmp)==1);
		for(int i=0;i<N;i++)
		{
			switch(tmp[i])
			{
				case'A':S[i]=0;break;
				case'G':S[i]=1;break;
				case'T':S[i]=2;break;
				case'C':S[i]=3;break;
				default:assert(0);break;
			}
		}
		DJ.clear(N);
		for(int i=0;i<T;i++)
		{
			static int len;assert(scanf("%d:",&len)==1);
			vector<int>seq;
			for(int i=0,v;i<len;i++)assert(scanf("%d",&v)==1&&v>=0&&v<N),seq.push_back(v);
			for(int i=0,j=len-1;i<j;i++,j--)DJ.Merge(seq[i],seq[j]);
		}
		DJ.ReIndex(N,SAME);
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
/*
10 2
ATGTAGGGGA
5: 2 3 5 8 9
10: 0 1 2 3 4 5 6 7 8 9
*/

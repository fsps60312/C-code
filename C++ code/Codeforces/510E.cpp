#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
struct Hungary
{
	int N,MATCH[100],NEXT[100];
	bool VB[100],EDGE[100][100];
	bool Match(const int u,int *match)
	{
		for(int i=0;i<N;i++)if(EDGE[u][i]&&!VB[i])
		{
			VB[i]=true;
			if(match[i]==-1||Match(match[i],match))
			{
				match[i]=u;
				return true;
			}
		}
		return false;
	}
	bool Solve()
	{
		for(int i=0;i<N;i++)MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VB[j]=false;
			if(!Match(i,MATCH))return false;
		}
		for(int i=0;i<N;i++)EDGE[MATCH[i]][i]=false;
		static int rnext[100];
		for(int i=0;i<N;i++)rnext[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VB[j]=false;
			if(!Match(i,rnext))return false;
		}
		for(int i=0;i<N;i++)NEXT[rnext[i]]=i;
		PrintResult();
		return true;
	}
	vector<pair<int,int> >SA,SB;
	void PrintResult()
	{
		static bool va[100];
		for(int i=0;i<N;i++)va[i]=false;
		vector<vector<int> >ans;
		for(int i=0;i<N;i++)if(!va[i])
		{
			vector<int>ta;
			int cur=i;
			for(;;)
			{
				va[cur]=true;
				ta.push_back(SA[cur].second);
				cur=NEXT[cur];
				ta.push_back(SB[cur].second);
				cur=MATCH[cur];
				if(cur==i)break;
			}
			ans.push_back(ta);
		}
		printf("%d\n",(int)ans.size());
		for(const vector<int>&ta:ans)
		{
			printf("%d",(int)ta.size());
			for(const int v:ta)printf(" %d",v);puts("");
		}
	}
}HUNGARY;
int N;
vector<pair<int,int> >ODD,EVEN;
bool IS_PRIME[20001];
bool Solve()
{
	if(ODD.size()!=EVEN.size())return false;
	HUNGARY.N=ODD.size();
	HUNGARY.SA=ODD,HUNGARY.SB=EVEN;
	for(int i=0;i<(int)ODD.size();i++)for(int j=0;j<(int)EVEN.size();j++)
	{
		HUNGARY.EDGE[i][j]=IS_PRIME[ODD[i].first+EVEN[j].first];
	}
	return HUNGARY.Solve();
}
int main()
{
	for(int i=2;i<=20000;i++)IS_PRIME[i]=true;
	for(int i=2;i<=20000;i++)if(IS_PRIME[i])
	{
		for(int j=2;i*j<=20000;j++)IS_PRIME[i*j]=false;
	}
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		ODD.clear(),EVEN.clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			(v&1?ODD:EVEN).push_back(make_pair(v,i+1));
		}
		if(!Solve())puts("Impossible");
	}
	return 0;
}

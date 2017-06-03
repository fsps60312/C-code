#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
const long long MOD=1000000007;
namespace AC
{
	const int W=26;
	vector<int>CH[W],END;
	int SZ;
	void push_back()
	{
		for(int i=0;i<W;i++)CH[i].push_back(-1);
		END.push_back(0);
		++SZ;
	}
	void clear()
	{
		for(int i=0;i<W;i++)CH[i].clear();
		END.clear();
		SZ=0;
		push_back();
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u]!=-1)return CH[c][u];
		push_back();
		return CH[c][u]=SZ-1;
	}
	void insert(const char *s)
	{
		int u=0;
		for(int i=0;s[i];i++)u=GetNxt(u,s[i]-'a');
		++END[u];
	}
	vector<int>FAIL;
	void Build()
	{
		FAIL.clear(),FAIL.resize(SZ,0);
		queue<int>q;
		for(int c=0;c<W;c++)if(CH[c][0]!=-1)q.push(CH[c][0]);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int c=0;c<W;c++)if(CH[c][u]!=-1)
			{
				const int nxt=CH[c][u];
				int &f=FAIL[nxt]=FAIL[u];
				while(f&&CH[c][f]==-1)f=FAIL[f];
				if(CH[c][f]!=-1)f=CH[c][f];
				END[nxt]+=END[f];
				q.push(nxt);
			}
		}
	}
	vector<long long>DP;
	void TransDP()
	{
		vector<long long>nxtDP;
		nxtDP.resize(SZ,0);
		for(int i=0;i<SZ;i++)if(END[i]==0)
		{
			for(int c=0;c<W;c++)
			{
				if(CH[c][i]==-1)
				{
					int cur=i;
					while(cur&&CH[c][cur]==-1)cur=FAIL[cur];
					if(CH[c][cur]!=-1)cur=CH[c][cur];
					CH[c][i]=cur;
				}
				(nxtDP[CH[c][i]]+=DP[i])%=MOD;
			}
		}
		DP.swap(nxtDP);
	}
	long long Get(const int repeat)
	{
		DP.clear(),DP.resize(SZ,0);
		DP[0]=1;
		for(int i=0;i<repeat;i++)TransDP();
		long long ans=0;
		for(int i=0;i<SZ;i++)if(END[i]==0)(ans+=DP[i])%=MOD;
		return ans;
	}
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		AC::clear();
		for(int i=0;i<M;i++)
		{
			static char s[101];
			scanf("%s",s);
			AC::insert(s);
		}
		AC::Build();
		printf("%lld\n",AC::Get(N));
	}
	return 0;
}

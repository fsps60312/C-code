#include<cstdio>
#include<vector>
#include<set>
using namespace std;
struct Hungary
{
	int N,M;
	int VB[10000],MATCH[10000];
	vector<int>ET[10000];
	bool Match(const int u)
	{
		for(const int nxt:ET[u])if(!VB[nxt])
		{
			VB[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
			}
		}
		return false;
	}
	int ANS[10000];
	int Solve()
	{
		int cnt=0,ans=0;
		while(cnt<N)
		{
			ans++;
			for(int i=0;i<M;i++)MATCH[i]=-1;
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<M;j++)VB[j]=false;
				if(Match(i))cnt++;
			}
			for(int i=0;i<M;i++)if(MATCH[i]!=-1)
			{
				vector<int>&e=ET[MATCH[i]];
				ANS[MATCH[i]]=(i==e[0]?1:0);
				e.clear();
			}
		}
		return ans;
	}
}HUNGARY;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&M);
	HUNGARY.N=M,HUNGARY.M=N;
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		HUNGARY.ET[i].clear();
		HUNGARY.ET[i].push_back(a),HUNGARY.ET[i].push_back(b);
	}
	printf("%d\n",HUNGARY.Solve());
	for(int i=0;i<M;i++)printf("%d\n",HUNGARY.ANS[i]);
	return 0;
}

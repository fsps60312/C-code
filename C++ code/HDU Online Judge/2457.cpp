#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
const int INF=2147483647;
struct AC_Automaton
{
	vector<int>CH[4];
	vector<bool>IS_END;
	int SIZE;
	void Clear()
	{
		for(int i=0;i<4;i++)CH[i].clear();
		IS_END.clear();
		SIZE=0;
		Extend();
	}
	void Extend()
	{
		for(int i=0;i<4;i++)CH[i].push_back(0);
		IS_END.push_back(false);
		SIZE++;
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u]==0)Extend(),CH[c][u]=SIZE-1;
		return CH[c][u];
	}
	int Id(const char c)
	{
		switch(c)
		{
			case'A':return 0;
			case'C':return 1;
			case'G':return 2;
			case'T':return 3;
			default:assert(0);return -1;
		}
	}
	void Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,Id(str[i]));
		IS_END[u]=true;
	}
	vector<int>FAIL;
	void BuildFail()
	{
		FAIL.resize(SIZE);
		FAIL[0]=0;
		queue<int>q;
		for(int i=0;i<4;i++)if(CH[i][0])FAIL[CH[i][0]]=0,q.push(CH[i][0]);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int i=0;i<4;i++)if(CH[i][u])
			{
				int &f=FAIL[CH[i][u]]=FAIL[u];
				while(f&&CH[i][f]==0)f=FAIL[f];
				f=CH[i][f];
				if(IS_END[f])IS_END[CH[i][u]]=true;
				q.push(CH[i][u]);
			}
		}
	}
	vector<int>DP[2];
	int Dp(const char *str)
	{
		DP[0].resize(SIZE),DP[1].resize(SIZE);
		for(int i=0;i<SIZE;i++)DP[0][i]=DP[1][i]=INF;
		DP[0][0]=0;
		int d=0;
		for(int loc=0;str[loc];loc++,d^=1)
		{
			const int c=Id(str[loc]);
			for(int u=0;u<SIZE;u++)if(DP[d][u]!=INF)
			{
				const int dp=DP[d][u];
				for(int nxtc=0;nxtc<4;nxtc++)
				{
					int nxtu=u;
					while(nxtu&&CH[nxtc][nxtu]==0)nxtu=FAIL[nxtu];
					nxtu=CH[nxtc][nxtu];
					if(!IS_END[nxtu])getmin(DP[d^1][nxtu],nxtc==c?dp:dp+1);
				}
				DP[d][u]=INF;
			}
		}
		int ans=INF;
		for(int i=0;i<SIZE;i++)getmin(ans,DP[d][i]);
		return ans==INF?-1:ans;
	}
}AC;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		AC.Clear();
		for(int i=0;i<N;i++)
		{
			static char dna[21];scanf("%s",dna);
			AC.Insert(dna);
		}
		AC.BuildFail();
		static char dna[1001];
		scanf("%s",dna);
		static int kase=1;
		printf("Case %d: %d\n",kase++,AC.Dp(dna));
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,X,Y,K,SZ;
vector<char>DIGIT,DEP;
vector<int>PRE;
int DP[2][10000000];
vector<int>V[2];
struct Edge
{
	int u,c;
	Edge(){}
	Edge(const int _u,const int _c):u(_u),c(_c){}
};
vector<Edge>ET[10];
inline bool Better(int a,int b)
{
	if(a==-1)return true;
	for(;a!=-1;)
	{
		if(DIGIT[a]!=DIGIT[b])return DIGIT[b]<DIGIT[a];
		if(a==b)return false;
		a=PRE[a],b=PRE[b];
	}
	assert(0);
}
void Solve1()
{
	for(int i=0;i<10;i++)for(int j=0;j<=X;j++)for(int k=0;k<=(N+1)*9;k++)DP[0][i+j*10000+k*10]=DP[1][i+j*10000+k*10]=-1;
	int mn=INF,mx=-INF;
	for(int i=0;i<10;i++)ET[i].clear();
	for(int i=0;i<10;i++)//initial number
	{
		for(int n=0,v,c;n<10;n++)//add n*k
		{
			v=i+n*K,c=v/10+v%10-i;
			ET[i].push_back(Edge(v/10,c));
			mn=min(mn,c),mx=max(mx,c);
		}
	}
	DIGIT.clear(),DEP.clear(),PRE.clear();
	static int MAXN=20000000;
	DIGIT.reserve(MAXN),PRE.reserve(MAXN),DEP.reserve(MAXN);
	DIGIT.push_back(-1),PRE.push_back(-1),DEP.push_back(0);
	V[0].clear(),V[1].clear();
	V[0].reserve(10*X*(N+1)*9),V[1].reserve(10*X*(N+1)*9);
	V[0].push_back(0);
	DP[0][0]=0;
	SZ=0;
	int nine=9;
	for(int d=0,digitloc=1;digitloc<=N;digitloc++,d^=1)
	{
		int bestzero=-1;
		int remain=N-digitloc;
		nine*=remain,mn*=remain,mx*=remain;
		int *dp0=DP[d],*dp1=DP[d^1];
		vector<int>&v0=V[d],&v1=V[d^1];
		for(int s=v0.size()-1;s>=0;s--)
		{
			static int u,cost,orig;
			u=v0[s];
			cost=u/10%1000;
			orig=u/10000;
			int &now=dp0[u];
			u%=10;
			if(u==0&&orig+1==X&&cost+ET[0][1].c==Y)
			{
				int uu=now;
				while(DEP[uu]+1<N)
				{
					DIGIT.push_back(0),PRE.push_back(uu),DEP.push_back(DEP[uu]+1);
					uu=++SZ;
				}
				DIGIT.push_back(1),PRE.push_back(uu),DEP.push_back(DEP[uu]+1);
				SZ++;
				if(Better(bestzero,SZ))bestzero=SZ;
			}
			static int i;i=0;
			if(digitloc==N)orig++,i++;
			static int dep;dep=DEP[now]+1;
			for(;i<10;i++,orig++)
			{
				const Edge &e=ET[u][i];
				if(orig>X||orig+nine<X||cost+e.c+mn>Y||cost+e.c+mx<Y)continue;
				static int nxt;
				nxt=orig*10000+(cost+e.c)*10+e.u;
				int &dest=dp1[nxt];
				DIGIT.push_back(i),PRE.push_back(now),DEP.push_back(dep);
				SZ++;
				if(Better(dest,SZ))
				{
					if(dest==-1)v1.push_back(nxt);
					dest=SZ;
				}
				else DIGIT.pop_back(),PRE.pop_back(),DEP.pop_back(),SZ--;
			}
			now=-1;
		}
		if(remain)nine/=remain,mn/=remain,mx/=remain;
		v0.clear();
		if(bestzero!=-1)
		{
			DP[N&1][ET[0][1].u+X*10000+Y*10]=bestzero;
			break;
		}
	}
	int ans=-1;
	for(int i=0;i<10;i++)
	{
		const int dp=DP[N&1][i+X*10000+Y*10];
//	  printf("dp[%d]:",i);for(int j=0;j<dp.size();j++)printf(" %d",dp[j]);puts("");
		if(dp!=-1&&Better(ans,dp))
		{
			assert(DIGIT[dp]!=0);
			ans=dp;
		}
	}
	if(DEP[ans]!=N)puts("-1");
	else
	{
		int cnt=0;
		while(PRE[ans]!=-1)
		{
			printf("%c",'0'+DIGIT[ans]);
			ans=PRE[ans];
			cnt++;
		}
		assert(cnt==N);
		puts("");
	}
}
void Solve2()
{
}
int main()
{
//  N=2,X=9,Y=9,K=5;
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	if(K==7)Solve1();
	else Solve1();
	return 0;
}

#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
void getmax(LL &a,const LL &b){if(b>a)a=b;}
LL Gcd(const LL &a,const LL &b){return b==0LL?a:Gcd(b,a%b);}
void bssert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Hungary
{
	int M,N;
	LL EDGE[500][500];
	LL WA[500],WB[500],LOW[500];
	int MATCH[500];
	bool VA[500],VB[500];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)
		{
			const LL &edge=EDGE[u][nxt];
			if(edge==WA[u]+WB[nxt])
			{
				VB[nxt]=true;
				if(MATCH[nxt]==-1||Match(MATCH[nxt]))
				{
					MATCH[nxt]=u;
					return true;
				}
			}
			else
			{
				assert(edge<WA[u]+WB[nxt]);
				getmin(LOW[nxt],WA[u]+WB[nxt]-edge);
			}
		}
		return false;
	}
	void Update()
	{
		LL low=INF;
		for(int i=0;i<N;i++)if(!VB[i])getmin(low,LOW[i]);
//		for(int i=0;i<M;i++)if(VA[i])
//			for(int j=0;j<N;j++)if(!VB[j])getmin(low,WA[i]+WB[j]-EDGE[i][j]);
		assert(low!=INF);
		for(int i=0;i<M;i++)if(VA[i])WA[i]-=low;
		for(int i=0;i<N;i++)if(VB[i])WB[i]+=low;
	}
	void Solve()
	{
		for(int i=0;i<M;i++)
		{
			WA[i]=0;
			for(int j=0;j<N;j++)getmax(WA[i],EDGE[i][j]);
		}
		for(int i=0;i<N;i++)WB[i]=0,MATCH[i]=-1;
		for(int i=0;i<M;i++)
		{
			for(;;)
			{
				for(int j=0;j<M;j++)VA[j]=false;
				for(int j=0;j<N;j++)VB[j]=false,LOW[j]=INF;
				if(Match(i))break;
				else Update();
			}
		}
	}
	LL GetSum()
	{
		LL ans=0LL;
		for(int i=0;i<M;i++)ans+=WA[i];
		for(int i=0;i<N;i++)ans+=WB[i];
		return ans;
	}
}HUNGARY;
const LL BASE=2*2*2*3*3*5*7;
int N,M,K;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	static int casecount;scanf("%d",&casecount);
	while(casecount--)
	{
		scanf("%d%d%d",&M,&N,&K);
		if(N<M)N=M;
		HUNGARY.M=M,HUNGARY.N=N;
		for(int i=0;i<M;i++)for(int j=0;j<N;j++)HUNGARY.EDGE[i][j]=0LL;
		for(int i=0,a,b;i<K;i++)
		{
			static LL q,p;
			scanf("%d%d%lld%lld",&a,&b,&q,&p);
			bssert(p>=1LL&&p<=10LL);
			a--,b--;
			bssert(a>=0&&a<M&&b>=0&&b<N);
			const LL cost=q*(BASE/p);
			HUNGARY.EDGE[a][b]=cost;
		}
		HUNGARY.Solve();
		LL ans=HUNGARY.GetSum();
		LL g=Gcd(ans,BASE);
		printf("%lld %lld\n",ans/g,BASE/g);
	}
	return 0;
}

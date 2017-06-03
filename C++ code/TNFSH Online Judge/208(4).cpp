#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=1000000000000000LL;//9223372036854775807LL;
void getmin(LL &a,const LL &b){if(b<a)a=b;}
void getmax(LL &a,const LL &b){if(b>a)a=b;}
LL Gcd(const LL &a,const LL &b){return b==0LL?a:Gcd(b,a%b);}
void bssert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Edge
{
	int to;
	LL cost;
	Edge(){}
	Edge(const int _t,const LL &_c):to(_t),cost(_c){}
};
struct Djset
{
	int s[1000];
	void clear(const int n){for(int i=0;i<n;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b;return true;}
}DJ1,DJ2;
struct Hungary
{
	int M,N;
	vector<Edge>EA[500],EB[500];
	LL WA[500],WB[500],LOW[500];
	int MATCH[500];
	bool VA[500],VB[500];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int i=0;i<(int)EA[u].size();i++)
		{
			const Edge &e=EA[u][i];
			if(e.cost==WA[u]+WB[e.to])
			{
				VB[e.to]=true;
				if(MATCH[e.to]==-1||Match(MATCH[e.to]))
				{
					MATCH[e.to]=u;
					return true;
				}
			}
			else
			{
				assert(e.cost<WA[u]+WB[e.to]);
				getmin(LOW[e.to],WA[u]+WB[e.to]-e.cost);
			}
		}
		return false;
	}
	bool Update()
	{
		LL low=INF;
		for(int i=0;i<N;i++)if(!VB[i])getmin(low,LOW[i]);
		if(low==INF)return false;
		assert(low!=INF);
		for(int i=0;i<M;i++)if(VA[i])WA[i]-=low;
		for(int i=0;i<N;i++)if(VB[i])WB[i]+=low;
		return true;
	}
	void Solve()
	{
		for(int i=0;i<M;i++)WA[i]=INF;
		for(int i=0;i<N;i++)WB[i]=0,MATCH[i]=-1;
		for(int i=0;i<M;i++)
		{
			assert(!EA[i].empty());
			for(;;)
			{
				for(int j=0;j<M;j++)VA[j]=false;
				for(int j=0;j<N;j++)VB[j]=false,LOW[j]=INF;
				if(Match(i))break;
				else if(!Update())break;
			}
		}
		for(int i=0;i<M;i++)VA[i]=false;
		for(int i=0;i<N;i++)VB[i]=false;
		for(int i=0;i<N;i++)for(const Edge &e:EA[i])if(e.cost==WA[i]+WB[e.to])VA[i]=VB[e.to]=true;
		for(int i=0;i<M;i++)if(!VA[i])
		{
			WA[i]=EA[i][0].cost-WB[EA[i][0].to];
			for(const Edge &e:EA[i])getmax(WA[i],e.cost-WB[e.to]);
		}
		for(int i=0;i<N;i++)if(!VB[i])
		{
			WB[i]=EB[i][0].cost-WA[EB[i][0].to];
			for(const Edge &e:EB[i])getmax(WB[i],e.cost-WA[e.to]);
		}
		DJ1.clear(N+M);
		DJ2.clear(N+M);
		int cnt1=N+M,cnt2=N+M;
		for(int i=0;i<M;i++)for(const Edge &e:EA[i])
		{
			assert(WA[i]+WB[e.to]>=e.cost);
//			printf("(%d,%d,%d): %d\n",i,e.to,e.cost,WA[i]+WB[e.to]);
			if(DJ1.Merge(i,M+e.to))cnt1--;
			if(WA[i]+WB[e.to]==e.cost&&DJ2.Merge(i,M+e.to))cnt2--;
		}
//		if(cnt1!=cnt2)printf("cnt(%d,%d)\n",cnt1,cnt2);
		assert(cnt1==cnt2);
	}
	void PrintF(const LL a)
	{
		const LL g=Gcd(a,2*2*2*3*3*5*7);
		printf(" %d/%d",a/g,2*2*2*3*3*5*7/g);
	}
	LL GetSum()
	{
		LL ans=0LL;
		for(int i=0;i<M;i++)ans+=WA[i],PrintF(WA[i]);puts("");
		for(int i=0;i<N;i++)ans+=WB[i],PrintF(WB[i]);puts("");
		return ans;
	}
}HUNGARY;
const LL BASE=2*2*2*3*3*5*7;
int N,M,K;
int main()
{
	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	static int casecount;scanf("%d",&casecount);
	while(casecount--)
	{
		scanf("%d%d%d",&M,&N,&K);
		HUNGARY.M=M,HUNGARY.N=N;
		for(int i=0;i<M;i++)HUNGARY.EA[i].clear();
		for(int i=0;i<N;i++)HUNGARY.EB[i].clear();
		for(int i=0,a,b;i<K;i++)
		{
			static LL q,p;
			scanf("%d%d%lld%lld",&a,&b,&q,&p);
			bssert(p>=1LL&&p<=10LL);
			a--,b--;
			bssert(a>=0&&a<M&&b>=0&&b<N);
			const LL cost=q*(BASE/p);
			HUNGARY.EA[a].push_back(Edge(b,cost));
			HUNGARY.EB[b].push_back(Edge(a,cost));
		}
		HUNGARY.Solve();
		LL ans=HUNGARY.GetSum();
		LL g=Gcd(ans,BASE);
		printf("%lld %lld\n",ans/g,BASE/g);
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<cstring>
#include<bitset>
#include<cassert>
//#define int long long
using namespace std;
typedef long long LL;
const int MAXN=1e3+3;
const int MOD=1e9+7;
LL FAC[MAXN],IFAC[MAXN];
void Initialize()
{
	static LL inv[MAXN];
    FAC[0]=1;
    for(int i=1;i<MAXN;i++)FAC[i]=FAC[i-1]*i%MOD;
    inv[0]=inv[1]=1;
    for(int i=2;i<MAXN;i++)inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
    IFAC[0]=1;
    for(int i=1;i<MAXN;i++)IFAC[i]=IFAC[i-1]*inv[i]%MOD;
}
LL C(int x,int y)
{
    if(y<0||y>x)return 0;
    return FAC[x]*IFAC[y]%MOD*IFAC[x-y]%MOD;
}
void Add(LL &x,const LL &y){if((x+=y)>=MOD)x-=MOD;}
struct Helper
{
    int N,A[MAXN];
	LL DP[MAXN][MAXN][2][2];//i,k,h(i-1),h(i)
    void Initialize(int _N){memset(A+1,0,sizeof(LL)*(N=_N));}
    void Apply(int i,int j){A[i]=j;}
    int IsSatisfied(int i){return A[i]&&(A[i]==i||A[i]==i-1||A[i]==i+N-1);}
    vector<LL>Solve()
    {
        for(int i=1;i<=N;i++) for(int j=0;j<=i;j++) memset(DP[i][j],0,sizeof(LL)*4);
        bitset<MAXN> has;
        for(int i=1;i<=N;i++) has[A[i]]=1;has[0]=0;
        DP[0][0][0][0]=1;
        for(int i=1;i<=N;i++) for(int k=0;k<=i;k++) for(int b=0;b<2;b++)
        {
            LL *me=DP[i][k][b];
            if(has[i] && A[i])
            {
                me[0]=0;
                int t=k-IsSatisfied(i);
                if(t<0) me[1]=0;
                else me[1]=(DP[i-1][t][0][b]+DP[i-1][t][1][b])%MOD;
            }
            else if(!has[i] && A[i])
            {
                int t=k-IsSatisfied(i);
                if(t<0) me[0]=0;
                else me[0]=(DP[i-1][t][0][b]+DP[i-1][t][1][b])%MOD;
                me[1]=0;
            }
            else if(has[i] && !A[i])
            {
                me[0]=0;
                me[1]=(DP[i-1][k][0][b]+DP[i-1][k][1][b])%MOD;
                if(b && k && i>1) Add(me[1],(DP[i-1][k-1][0][0]+DP[i-1][k-1][1][0])%MOD);// put i-1 @ a[i]
            }
            else
            {
                me[0]=(DP[i-1][k][0][b]+DP[i-1][k][1][b])%MOD;
                if(b && k && i>1) Add(me[0],(DP[i-1][k-1][0][0]+DP[i-1][k-1][1][0])%MOD);// put i-1 @ a[i]
                if(k<0) me[1]=0;
                else me[1]=(DP[i-1][k-1][0][b]+DP[i-1][k-1][1][b])%MOD;
            }
        }
        vector<LL> ret(N+1,0);
        for(int i=0;i<=N;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) Add(ret[i],DP[N][i][j][k]);
        int s=(int)has.count();
        for(int i=1;i<=N;i++) s-=IsSatisfied(i);
        for(int i=0;i<=N;i++) ret[i]=ret[i]*(N-i-s>=0?FAC[N-i-s]:0)%MOD;
        return ret;
    }
}HELPER;
int N,M,K;
int A[MAXN],B[MAXN];
void ReadInput()
{
	scanf("%lld%lld%lld",&N,&M,&K);
    for(int i=1;i<=K;i++) scanf("%lld%lld",&A[i],&B[i]);
}
LL POLY[MAXN];
void Build()
{
    memset(POLY,0,sizeof(LL)*(N+1));
    if(K==0)
    {
        HELPER.Initialize(N);
        HELPER.Apply(1,N);
        vector<LL>v=HELPER.Solve();
        for(int i=0;i<=N;i++) Add(POLY[i],v[i]);
        HELPER.Initialize(N);
        v=HELPER.Solve();
        for(int i=0;i<=N;i++) Add(POLY[i],v[i]);
    }
    else
    {
        int sh=N+1-B[1];
        for(int i=1;i<=K;i++)
        {
            A[i]=(A[i]+sh-1)%N+1;
            B[i]=(B[i]+sh-1)%N+1;
        }
        assert(B[1]==1);
        HELPER.Initialize(N);
        for(int i=1;i<=K;i++) HELPER.Apply(B[i],A[i]);
        vector<LL>v=HELPER.Solve();
        for(int i=0;i<=N;i++) Add(POLY[i],v[i]);
    }
}
void Solve()
{
	static LL co[MAXN];
    memset(co,0,sizeof(LL)*(N+1));
    LL ans=0;
	int die=0;
    for(int i=1;i<=N;i++) die+=HELPER.IsSatisfied(i);
    for(int i=M;i<=N;i++)
    {
        LL mul=(MOD+1-co[i])%MOD;
        Add(ans,POLY[i]*mul%MOD);
        for(int j=i;j<=N;j++) Add(co[j],mul*C(j-die,i-die)%MOD);
    }
    if((ans%=MOD)<0) ans+=MOD;
    printf("%lld\n",ans);
}
int main()
{
//	freopen("in.txt","r",stdin);
    Initialize();
    int testcount;scanf("%lld",&testcount);
    while(testcount--)
    {
        ReadInput();
        if(N==1){printf("%lld\n",1LL);continue;}
        Build();//rotate / k==0
        Solve();
    }
    return 0;
}

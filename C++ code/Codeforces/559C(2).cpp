#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
struct Point
{
	int r,c;
	Point(){}
	Point(const int _r,const int _c):r(_r),c(_c){}
};
void ExGcd(const LL a,const LL b,LL &x,LL &y)
{
	if(b==0LL)assert(a==1LL),x=1LL,y=0LL;
	else ExGcd(b,a%b,y,x),(y-=a/b*x)%=MOD;
}//(a-a/b*b)x+by==1
LL Inv(const LL v)
{
	static LL x,y;
	ExGcd(v,MOD,x,y);//x*v+y*MOD==1
	return (x%MOD+MOD)%MOD;
}
void Mul(LL &a,const LL &b){(a*=b)%=MOD;}
LL LEVEL[200001],INVL[200001];
LL Solve(const LL dy,const LL dx)
{
	return LEVEL[dy+dx]*INVL[dy]%MOD*INVL[dx]%MOD;
}
int H,W,N;
vector<Point>P;
vector<int>ET[2000];
LL DP[2000];
LL GetDP(const int u)
{
	LL &ans=DP[u];
	if(ans!=-1LL)return ans;
	ans=Solve(H-P[u].r,W-P[u].c);
	for(const int nxt:ET[u])
	{
		(ans-=Solve(P[nxt].r-P[u].r,P[nxt].c-P[u].c)*GetDP(nxt))%=MOD;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	LEVEL[0]=1LL,INVL[0]=1LL;
	for(int i=1;i<=200000;i++)LEVEL[i]=LEVEL[i-1]*i%MOD,INVL[i]=Inv(LEVEL[i]);
	while(scanf("%d%d%d",&H,&W,&N)==3)
	{
		P.clear();
		for(Point p;N--;)scanf("%d%d",&p.r,&p.c),P.push_back(p);
		N=P.size();
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(j!=i&&P[j].r>=P[i].r&&P[j].c>=P[i].c)
		{
			ET[i].push_back(j);
		}
		for(int i=0;i<N;i++)DP[i]=-1LL;
		LL ans=Solve(H-1LL,W-1LL);
		for(int i=0;i<N;i++)(ans-=Solve(P[i].r-1,P[i].c-1)*GetDP(i))%=MOD;
		printf("%I64d\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}

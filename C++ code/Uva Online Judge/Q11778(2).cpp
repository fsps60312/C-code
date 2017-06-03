#include<cstdio>
#include<vector>
using namespace std;
#define LL long long
const LL MOD=1000000007LL;
LL T,N,M,P,MAT[100][100];
vector<LL> TO[100];
void initMAT()
{
	for(LL i=0LL;i<N;i++)for(LL j=0LL;j<N;j++)MAT[i][j]=0LL;
	for(LL i=0LL;i<N;i++)
	{
		MAT[i][i]--;
		for(int _=0;_<TO[i].size();_++)
		{
			LL &j=TO[i][_];
			MAT[i][j]++;
		}
		for(LL j=0LL;j<N;j++)MAT[i][j]=(MAT[i][j]%P+P)%P;
	}
}
LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b)
	{
		exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
	else x=1LL,y=0LL;
}
LL inv(LL a)
{
	LL x,y;
	exgcd(a,P,x,y);
	return (x%P+P)%P;
}
void Exchange(LL r1,LL r2){for(LL i=0LL,v;i<N;i++)v=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=v;}
void showMAT(char *msg)
{
	puts(msg);
	for(LL i=0LL;i<N;i++)
	{
		for(LL j=0LL;j<N;j++)
		{
			printf(" %lld",MAT[i][j]);
		}
		puts("");
	}
}
LL solve()
{
	LL cnt=0LL;
	for(LL i=0LL;i<N;i++)
	{
		LL j=i;for(;j<N;j++)if(MAT[j][i])break;
		if(j==N){cnt++;continue;}
		if(j!=i)Exchange(i,j);
		for(j=0LL;j<N;j++)
		{
			if(j==i||!MAT[j][i])continue;
			LL ratio=inv(MAT[i][i])*MAT[j][i]%P;
			for(LL k=0LL;k<N;k++)MAT[j][k]=((MAT[j][k]-MAT[i][k]*ratio)%P+P)%P;
		}
	}
	LL ans=1LL;
	while(cnt--)ans*=P,ans%=MOD;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	int kase=1;
	while(T--)
	{
		scanf("%lld%lld%lld",&N,&M,&P);
		for(LL i=0LL;i<N;i++)TO[i].clear();
		for(LL i=0LL,p,q;i<M;i++)
		{
			scanf("%lld%lld",&p,&q);
			p--,q--;
			TO[p].push_back(q);
			TO[q].push_back(p);
		}
		initMAT();
		printf("Case %d: %lld\n",kase++,solve());
	}
	return 0;
}

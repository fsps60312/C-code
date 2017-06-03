#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000009LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,P;
vector<vector<LL> >A,B;
void ReadInput()
{
	scanf("%d%d",&N,&P);
	LL *a=new LL[N],*b=new LL[N];
	for(int i=0;i<N;i++)scanf("%lld",&a[i]);
	for(int i=0;i<N;i++)scanf("%lld",&b[i]);
	for(int i=0;i<N;i++)if(a[i]>b[i])swap(a[i],b[i]);
	A.clear(),B.clear();
	for(int i=0;i<N;i++)
	{
		vector<LL>va,vb;
		while(a[i])va.push_back(a[i]%P),a[i]/=P;
		while(b[i])vb.push_back(b[i]%P),b[i]/=P;
		A.push_back(va),B.push_back(vb);
	}
	delete[]a;delete[]b;
}
LL Solve(const vector<LL>&l,const vector<LL>&r)//O(7*20)
{
	assert((int)l.size()==N&&l.size()==r.size());
	static LL dp[2][19];
	for(int i=0;i<P;i++)dp[0][i]=0LL;
	dp[0][0]=1LL;
	int d=0;
	for(int i=0;i<N;i++,d^=1)
	{
		for(int j=0;j<P;j++)dp[d^1][j]=0LL;
		for(int j=0;j<P;j++)
		{
			for(int k=l[i];k<=r[i]&&j+k<P;k++)(dp[d^1][j+k]+=dp[d][j])%=MOD;
		}
	}
	LL ans=0LL;
	for(int i=0;i<P;i++)(ans+=dp[d][i])%=MOD;
	return ans;
}
LL Get(const vector<vector<LL> >&s,const int i,const int j){return j<(int)s[i].size()?s[i][j]:0LL;}
LL DP[51][1<<14];
bool Get(const int v,const int i){return (v&(1<<i))>0;}
LL Solve(const vector<vector<LL> >&A,const vector<vector<LL> >&B,const int M)//O(50*(2187*(21+140)+(2187*7)))
{
	assert(M<=50);
	for(int u=0;u<(1<<(N*2));u++)DP[M][u]=0LL;
	DP[M][0]=1LL;//all incomplete
	for(int i=M-1;i>=0;i--)
	{
		for(int u=0;u<(1<<(2*N));u++)
		{
			DP[i][u]=0LL;
			for(int a=u;;a=(a-1)&u)//complete can come from incomplete
			{
				if(DP[i+1][a])
				{
					vector<LL>ls,rs;
					for(int j=0;j<N;j++)
					{
						LL l,r;
						if(!Get(a,j*2)&&!Get(a,j*2+1))
						{
							const int v1=Get(A,j,i),v2=Get(B,j,i);
							if((v1==v2)!=(!Get(u,j*2)&&!Get(u,j*2+1)))
							{
								l=0,r=-1;
							}
							else if(!Get(u,j*2)&&!Get(u,j*2+1))l=r=v1;
							else if(!Get(u,j*2))l=r=v1;
							else if(!Get(u,j*2+1))l=r=v2;
							else l=v1+1,r=v2-1;
						}
						else if(!Get(a,j*2))
						{
							if(Get(u,j*2))l=Get(A,j,i)+1,r=P-1;
							else l=r=Get(A,j,i);
						}
						else if(!Get(a,j*2+1))
						{
							if(Get(u,j*2+1))l=0,r=Get(B,j,i)-1;
							else l=r=Get(B,j,i);
						}
						else l=0,r=P-1;
						ls.push_back(l),rs.push_back(r);
					}
					(DP[i][u]+=DP[i+1][a]*Solve(ls,rs))%=MOD;
				}
				if(a==0)break;
			}
		}
	}
	LL ans=0LL;
	for(int u=0;u<(1<<(N*2));u++)(ans+=DP[0][u])%=MOD;
	return ans;
}
LL Solve()
{
	int m=0;
	for(int i=0;i<N;i++)getmax(m,A[i].size()),getmax(m,B[i].size());
	return Solve(A,B,m);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		ReadInput();
		static int kase=1;
		printf("Case %d: %lld\n",kase++,Solve());
	}
	return 0;
}

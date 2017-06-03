#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000009LL;
int N,P;
vector<vector<LL> >A,B;
//LL C[14][14];
//void Initialize()
//{
//	for(int i=1;i<=13;i++)
//	{
//		C[i][0]=C[i][i]=1LL;
//		for(int j=1;j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
//	}
//}
LL Solve(const vector<LL>&s)
{
	static LL dp[2][19];
	for(int i=0;i<P;i++)dp[0][i]=0LL;
	dp[0][0]=1LL;
	int d=0;
	for(int i=0;i<(int)s.size();i++,d^=1)
	{
		for(int j=0;j<P;j++)dp[d^1][j]=0LL;
		for(int j=0;j<P;j++)
		{
			for(int k=0;k<=s[i]&&j+k<P;k++)(dp[d^1][j+k]+=dp[d][j])%=MOD;
		}
	}
	LL ans=0LL;
	for(int i=0;i<P;i++)(ans+=dp[d][i])%=MOD;
	return ans;
}
LL Get(const vector<vector<LL> >&s,const int i,const int j){return j<(int)s[i].size()?s[i][j]:0LL;}
LL DP[51][1<<7];
LL Solve(const vector<vector<LL> >&s)
{
	for(int i=0;i<N;i++)if(s[i][0]<0LL)return 0LL;
	const int m=(int)s[N-1].size();
	for(int s=0;s<(1<<N);s++)DP[m][s]=0LL;
	DP[m][0]=1LL;//all incomplete
	for(int i=m-1;i>=0;i--)
	{
		for(int u=0;u<(1<<N);u++)
		{
			DP[i][u]=0LL;
			for(int a=u;a;a=(a-1)&u)//complete can come from incomplete
			{
				LL v=DP[i+1][a];
				for(int j=0;j<N;j++)(v*=(a&(1<<j)?Get(s,j,i):1LL))%=MOD;
				(DP[i][u]+=v)%=MOD;
			}
//			vector<LL>tmp;
//			for(int j=0;j<N;j++)tmp.push_back(u&(1<<j)?P-1:Get(s,j,i));
//			DP[i][u]=DP[i+1][u]*
		}
	}
	
}
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
		a[i]--;
		while(a[i])va.push_back(a[i]%P),a[i]/=P;
		while(b[i])vb.push_back(b[i]%P),b[i]/=P;
		A.push_back(va),B.push_back(vb);
	}
	delete[]a;delete[]b;
}
int CntBits(int x)
{
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
bool CmpMyNumber(const vector<LL>&a,const vector<LL>&b)
{
	if(a.size()!=b.size())return a.size()<b.size();
	for(int i=(int)a.size()-1;i>=0;i--)if(a[i]!=b[i])return a[i]<b[i];
	return false;
}
LL Solve()
{
	LL ans=0LL;
	for(int s=0;s<(1<<N);s++)
	{
		vector<vector<LL> >tmp;
		for(int i=0;i<N;i++)
		{
			if(s&(1<<i))tmp.push_back(A[i]);
			else tmp.push_back(B[i]);
		}
		sort(tmp.begin(),tmp.end(),CmpMyNumber);
		if(CntBits(s)&1)(ans-=Solve(tmp))%=MOD;
		else (ans+=Solve(tmp))%=MOD;
	}
	return (ans%MOD+MOD)%MOD;
}
int main()
{
	freopen("in.txt","r",stdin);
//	Initialize();
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		ReadInput();
		printf("%lld\n",Solve());
	}
	return 0;
}

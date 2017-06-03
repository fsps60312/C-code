#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1000000009LL;
int N,P,POW3[8];
vector<vector<LL> >A,B;
LL Solve(const vector<LL>&l,const vector<LL>&r)//O(7*20)
{
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
LL DP[51][1<<7];
LL Solve(const vector<vector<LL> >&s)//O(50*(2187*(21+140)+(2187*7)))
{
	for(int i=0;i<N;i++)if(Get(s,i,0)<0LL)return 0LL;
	const int m=(int)s[N-1].size();
	for(int u=0;u<(1<<N);u++)DP[m][u]=0LL;
	DP[m][0]=1LL;//all incomplete
	for(int i=m-1;i>=0;i--)
	{
		static LL pre_cal[2187];
		for(int u=0;u<POW3[N];u++)
		{
			vector<LL>l,r;
			for(int j=0;j<N;j++)
			{
				const int d=u/POW3[j]%3;
				if(d==0)l.push_back(0LL),r.push_back(P-1LL);
				else if(d==1)l.push_back(0LL),r.push_back(Get(s,j,i)-1LL);
				else if(d==2)l.push_back(Get(s,j,i)),r.push_back(Get(s,j,i));
				else assert(0);
			}
			pre_cal[u]=Solve(l,r);
		}
		for(int u=0;u<(1<<N);u++)
		{
			DP[i][u]=0LL;
			for(int a=u;;a=(a-1)&u)//complete can come from incomplete
			{
				int v=0;
				vector<LL>l,r;
				for(int j=0;j<N;j++)
				{
					if(a&(1<<j))v+=0*POW3[j];
					else if(u&(1<<j))v+=1*POW3[j];
					else v+=2*POW3[j];
				}
				(DP[i][u]+=DP[i+1][a]*pre_cal[v])%=MOD;
				if(a==0)break;
			}
		}
	}
	LL ans=0LL;
	for(int u=0;u<(1<<N);u++)(ans+=DP[0][u])%=MOD;
	return ans;
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
//	freopen("in.txt","r",stdin);
	POW3[0]=1;
	for(int i=1;i<=7;i++)POW3[i]=POW3[i-1]*3;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		ReadInput();
		static int kase=1;
		printf("Case %d: %lld\n",kase++,Solve());
	}
	return 0;
}
